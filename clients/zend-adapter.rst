Zend Adapter (deprecated)
=========================

An HTTPlug adapter for the Zend HTTP client.

Zend framework meanwhile has been renamed to Laminas, and the client is no
longer maintained.

This adapter only implements the PHP-HTTP synchronous interface. This interface
has been superseded by PSR-18, which the `Laminas Diactoros`_ implements
directly.

Installation
------------

To install the Zend adapter, which will also install Zend itself (if it was
not yet included in your project), run:

.. code-block:: bash

    $ composer require php-http/zend-adapter

.. _Laminas Diactoros: https://docs.laminas.dev/laminas-diactoros/
