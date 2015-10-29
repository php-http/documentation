# PHP-HTTP Httplug

**This is the documentation for the Httplug HTTP client abstraction and the other PHP-HTTP components.**

[PSR-7](http://www.php-fig.org/psr/psr-7/) defines interfaces for HTTP requests and responses. However, it does not define how to create a request or how to send a request. Httplug abstracts from HTTP clients written in PHP, offering a simple interface. It also brings a implementation-independent plugin system to build pipelines regardless of the HTTP client implementation used. The message factory provides an implementation independent way to instantiate `Psr\RequestInterface` objects.

Httplug allows you to write reusable libraries and applications that need a HTTP client without binding to a specific implementation. When all packages used in an application only specify Httplug, the application developers can chose the client that fits best for their project and use the same client with all packages.

There are clients implementing the Httplug `Http\Client\HttpClient` interface directly, and adapter packages that implement the interface and forward the calls to HTTP clients not implementing the interface.


## Getting started

Read our [tutorial](tutorial.md).


## Overview

PHP-HTTP is separated into several packages:

- [Httplug](httplug.md), the HTTP client abstraction to send PSR-7 requests without binding to a specific implementation;
- [Message Factory](message-factory.md) to create PSR-7 requests without binding to a specific implementation; 
- [Discovery](discovery.md) to automatically locate a suitable Httplug implementation and PSR-7 message and URI factories.
- [Utilities](utils.md) convenience tools to simplify working with Httplug in your applications.

See [package overview](package-overview.md) for a complete list.


## History

This project has been started by [Eric Geloen](https://github.com/egeloen) as [Ivory Http Adapter](https://github.com/egeloen/ivory-http-adapter). It never made it to a stable release, but it relied on PSR-7 which was not stable either that time. Because of the constantly changing PSR-7, Eric had to rewrite the library over and over again (at least the message handling part, which in most cases affected every adapter as well).

In 2015, a decision has been made to move the library to it's own organization, so PHP HTTP was born.

See [migrating](migrating.md) for a guide how to migrate your code from the Ivory adapter to Httplug.
