# PHP-HTTP and HTTPlug

**This is the documentation for the HTTPlug client abstraction and the other PHP-HTTP components.**


In the past few years HTTP related actions got much more attention. We took a long way from `file_get_contents` to
[PSR-7](http://www.php-fig.org/psr/psr-7/). We still felt that something was missing: and PHP HTTP was born.

We aim to provide good quality, HTTP related packages to the PHP community. Our main product is
[HTTPlug](http://httplug.io), but we also have other smaller packages to make using HTTP more convenient.


## HTTPlug

[PSR-7](http://www.php-fig.org/psr/psr-7/) defines interfaces for HTTP requests and responses.
However, it does not define how to create a request or how to send a request.
HTTPlug abstracts from HTTP clients written in PHP, offering a simple interface.
It also provides an implementation-independent plugin system to build pipelines regardless of the
HTTP client implementation used.

HTTPlug allows you to write reusable libraries and applications that need
an HTTP client without binding to a specific implementation.
When all packages used in an application only specify HTTPlug,
the application developers can chose the client that fits best for their
project and use the same client with all packages.

There are clients implementing one of the HTTPlug interfaces directly,
and adapter packages that implement the interface and forward the calls to HTTP clients not implementing the interface.


Read our [tutorial](httplug/tutorial.md).


# PHP-HTTP Components

As explained above, PHP HTTP has room for anything that is connected to HTTP and PHP.
Although [HTTPlug](http://httplug.io) is considered to be our "main product", we have other components as well.

See the list of components in the left side navigation.
