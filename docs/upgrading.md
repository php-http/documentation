# Upgrading to PHP HTTP Adapter from Ivory Http Adapter

There are some major changes between the two library. This guide will help you upgrading your code.


## New vendor

The new organization name is **PHP HTTP**. This suggests that while our main product is the HTTP Adapter project, we are not limited to it. We plan to collect any kind of HTTP related packages written in PHP.

Our composer vendor name is `php-http`, our vendor namespace is `Http`.


## Package separation

One of the biggest changes changes is the package separation. One big package is separated ito several smaller one.

These packages are:

### adapter

**Interfaces for HTTP Adapters**

Namespace: `Http\Adapter`
Repository: https://github.com/php-http/adapter


### *-adapter

**Each adapter is separated into its own package. This allows to make requirements to the underlying HTTP Client libraries.**

Namespace: `Http\Adapter`
Repository: https://github.com/php-http/*-adapter


### client

**Interfaces for HTTP Clients**

Namespace: `Http\Client`
Repository: https://github.com/php-http/client


### helper

**Helper classes for HTTP content**

Namespace: `Http\Helper`
Repository: https://github.com/php-http/helper


### discovery

**Discovery service to find installed resources (like adapters)**

Namespace: `Http\Discovery`
Repository: https://github.com/php-http/discovery
Documentation: http://php-http.readthedocs.org/en/latest/discovery/


## Removed HTTP methods from adapter

In the Ivory package there are two interfaces:

- Ivory\HttpAdapter\PsrHttpAdapter
- Ivory\HttpAdapter\HttpAdapter

These has been transformed into:

- Http\Adapter\HttpAdapter
- Http\Client\HttpClient

Every adapter in the Ivory package implemented both interfaces. In the new packages only the PSR-7 request acceptor methods are implelented (which can be found in `Http\Adapter\HttpAdapter`).

To preserve some functionality, we created a special adapter called `adapter-client`. This adapter implements both interfaces and accepts an instance of `Http\Adapter\HttpAdapter`.
