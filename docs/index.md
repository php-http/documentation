# HTTP Adapter

**This is the documentation for HTTP Adapter and it's software components.**


## History

This project has been started by [Eric Geloen](https://github.com/egeloen) as [Ivory Http Adapter](https://github.com/egeloen/ivory-http-adapter). It never made it to be really stable, but it relied on PSR-7 which was not stable either that time.


## Getting started

HTTP Adapter is separated into several components:

- Adapter contract
- Client contract
- Adapter client
- Adapter implementations
- Helpers


### Installation

There are many strategies how adapters and other components can be installed. However they are the same in one thing: they can be installed via [Composer](http://getcomposer.org/):

``` bash
$ composer require php-http/adapter
```


#### Installation in a reusable package

In many cases packages are designed to be reused from the very beginning. For example API clients are usually used in other packages/applications, not on their own.

In these cases it is always a good idea not to rely on a concrete implementation (like Guzzle), but only require some implementation of an HTTP Adapter. With Composer, it is possible:

``` json
{
    "require": {
        "php-http/adapter-implementation": "^1.0"
    }
}
```

This allows the end user to choose a concrete implementation when installs the package. Of course, during development a concrete implementation is needed:


``` json
{
    "require-dev": {
        "php-http/guzzle6-adapter": "^1.0"
    }
}
```


Another good practice if the package works out-of-the-box, no or only minimal configuration is needed. While not requiring a concrete implementation is great, it also means that the end user would have to always inject the installed adapter (which is the right, but not a convenient solution). To solve this, there is a discovery components which finds and resolves other installed components:

``` json
{
    "require": {
        "php-http/discovery": "^1.0"
    }
}
```

Read more about it in the [Discovery](discovery.md) part.


#### Installation in an end user package

When installing in an application or a non-reusable package, using a virtual package doesn't really make sense. However there are a few things which should be taken into consideration before choosing an adapter:

- It is possible that some other package already has an HTTP Client requirement. It doesn't worth to install more than one HTTP Clients.
- Some adapters support paralell requests, some only emulate them. If paralell requests are needed, use one which supports it.

Installing an implementation is easy:

``` bash
$ composer require php-http/*-adapter
```

_Replace * with any supported adapter name_
