---
layout: post
title: 'TIL: MySQL will return 2 rows affected if UPSERT updates an existing row'
categories: blog
tags: ['databases', 'mysql', 'postgres', 'programming', 'til']
excerpt: "An interesting discovery on how MySQL handles UPSERT"
date:  10 October, 2024
author: self
---

I like using `Upsert` for my `CreateOrUpdate` methods in my application code. It simplifies the application programming and avoids an unnecessary redundant query where I can avoid making 2 separate queries:

- first to check if the row exists or not
- second to insert it

And last week I learned that if the row already exists and your upsert query is updating the row instead, then MySQL will return the result of rows affected as `2`. I found myself being surprised by  this finding and felt it important to blog about. 

Let's look at this with a simple example. 

Say, we have a table `users` with two columns: `username` and `login_count`:

```sql
CREATE TABLE users (
  username varchar(32) PRIMARY KEY,
  login_count INT DEFAULT 1
);
```

And if you were to write a query that inserts a new username with login_count = 1, or if the username already exists, then increment the current value of `login_count`, you'd write the following query:

```sql
mysql> INSERT INTO users (username) VALUES ('johndoe') ON DUPLICATE KEY UPDATE login_count = login_count + 1;
Query OK, 1 row affected (0.01 sec)
```

Which results in a new row being inserted. We can clearly see that 1 row was affected by the query. Let's look at the table now:

```sql
mysql> select * from users;
+----------+-------------+
| username | login_count |
+----------+-------------+
| johndoe  |           1 |
+----------+-------------+
1 row in set (0.00 sec)
```

Looks good! We have a single row as expected. Now let's try to run the same query again (the user logged in again):

```
mysql> INSERT INTO users (username) VALUES ('johndoe') ON DUPLICATE KEY UPDATE login_count = login_count + 1;
Query OK, 2 rows affected (0.00 sec)
```

The output suggests that 2 rows were affected. Does that mean we have 2 rows in the table now? Or perhaps we have a bug in our schema? Neither, but let's look at the table again to be sure:

```
mysql> select * from users;
+----------+-------------+
| username | login_count |
+----------+-------------+
| johndoe  |           2 |
+----------+-------------+
1 row in set (0.01 sec)
```

In fact, our query worked as expected. From the Database's point of view, 2 rows
affected makes sense – 1 row that was attempted to be inserted and then another
row that was updated. But I initially found it confusing as I was writing some
tests for my DB layer in Go (or else I would never have learned this cool
fact!). Here's a short example of what my test looked like:

```go
func TestUserStore_Upsert(t *testing.T) {
	// Sets up a test database and applies the migrations. Out of scope for this blog post.
	db, err := setupDB(t)
	if err != nil {
		t.Fatal("failed to setup test database", err)
	}

	store := UserStore{db: db}
	if err = store.Upsert("johnwick"); err != nil {
		t.Fatal("failed to insert", err)
	}

	err = store.Upsert("johnwick")
	if err != nil {
		t.Fatal("failed to update", err)
	}
}
```

And it failed with:

```go
$ go test
--- FAIL: TestUserStore_Upsert (0.04s)
    main_test.go:31: failed to update unexpected rowsAffected: 2 for upsert of username: "johnwick"
FAIL
exit status 1
FAIL	github.com/indradhanush/mysql-rows-affected	0.279s
```

The failing code looked like this:

```go
	if rowsAffected != 1 {
		return fmt.Errorf("unexpected rowsAffected: %d for upsert of username: %q", rowsAffected, username)
	}
    
    return nil
```

This was the only check in my code. As a result of this failure, I then updated my code to look somewhat different:

```go
	if rowsAffected == 1 || rowsAffected == 2 {
		return nil
	}

	return fmt.Errorf("unexpected rowsAffected: %d for upsert of username: %q", rowsAffected, username)
```

And then my test passed!

```
$ go test -v
=== RUN   TestUserStore_Upsert
--- PASS: TestUserStore_Upsert (0.04s)
PASS
ok  	github.com/indradhanush/mysql-rows-affected	0.283s
```

Morale of the story? Write tests! 😛

If you'd like to check out the code and play around with it yourself you can find it [here](https://github.com/indradhanush/mysql-rows-affected-go). And if you liked this blog post, I won't mind you adding a star on the GitHub repo. 😁 

