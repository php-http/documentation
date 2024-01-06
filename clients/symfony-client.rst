Symfony Client
==============

An HTTPlug implementation from the `Symfony HttpClient`_.

Installation
------------

To install the Symfony client, run:

.. code-block:: bash

    $ composer require symfony/http-client

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
