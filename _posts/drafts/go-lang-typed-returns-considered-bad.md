```
func removeSSHKeys(unixUsername string) (err error) {
	unixUser, err := user.Lookup(unixUsername)
	if err != nil {
		return
	}

	sshDir := unixUser.HomeDir + "/.ssh"
	path := sshDir + "/authorized_keys.d"

	_, err = os.Stat(path)
	if !os.IsNotExist(err) {
		err = os.RemoveAll(path)
		if err != nil {
			log.WithError(err).Errorf("Error in deleting %s", path)
			return
		}

		err = os.MkdirAll(path, os.ModeDir)
		if err != nil {
			log.WithError(err).Errorf("Error in re-creating directory %s", path)
			return
		}

		path = sshDir + "/authorized_keys"
		err = os.Remove(path)
		if err != nil {
			log.WithError(err).Errorf("Error in deleting %s", path)
			return
		}
	}
	return
}
```

### More unintive code

```
func CreateUnixGroup() (created bool, err error) {

	_, err = user.LookupGroup(unixGroupName)
	if err != nil {
		cmd := exec.Command("groupadd", "-p", `"*"`, unixGroupName)
		_, err = cmd.Output()
		if err != nil {
			return
		}

		created = true
	}

	return
}
```

### One example when it makes sense

```
func RunActions(iamSvc *iam.IAM, iamUser *iam.User) (unixUsername string, err error) {
	unixUsername = strings.Split(*iamUser.UserName, "@")[0]

	err = addToUnixGroup(unixUsername)
	if err != nil {
		log.WithError(err).Errorf("Error in adding %s to %s", unixUsername, unixGroupName)
		return
	}
	err = removeSSHKeys(unixUsername)
	if err != nil {
		log.WithError(err).Errorf("Error in removing ssh keys for user %s", unixUsername)
		return
	}

	err = addSSHKeysFromAws(iamSvc, *iamUser.UserName, unixUsername)
	if err != nil {
		log.WithError(err).Errorf("Error in adding ssh keys from aws for user %s", unixUsername)
		return
	}

	return
}
```
