Guzzle5 Adapter
===============

An HTTPlug adapter for the `Guzzle 5 HTTP client`_.

Installation
------------

To install the Guzzle adapter, which will also install Guzzle itself (if it was
not yet included in your project), run:

.. code-block:: bash

    $ composer require php-http/guzzle5-adapter

.. include:: includes/install-message-factory.inc

.. include:: includes/install-discovery.inc

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
