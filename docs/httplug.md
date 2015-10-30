# Httplug HTTP client abstraction

Httplug is an abstraction for HTTP clients. There are two main use cases:

1. Usage in a project
2. Usage in a reusable package

In both cases, the client provides a `sendRequest` method to send a PSR-7 `RequestInterface` and returns a PSR-7 `ResponseInterface` or throws an exception that implements `Http\Client\Exception`.

See the [tutorial](tutorial.md) for a concrete example.


## Httplug implementations

Httplug implementations typically are either HTTP clients of their own, or they are adapters wrapping existing clients like Guzzle 6. In the latter case, they will depend on the required client implementation, so you only need to require the adapter and not the actual client.

See [packagist](https://packagist.org/providers/php-http/client-implementation) for the full list of implementations.

Note: Until Httplug 1.0 becomes stable, we will focus on the Guzzle6 adapter.

## Usage in a project

When writing an application, you need to require a concrete [client implementation](https://packagist.org/providers/php-http/client-implementation). The client will in turn depend on `php-http/httplug`, thus you do not need to duplicate the dependency on `php-http/httplug` in your composer.json file. However, if your code depends on a minimal version of Httplug, specify it to have composer report problems rather than the application failing at some point.

Choose the client based on your personal preferences or dependencies of your project. If your preferred client has no Httplug adapter, submit one.


## Installation in a reusable package

In many cases, packages are designed to be reused from the very beginning. For example, API clients are usually used in other packages/applications, not on their own.

In these cases, they should **not rely on a concrete implementation** (like Guzzle 6), but only require any implementation of Httplug. Httplug uses the concept of virtual packages. Instead of depending on only the interfaces, which would be missing an implementation, or depending on one concrete implementation, you should depend on the virtual package `php-http/client-implementation`. There is no package with that name, but all clients and adapters implementing Httplug declare that they provide this virtual package.

You need to edit the `composer.json` of your package to add the virtual package. For development (installing the package standalone, running tests), add a concrete implementation in the `require-dev` section to make the project installable:

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

For extra convenience, you can use the [Discovery](discovery.md) system to free the user of your package from having to instantiate the client. You should however always accept injecting the client instance to allow the user to configure the client as needed.

Users of your package will have to select a concrete adapter in their project to make your package installable. Best point them to the [virtual package](virtual-package.md) howto page.

To be able to send requests, you should not depend on a specific PSR-7 implementation, but use the [message factory](message-factory.md) system.
