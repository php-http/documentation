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

3. Over time, make HTTPlug a PHP Standards Recommendation (PSR) so that clients
   will directly implement the HTTPlug interface and our adapters are no longer
   needed.

HTTPlug
-------

HTTPlug abstracts from HTTP clients written in PHP, offering a simple interface.
It also provides an implementation-independent plugin system to build pipelines
regardless of the HTTP client implementation used.

Read more about :doc:`HTTPlug </httplug/introduction>`.

They use us
```````````

.. image:: https://avatars3.githubusercontent.com/u/5303359?v=3&s=100
    :align: left
    :width: 10%
    :target: https://github.com/geocoder-php/Geocoder
    :alt: Geocoder

.. image:: https://avatars0.githubusercontent.com/u/447686?v=3&s=100
    :align: left
    :width: 10%
    :target: https://github.com/mailgun/mailgun-php
    :alt: Mailgun

.. image:: https://avatars2.githubusercontent.com/u/529709?v=3&s=100
    :align: left
    :width: 10%
    :target: https://github.com/FriendsOfSymfony/FOSHttpCache
    :alt: FOSHttpCache

.. image:: https://avatars3.githubusercontent.com/u/202732?v=3&s=100
    :align: left
    :width: 10%
    :target: https://github.com/KnpLabs/php-github-api
    :alt: KnpLabs

.. image:: http://httplug.io/assets/img/logo/swap.png
    :align: left
    :width: 10%
    :target: https://github.com/florianv/swap
    :alt: Swap

.. image:: https://avatars3.githubusercontent.com/u/9406778?v=3&s=100
    :align: left
    :width: 10%
    :target: https://github.com/SparkPost/php-sparkpost
    :alt: SparkPost

.. image:: https://avatars3.githubusercontent.com/u/551057?v=3&s=100
    :align: left
    :width: 10%
    :target: https://github.com/Nexmo/nexmo-php
    :alt: Nexmo

|clearfloat|

Packages
--------

PHP-HTTP offers several packages:

=============== =========================================================== ====================================
Type            Description                                                 Namespace
=============== =========================================================== ====================================
Clients         HTTP clients: Socket, cURL and others                       ``Http\Client\[Name]``
Client adapters Adapters for other clients: Guzzle, React and others        ``Http\Adapter\[Name]``
Plugins         Implementation-independent authentication, cookies and more ``Http\Client\Common\Plugin\[Name]``
=============== =========================================================== ====================================

Read more about :doc:`clients and adapters <clients>` and :doc:`plugins <plugins/index>`.

The future
----------

HTTPlug, as a working example of an HTTP client interface, can serve as a basis
for discussion around a future HTTP client PSR.

.. toctree::
    :hidden:

    PHP-HTTP <self>

.. toctree::
   :hidden:
   :caption: HTTPlug
   :maxdepth: 4

   Introduction <httplug/introduction>
   Usage <httplug/usage>
   Exceptions <httplug/exceptions>
   Tutorial <httplug/tutorial>
   Migrating <httplug/migrating>

   clients
   plugins/index

   integrations/index

   Backwards compatibility <httplug/backwards-compatibility>

.. toctree::
   :hidden:
   :caption: Components

   message
   components/client-common
   components/adapter-integration-tests
   components/promise
   discovery
   components/multipart-stream-builder

.. toctree::
   :hidden:
   :caption: ---------

   development/index.rst

.. |clearfloat|  raw:: html

    <div style="clear:left"></div>
