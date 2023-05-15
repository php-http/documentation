Guzzle5 Adapter (deprecated)
============================

An HTTPlug adapter for the `Guzzle 5 HTTP client`_.

This adapter only implements the PHP-HTTP synchronous interface. This interface
has been superseded by PSR-18.

Guzzle 5 is very old and `not maintained anymore`_. We recommend to upgrade to
Guzzle version 7.

Installation
------------

To install the Guzzle adapter, which will also install Guzzle itself (if it was
not yet included in your project), run:

.. code-block:: bash

    $ composer require php-http/guzzle5-adapter

Usage
-----

Begin by creating a Guzzle client, passing any configuration parameters you
like::

    use GuzzleHttp\Client as GuzzleClient;

    $config = [
        // Config params
    ];
    $guzzle = new GuzzleClient($config);

Then create the adapter::

    use Http\Adapter\Guzzle5\Client as GuzzleAdapter;
    use Http\Message\MessageFactory\GuzzleMessageFactory;

    $adapter = new GuzzleAdapter($guzzle, new GuzzleMessageFactory());

Or if you installed the :doc:`discovery </discovery>` layer::

    use Http\Adapter\Guzzle5\Client as GuzzleAdapter;

    $adapter = new GuzzleAdapter($guzzle);

.. warning::

    The message factory parameter is mandatory if the discovery layer is not installed.

.. include:: includes/further-reading-sync.inc

.. _Guzzle 5 HTTP client: http://docs.guzzlephp.org/en/5.3/
.. _not maintained anymore: https://github.com/guzzle/guzzle#version-guidance
