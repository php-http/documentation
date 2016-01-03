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

Usage in an application
-----------------------

When writing an application, you need to require a concrete implementation.

See :doc:`virtual-package` for more information on the topic of working with HTTPlug implementations.

Installation in a reusable package
----------------------------------

In many cases, packages are designed to be reused from the very beginning.
For example, API clients are usually used in other packages/applications, not on their own.

Reusable packages should **not rely on a concrete implementation** (like Guzzle 6),
but only require any implementation of HTTPlug. HTTPlug uses the concept of virtual packages.
Instead of depending on only the interfaces, which would be missing an implementation,
or depending on one concrete implementation, you should depend on the virtual package ``php-http/client-implementation``
or ``php-http/async-client-implementation``. There is no package with that name,
but all clients and adapters implementing HTTPlug declare that they provide one of this virtual package or both.

You need to edit the ``composer.json`` of your package to add the virtual package.
For development (installing the package standalone, running tests),
add a concrete implementation in the ``require-dev`` section to make the project installable:

.. code-block:: json

    {
        "require": {
            "php-http/client-implementation": "^1.0"
        },
        "require-dev": {
            "php-http/guzzle6-adapter": "^1.0"
        },
    }

For extra convenience, you can use the :doc:`/discovery` system to free the user of your
package from having to instantiate the client.
You should however always accept injecting the client instance to allow the user to configure the client as needed.
You can find an example in the :doc:`/discovery` documentation.

Users of your package will have to select a concrete adapter in their project to make your package installable.
Best point them to the :doc:`virtual-package` page.

To be able to send requests, you should not depend on a specific PSR-7 implementation,
but use the :ref:`message-factory` system.

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
