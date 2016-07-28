Clients & Adapters
==================

There are two types of libraries you can use to send HTTP messages; clients and adapters. A client implements the
``HttpClient`` and/or the ``HttpAsyncClient`` interfaces directly. A client adapter is a class implementing the
interface and forward the calls to a HTTP client not implementing the interface. (See `Adapter pattern`_ on Wikipedia).

.. note::

    All clients and adapters comply with `Liskov substitution principle`_ which means that you can easily change one
    for another without any side effects.

.. _`Adapter pattern`: https://en.wikipedia.org/wiki/Adapter_pattern
.. _`Liskov substitution principle`: https://en.wikipedia.org/wiki/Liskov_substitution_principle


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
without forcing a specific implementation. For HTTPlug, the virtual packages are called `php-http/client-implementation`_
and `php-http/async-client-implementation`_.

There is no library registered with those names. However, all client implementations including client adapters for
HTTPlug use the ``provide`` section to tell composer that they do provide the client-implementation.

.. _`php-http/client-implementation`: https://packagist.org/providers/php-http/client-implementation
.. _`php-http/async-client-implementation`: https://packagist.org/providers/php-http/async-client-implementation:
