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
factory in order to to work::

    use Http\Client\Curl\Client;

    $client = new Client($messageFactory, $streamFactory);

Using `php-http/message <https://packagist.org/packages/php-http/message>`_::

    use Http\Client\Curl\Client;
    use Http\Message\MessageFactory\DiactorosMessageFactory;
    use Http\Message\StreamFactory\DiactorosStreamFactory;

    $client = new Client(new DiactorosMessageFactory(), new DiactorosStreamFactory());

Using `php-http/discovery <https://packagist.org/packages/php-http/discovery>`_::

    use Http\Client\Curl\Client;
    use Http\Discovery\MessageFactoryDiscovery;
    use Http\Discovery\StreamFactoryDiscovery;

    $client = new Client(MessageFactoryDiscovery::find(), StreamFactoryDiscovery::find());

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
