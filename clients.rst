Clients & Adapters
==================

There are two types of libraries you can use to send HTTP messages; clients and adapters. A client implements the
``HttpClient`` and/or the ``HttpAsyncClient`` interfaces directly. A client adapter is a class implementing the
interface and forwarding the calls to an HTTP client not implementing the interface. (See `Adapter pattern`_ on Wikipedia).

.. note::

    All clients and adapters comply with `Liskov substitution principle`_ which means that you can easily change one
    for another without any side effects.



.. csv-table::
   :header: "Name", "Type", "Links", "Stats"
   :widths: 32, 15, 15, 38

   "``clients/curl-client``", "Client", ":doc:`Docs </clients/curl-client>`, `Repo <https://github.com/php-http/curl-client>`__", "|curl_version| |curl_downloads| "
   "``clients/socket-client``", "Client", ":doc:`Docs </clients/socket-client>`, `Repo <https://github.com/php-http/socket-client>`__", "|socket_version| |socket_downloads| "
   "``clients/mock-client``", "Client", ":doc:`Docs </clients/mock-client>`, `Repo <https://github.com/php-http/mock-client>`__", "|mock_version| |mock_downloads| "
   "``clients/buzz-adapter``", "Adapter", ":doc:`Docs </clients/buzz-adapter>`, `Repo <https://github.com/php-http/buzz-adapter>`__", "|buzz_version| |buzz_downloads| "
   "``clients/cakephp-adapter``", "Adapter", ":doc:`Docs </clients/cakephp-adapter>`, `Repo <https://github.com/php-http/cakephp-adapter>`__", "|cakephp_version| |cakephp_downloads| "
   "``clients/guzzle5-adapter``", "Adapter", ":doc:`Docs </clients/guzzle5-adapter>`, `Repo <https://github.com/php-http/guzzle5-adapter>`__", "|guzzle5_version| |guzzle5_downloads| "
   "``clients/guzzle6-adapter``", "Adapter", ":doc:`Docs </clients/guzzle6-adapter>`, `Repo <https://github.com/php-http/guzzle6-adapter>`__", "|guzzle6_version| |guzzle6_downloads| "
   "``clients/react-adapter``", "Adapter", ":doc:`Docs </clients/react-adapter>`, `Repo <https://github.com/php-http/react-adapter>`__", "|react_version| |react_downloads| "
   "``clients/zend-adapter``", "Adapter", ":doc:`Docs </clients/zend-adapter>`, `Repo <https://github.com/php-http/zend-adapter>`__", "|zend_version| |zend_downloads| "

Composer Virtual Packages
-------------------------

Virtual packages are a way to specify the dependency on an implementation of an interface-only repository
without forcing a specific implementation. For HTTPlug, the virtual packages are called `php-http/client-implementation`_
and `php-http/async-client-implementation`_.

There is no library registered with those names. However, all client implementations (including client adapters) for
HTTPlug use the ``provide`` section to tell composer that they do provide the client-implementation.

.. toctree::
   :hidden:

   clients/curl-client
   clients/socket-client
   clients/mock-client
   clients/buzz-adapter
   clients/cakephp-adapter
   clients/guzzle5-adapter
   clients/guzzle6-adapter
   clients/react-adapter
   clients/zend-adapter

.. _`php-http/client-implementation`: https://packagist.org/providers/php-http/client-implementation
.. _`php-http/async-client-implementation`: https://packagist.org/providers/php-http/async-client-implementation
.. _`Adapter pattern`: https://en.wikipedia.org/wiki/Adapter_pattern
.. _`Liskov substitution principle`: https://en.wikipedia.org/wiki/Liskov_substitution_principle


.. |curl_downloads| image:: https://img.shields.io/packagist/dt/php-http/curl-client.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/curl-client
   :alt: Total Downloads
.. |curl_version| image:: https://img.shields.io/github/release/php-http/curl-client.svg?style=flat-square
   :target: https://github.com/php-http/curl-client/releases
   :alt: Latest Version

.. |socket_downloads| image:: https://img.shields.io/packagist/dt/php-http/socket-client.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/socket-client
   :alt: Total Downloads
.. |socket_version| image:: https://img.shields.io/github/release/php-http/socket-client.svg?style=flat-square
   :target: https://github.com/php-http/socket-client/releases
   :alt: Latest Version

.. |mock_downloads| image:: https://img.shields.io/packagist/dt/php-http/mock-client.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/mock-client
   :alt: Total Downloads
.. |mock_version| image:: https://img.shields.io/github/release/php-http/mock-client.svg?style=flat-square
   :target: https://github.com/php-http/mock-client/releases
   :alt: Latest Version

.. |buzz_downloads| image:: https://img.shields.io/packagist/dt/php-http/buzz-adapter.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/buzz-adapter
   :alt: Total Downloads
.. |buzz_version| image:: https://img.shields.io/github/release/php-http/buzz-adapter.svg?style=flat-square
   :target: https://github.com/php-http/buzz-adapter/releases
   :alt: Latest Version

.. |cakephp_downloads| image:: https://img.shields.io/packagist/dt/php-http/cakephp-adapter.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/cakephp-adapter
   :alt: Total Downloads
.. |cakephp_version| image:: https://img.shields.io/github/release/php-http/cakephp-adapter.svg?style=flat-square
   :target: https://github.com/php-http/cakephp-adapter/releases
   :alt: Latest Version

.. |guzzle5_downloads| image:: https://img.shields.io/packagist/dt/php-http/guzzle5-adapter.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/guzzle5-adapter
   :alt: Total Downloads
.. |guzzle5_version| image:: https://img.shields.io/github/release/php-http/guzzle5-adapter.svg?style=flat-square
   :target: https://github.com/php-http/guzzle5-adapter/releases
   :alt: Latest Version

.. |guzzle6_downloads| image:: https://img.shields.io/packagist/dt/php-http/guzzle6-adapter.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/guzzle6-adapter
   :alt: Total Downloads
.. |guzzle6_version| image:: https://img.shields.io/github/release/php-http/guzzle6-adapter.svg?style=flat-square
   :target: https://github.com/php-http/guzzle6-adapter/releases
   :alt: Latest Version

.. |react_downloads| image:: https://img.shields.io/packagist/dt/php-http/react-adapter.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/react-adapter
   :alt: Total Downloads
.. |react_version| image:: https://img.shields.io/github/release/php-http/react-adapter.svg?style=flat-square
   :target: https://github.com/php-http/react-adapter/releases
   :alt: Latest Version

.. |zend_downloads| image:: https://img.shields.io/packagist/dt/php-http/zend-adapter.svg?style=flat-square
   :target: https://packagist.org/packages/php-http/zend-adapter
   :alt: Total Downloads
.. |zend_version| image:: https://img.shields.io/github/release/php-http/zend-adapter.svg?style=flat-square
   :target: https://github.com/php-http/zend-adapter/releases
   :alt: Latest Version
