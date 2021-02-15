# README

This is my github pages blog powered by Jekyll and the [So Simple Theme](https://github.com/mmistakes/so-simple-theme)

### Setting up

Ensure that `ruby` is installed and run:

```
gem install bundler -v 1.16.1

# Install blog dependencies locally at vendor/bundle under project root.
bundler install --path vendor/bundle
```

### Running the blog locally

`bundler exec jekyll serve --watch`



### Local configuration

Set the following in [_config.yml](_config.yml) to make links work
locally instead of redirecting to live website:

```
url: http://127.0.0.1:4000
```
