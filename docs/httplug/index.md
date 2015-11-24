# HTTPlug HTTP client abstraction

HTTPlug is an abstraction for HTTP clients. There are two main use cases:

1. Usage in a project/application
2. Usage in a reusable package

In both cases, the `Http\Client\HttpClient` provides a `sendRequest` method to send a PSR-7 `RequestInterface`
and returns a PSR-7 `ResponseInterface`or throws an exception that implements `Http\Client\Exception`.

There is also the `Http\Client\HttpAsyncClient` which provides the `sendAsyncRequest` method to send
a request asynchronously and returns a `Http\Client\Promise`.

The promise allows to specify handlers for a PSR-7 `ResponseInterface`
or an exception that implements `Http\Client\Exception`.


<p class="text-warning">
    Contract for the `Http\Client\Promise` is temporary until
    [PSR is released](https://groups.google.com/forum/?fromgroups#!topic/php-fig/wzQWpLvNSjs).
    Once it is out, we will use this PSR in the main client and deprecate the old contract.
</p>


See the [tutorial](tutorial.md) for a concrete example.


## HTTPlug implementations

HTTPlug implementations typically are either HTTP clients of their own, or adapters wrapping existing clients
like Guzzle 6. In the latter case, they will depend on the required client implementation,
so you only need to require the adapter and not the actual client.


There are two kind of implementations:

 - [php-http/client-implementation](https://packagist.org/providers/php-http/client-implementation):
 the synchronous implementation that waits for the response / error before returning from the `sendRequest` method.
 - [php-http/async-client-implementation](https://packagist.org/providers/php-http/async-client-implementation):
 the asynchronous implementation that immediately returns a `Http\Client\Promise`,
 allowing to send several requests in parallel and handling responses later.

Check links above for the full list of implementations.


## Usage in an application

When writing an application, you need to require a concrete
[implementation](https://packagist.org/providers/php-http/client-implementation).

See [virtual package](virtual-package.md) for more information on the topic of working with HTTPlug implementations.


## Installation in a reusable package

In many cases, packages are designed to be reused from the very beginning.
For example, API clients are usually used in other packages/applications, not on their own.

Reusable packages should **not rely on a concrete implementation** (like Guzzle 6),
but only require any implementation of HTTPlug. HTTPlug uses the concept of virtual packages.
Instead of depending on only the interfaces, which would be missing an implementation,
or depending on one concrete implementation, you should depend on the virtual package `php-http/client-implementation`
or `php-http/async-client-implementation`. There is no package with that name,
but all clients and adapters implementing HTTPlug declare that they provide one of this virtual package or both.

You need to edit the `composer.json` of your package to add the virtual package.
For development (installing the package standalone, running tests),
add a concrete implementation in the `require-dev` section to make the project installable:

``` json
...
"require": {
    "php-http/client-implementation": "^1.0"
},
"require-dev": {
    "php-http/guzzle6-adapter": "^1.0"
},
...
```

For extra convenience, you can use the [Discovery Component](/components/discovery) system to free the user of your
package from having to instantiate the client.
You should however always accept injecting the client instance to allow the user to configure the client as needed.
You can find an example in the [Discovery Component](/components/discovery) documentation.

Users of your package will have to select a concrete adapter in their project to make your package installable.
Best point them to the [virtual package](virtual-package.md) howto page.

To be able to send requests, you should not depend on a specific PSR-7 implementation,
but use the [Message Factory Component](/components/message-factory) system.


### Framework Integration

HTTPlug can be used in any PHP based project.
Nonetheless, we provide particular integration for some popular frameworks:

- [HttplugBundle](https://github.com/php-http/HttplugBundle/) integration with the Symfony framework.


## History

This project has been started by [Eric Geloen](https://github.com/egeloen) as
Ivory Http Adapter](https://github.com/egeloen/ivory-http-adapter). It never made it to a stable release,
but it relied on PSR-7 which was not stable either that time. Because of the constantly changing PSR-7,
Eric had to rewrite the library over and over again (at least the message handling part,
which in most cases affected every adapter as well).

In 2015, a decision has been made to move the library to it's own organization, so PHP HTTP was born.

See [migrating](migrating.md) for a guide how to migrate your code from the Ivory adapter to HTTPlug.
