HTTPlug: HTTP client abstraction
================================

HTTPlug is an abstraction for HTTP clients. There are two main use cases:

1. Usage in a project/application
2. Usage in a reusable package

In both cases, the ``Http\Client\HttpClient`` provides a ``sendRequest`` method
to send a PSR-7 ``RequestInterface`` and returns a PSR-7 ``ResponseInterface``
or throws an exception that implements ``Http\Client\Exception``.

There is also the ``Http\Client\HttpAsyncClient`` which provides the
``sendAsyncRequest`` method to send a request asynchronously and returns a
``Http\Client\Promise``.

The promise allows to specify handlers for a PSR-7 ``ResponseInterface``
or an exception that implements ``Http\Client\Exception``.

See the :doc:`tutorial </httplug/tutorial>` for a concrete example.


.. toctree::

   Introduction <httplug/introduction>
   Tutorial <httplug/tutorial>
   Migrating <httplug/migrating>
   Virtual Package <httplug/virtual-package>

