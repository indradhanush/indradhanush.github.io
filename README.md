# README

[![blog-build-deployment](https://github.com/indradhanush/indradhanush.github.io/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/indradhanush/indradhanush.github.io/actions/workflows/pages/pages-build-deployment)

This is my github pages blog powered by Jekyll and the [So Simple Theme](https://github.com/mmistakes/so-simple-theme)

### Setting up

Ensure that `ruby` is installed and gem install bundler -v 1.16.1

# Install blog dependencies locally at vendor/bundle under project root.
bundle config set path vendor/bundle

# If setting this up for the first time in a while, run:
 
```
bundle update

bundler install
```

### Running the blog locally

`bundler exec jekyll serve --watch`

### Local configuration

Set the following in [_config.yml](_config.yml) to make links work
locally instead of redirecting to live website:

```
url: http://127.0.0.1:4000
```
