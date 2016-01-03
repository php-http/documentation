PHP-HTTP: standardized HTTP for PHP
===================================

.. image:: assets/img/plugefant.png
    :align: right
    :width: 120px
    :alt: HTTPlug Logo

PHP-HTTP is the next step in standardizing HTTP interaction for PHP packages.
It builds on top of PSR-7_, which defines interfaces for HTTP requests and
responses. PSR-7 does not describe, however, the way you should create requests
or send them. PHP-HTTP aims to fill that gap by offering an HTTP client
interface: HTTPlug.

PHP-HTTP has three goals:

1. Encourage package developers to depend on the simple HTTPlug interface
   instead of concrete HTTP clients.

2. Provide good quality HTTP-related packages to the PHP community.

3. Over time, make HTTPlug a PSR so that clients will directly implement the
   HTTPlug interface and our adapters are no longer needed.

HTTPlug
-------

HTTPlug abstracts from HTTP clients written in PHP, offering a simple interface.
It also provides an implementation-independent plugin system to build pipelines
regardless of the HTTP client implementation used.

HTTPlug allows you to write reusable libraries and applications that need
an HTTP client without binding to a specific implementation.
When all packages used in an application only specify HTTPlug,
the application developers can choose the client that best fits their project
and use the same client with all packages.

There are clients implementing one of the HTTPlug interfaces directly,
and adapter packages that implement the interface and forward the calls to HTTP
clients not implementing the interface.

Get started by reading our :doc:`tutorial </httplug/tutorial>`.

Packages
--------

PHP-HTTP offers several packages:

+-----------------+-------------------------------------------------------------+------------------------+
| Type            | Description                                                 | Namespace              |
+=================+=============================================================+========================+
| Clients         | HTTP clients: Socket, cURL and others                       | ``Http\Client\[Name]`` |
+-----------------+-------------------------------------------------------------+------------------------+
| Client adapters | Adapters for other clients: Guzzle, React and others        | ``Http\Adapter\[Name]``|
+-----------------+-------------------------------------------------------------+------------------------+
| Plugins         | Implementation-independent authentication, cookies and more | ``Http\Plugin\[Name]`` |
+-----------------+-------------------------------------------------------------+------------------------+

The future
----------

HTTPlug, as a working example of an HTTP client interface, can serve as a basis
for discussion around a future HTTP client PSR.

.. toctree::
    :hidden:
    :maxdepth: 3

    PHP-HTTP <self>

.. toctree::
   :hidden:

   HTTPlug <httplug>

.. toctree::
   :hidden:

   clients
   plugins/index

.. toctree::
   :hidden:
   :caption: Components

   message
   components/client-common
   components/adapter-integration-tests
   components/promise
   discovery

.. toctree::
   :hidden:
   :caption: ---------

   development/index.rst
