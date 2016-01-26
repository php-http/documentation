cURL Client
===========

This client uses `cURL PHP extension <http://php.net/curl>`_.

Installation
------------

To install the cURL client, run:

.. code-block:: bash

    $ composer require php-http/curl-client

Usage
-----

The cURL client needs a :ref:`message <message-factory>` and a :ref:`stream <message-factory>`
factories in order to to work::

    use Http\Client\Curl\Client;

    $client = new Client($messageFactory, $streamFactory);

Using `php-http/discovery <https://packagist.org/packages/php-http/discovery>`_::

    use Http\Client\Curl\Client;
    use Http\Discovery\MessageFactoryDiscovery;
    use Http\Discovery\StreamFactoryDiscovery;

    $messageFactory = MessageFactoryDiscovery::find();
    $streamFactory = StreamFactoryDiscovery::find();
    $client = new Client($messageFactory, $streamFactory);


Using `mekras/httplug-diactoros-bridge <https://packagist.org/packages/mekras/httplug-diactoros-bridge>`_::

    use Http\Client\Curl\Client;
    use Mekras\HttplugDiactorosBridge\DiactorosMessageFactory;
    use Mekras\HttplugDiactorosBridge\DiactorosStreamFactory;

    $client = new Client(new DiactorosMessageFactory(), new DiactorosStreamFactory());


Configuring client
------------------

You can use `cURL options <http://php.net/curl_setopt>`_ to configure Client::

    use Http\Client\Curl\Client;
    use Http\Discovery\MessageFactoryDiscovery;
    use Http\Discovery\StreamFactoryDiscovery;

    $options = [
        CURLOPT_CONNECTTIMEOUT => 10, // The number of seconds to wait while trying to connect.
        CURLOPT_SSL_VERIFYPEER => false // Stop cURL from verifying the peer's certificate
    ];
    $client = new Client(MessageFactoryDiscovery::find(), StreamFactoryDiscovery::find(), $options);

These options can not be used:

    * CURLOPT_CUSTOMREQUEST
    * CURLOPT_FOLLOWLOCATION
    * CURLOPT_HEADER
    * CURLOPT_HTTP_VERSION
    * CURLOPT_HTTPHEADER
    * CURLOPT_NOBODY
    * CURLOPT_POSTFIELDS
    * CURLOPT_RETURNTRANSFER
    * CURLOPT_URL

These options can be overwritten by Client:

    * CURLOPT_USERPWD

.. include:: includes/further-reading-sync.inc