Edit: I went looking for the docs _after_ I published this post today, and found out that this is a  [well-documented and expected behaviour](https://dev.mysql.com/doc/refman/8.4/en/insert-on-duplicate.html):

> With ON DUPLICATE KEY UPDATE, the affected-rows value per row is 1 if the row is inserted as a new row, 2 if an existing row is updated, and 0 if an existing row is set to its current values.

While, Postgres on the other hand will return 1 rows affected as the result. While I still find it counter-intuitive, my best guess as to why MySQL chose to do this way is that the authors possibly wanted to provide an API to the consumer to distinguish between an `INSERT` and `UPDATE` operation. 

**P.S.:** If you made it this far - thank you for reading but another little tidbit is that you can also run `select row_count()` immediately after a query to get this number. But if you run it again the result will be `-1`, since it's updated after each query. And we've just run a new query in itself with `select row_count()` which affects no rows at all.

**P.P.S:** Technically it's a Last-Week-I-Learned but I didn't have the time to blog about it then.

## Addendum: Bulk inserts

When performing an UPSERT on a single row, the output is still unambiguous. We can tell whether the row was inserted (1), updated (2), or unchanged (0). But this gets very confusing for bulk upserts. If you've been following along, our table currently looks like:

```
mysql> select * from users;
+----------+-------------+
| username | login_count |
+----------+-------------+
| johndoe  |           2 |
+----------+-------------+
1 row in set (0.01 sec)
```

Say we wanted to UPSERT a few more users – spiderman, batman, wonderwoman, catwoman and superman while also updating the login count for existing users. Let's execute the following query:

```sql
mysql> INSERT into
       users (username)
     VALUES
       ("johnwick"),
       ("spiderman"),
       ("batman"),
       ("wonderwoman"),
       ("catwoman"),
       ("superman") on duplicate key
     UPDATE login_count = login_count + 1;
Query OK, 7 rows affected (0.00 sec)
Records: 6  Duplicates: 1  Warnings: 0
```

The mysql shell is correctly identifying the number of existing rows here. But the rows affected remains more than the total number of rows! 

```sql
mysql> select row_count();
+-------------+
| row_count() |
+-------------+
|           7 |
+-------------+
1 row in set (0.01 sec)
```

And one last time, if we run the same query again you'll now see an even more inflated number of rows affected (everything is a duplicate, so each row is counted twice, once for insertion and once for updating it)!

```sql
// Same query as above, skipped here for ease of reading. 
Query OK, 12 rows affected (0.00 sec)
Records: 6  Duplicates: 6  Warnings: 0
```

Running the query to see the affected rows returns 12:

```sql
mysql> select row_count();
+-------------+
| row_count() |
+-------------+
|          12 |
+-------------+
1 row in set (0.00 sec)
```

The MySQL shell reporting the total records, duplicates and warnings might be a mysql specific feature. As I did not see this additional information with [SequelAce](https://sequel-ace.com/), which only reports the number of rows affected in the GUI. If you know why this is the case, please do let me know!

## Postgres

Postgres remains consistent and only returns the total number of rows `inserted + updated` each time independent of how many rows were already in the DB. For example:

(The query to return number of rows affected is slightly more involved)

```sql
dhanush@/tmp:localdb> WITH
   affected_rows as (
     INSERT into
       users (username)
     VALUES
       ('johnwick'),
       ('spiderman'),
       ('batman'),
       ('wonderwoman'),
       ('catwoman'),
       ('superman') ON CONFLICT (username) do
     UPDATE
     SET
       login_count = users.login_count + 1 RETURNING *
   )
 SELECT
   COUNT(*)
 FROM
   affected_rows;
+-------+
| count |
|-------|
| 6     |
+-------+
SELECT 1
Time: 0.006s
```

## Conclusion

If you're using the rows affected to determine how many rows were affected and
need this information in your business logic for whatever reason, please do not
rely on the output of `select row_count()` in MySQL. Instead, possibly have
additional application logic to detect the changes.


## Acknowledgments

Thank you to [Swanand](https://x.com/_swanand/) for encouraging me to write
about the bulk upsert use case and for reviewing the post and suggesting edits.
