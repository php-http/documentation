HTTPlug: HTTP client abstraction
================================

HTTPlug allows you to write reusable libraries and applications that need
an HTTP client without binding to a specific implementation.
When all packages used in an application only specify HTTPlug,
the application developers can choose the client that best fits their project
and use the same client with all packages.

The client interfaces
---------------------

HTTPlug defines two HTTP client interfaces that we kept as simple as possible:

* ``HttpClient`` defines a ``sendRequest`` method that sends a PSR-7
  ``RequestInterface`` and either returns a PSR-7 ``ResponseInterface`` or
  throws an exception that implements ``Http\Client\Exception``.

* ``HttpAsyncClient`` defines a ``sendAsyncRequest`` method that sends a request
  asynchronously and always returns a ``Http\Client\Promise``.
  See :doc:`../components/promise` for more information.

Implementations
---------------

PHP-HTTP offers two types of clients that implement the above interfaces:

1. Standalone clients that directly implement the interfaces.

   Examples: :doc:`/clients/curl-client` and :doc:`/clients/socket-client`.

2. Adapters that wrap existing HTTP client, such as Guzzle. These adapters act
   as a bridge between the HTTPlug interfaces and the clients that do not (yet)
   implement these interfaces.

   Examples: :doc:`/clients/guzzle6-adapter` and :doc:`/clients/react-adapter`.

.. note::

    Ideally, all HTTP client libraries out there will implement the HTTPlug
    interfaces. At that point, our adapters will no longer be necessary.

Usage
-----

There are two main use cases for HTTPlug:

* Usage in an application that executes HTTP requests (see :doc:`tutorial` and :doc:`../integrations/index`);
* Usage in a reusable package that executes HTTP requests (see :doc:`library-developers`).

History
-------

This project has been started by `Eric Geloen`_ as `Ivory Http Adapter`_. It
never made it to a stable release, but it relied on PSR-7 which was not stable
either that time. Because of the constantly changing PSR-7, Eric had to rewrite
the library over and over again (at least the message handling part, which in
most cases affected every adapter as well).

In 2015, a decision has been made to move the library to its own organization,
so PHP-HTTP was born.

See :doc:`migrating` for a guide how to migrate your code from the Ivory
adapter.

.. _`Eric Geloen`: https://github.com/egeloen
.. _`Ivory Http Adapter`: https://github.com/egeloen/ivory-http-adapter
