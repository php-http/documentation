cURL Client
===========

This client uses `cURL PHP extension <http://php.net/curl>`_.

Installation
------------

To install the cURL client, run:

.. code-block:: bash

    $ composer require php-http/curl-client

.. include:: includes/install-message-factory.inc

.. include:: includes/install-discovery.inc

Usage
-----

The cURL client needs a :ref:`message factory <message-factory>` and a
:ref:`stream factory <stream-factory>` in order to to work. You can either specify the factory
explicitly::

    use Http\Client\Curl\Client;
    use Http\Message\MessageFactory\DiactorosMessageFactory;
    use Http\Message\StreamFactory\DiactorosStreamFactory;

    $client = new Client(new DiactorosMessageFactory(), new DiactorosStreamFactory());

Or you can use :doc:`../discovery`::

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

The following options can not be changed in the set up. Most of them are to be provided with the
request instead:

    * CURLOPT_CUSTOMREQUEST
    * CURLOPT_FOLLOWLOCATION
    * CURLOPT_HEADER
    * CURLOPT_HTTP_VERSION
    * CURLOPT_HTTPHEADER
    * CURLOPT_NOBODY
    * CURLOPT_POSTFIELDS
    * CURLOPT_RETURNTRANSFER
    * CURLOPT_URL
    * CURLOPT_USERPWD

.. include:: includes/further-reading-sync.inc
