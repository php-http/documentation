Symfony Client
==============

The Symfony HTTP client provides a ``HttplugClient`` class that implements the ``Http\Client\HttpAsyncClient``.
Until Symfony 5.4, it also implemented the ``Http\Client\HttpClient``, newer versions implement the PSR-18
``HttpClientInterface`` instead.

Installation
------------

The Symfony client does not depend on HTTPlug, but the ``HttplugClient`` does. To use the Symfony client with HTTPlug,
you need to install both the client and HTTPlug with:

.. code-block:: bash

    $ composer require symfony/http-client php-http/httplug

This client does not come with a PSR-7 implementation out of the box. If you do
not require one, `discovery <../discovery>` will install `Nyholm PSR-7`_. If
you do not allow the composer plugin of the ``php-http/discovery`` component,
you need to install a PSR-7 implementation manually:

.. code-block:: bash

    $ composer require nyholm/psr7

Usage
-----
.. code-block:: php

    use Symfony\Component\HttpClient\HttplugClient;

    $symfonyClient = new HttplugClient();

.. note::

    Check the official `Symfony HttpClient`_ documentation for more details.

.. _Symfony HttpClient: https://symfony.com/doc/current/components/http_client.html#httplug

.. _Nyholm PSR-7: https://github.com/Nyholm/psr7/
