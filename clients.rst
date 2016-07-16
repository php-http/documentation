Clients & Adapters
==================

There are clients implementing one of the HTTPlug interfaces directly,
and adapter packages that implement the interface and forward the calls to HTTP clients not implementing the interface.

.. _`php-http/client-implementation`: https://packagist.org/providers/php-http/client-implementation
.. _`php-http/async-client-implementation`: https://packagist.org/providers/php-http/async-client-implementation:


Clients:

.. toctree::

   clients/curl-client
   clients/socket-client
   clients/mock-client

Client adapters:

.. toctree::

   clients/buzz-adapter
   clients/guzzle5-adapter
   clients/guzzle6-adapter
   clients/react-adapter

Composer Virtual Packages
-------------------------

Virtual packages are a way to specify the dependency on an implementation of an interface-only repository
without forcing a specific implementation. For HTTPlug, the virtual package is called ``php-http/client-implementation``.

There is no project registered with that name. However, all client implementations including client adapters for
HTTPlug use the ``provide`` section to tell composer that they do provide the client-implementation.


