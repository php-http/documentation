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

   clients/guzzle5-adapter
   clients/guzzle6-adapter
   clients/react-adapter
