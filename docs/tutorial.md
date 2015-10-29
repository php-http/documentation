# Httplug tutorial

This tutorial should give you an idea how to use Httplug in your project. Httplug has two main use cases:

1. Usage in your project;
2. Usage in a reusable package.

This tutorial will start with the first use case and then explain the special considerations to take into account when building a reusable package.

We use (composer)[https://getcomposer.org] for dependency management. Install it if you don't have it yet.

## Setting up the project

``` bash
mkdir httplug-tutorial
cd httplug-tutorial
composer init
# specify your information as you want. say no to defining the dependencies interactively
composer require php-http/guzzle6-adapter
```

The last command will install Guzzle as well as the Guzzle Httplug adapter and the required interface repositories. We are now ready to start coding.

## Writing some simple code

Create a file `demo.php` in the root folder and write the following code:

``` php
<?php
require('vendor/autoload.php');

TODO: create client instance with discovery and do some requests
```

## Handling errors

TODO: explain how to handle exceptions, distinction between network exception and HttpException.

## Doing parallel requests

TODO explain sendRequests and how to work with BatchResult and BatchException


## Writing a reusable package

TODO: explain the virtual package 
