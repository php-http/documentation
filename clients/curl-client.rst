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

The cURL client needs a PSR-17 message factory and stream factory to work.
You can either specify the factory explicitly::

    use Http\Client\Curl\Client;
    use Http\Message\MessageFactory\DiactorosMessageFactory;
    use Http\Message\StreamFactory\DiactorosStreamFactory;

    $client = new Client(new DiactorosMessageFactory(), new DiactorosStreamFactory());

Or you can omit the parameters and let the client use :doc:`../discovery` to
determine a suitable factory::

    use Http\Client\Curl\Client;
    use Http\Discovery\MessageFactoryDiscovery;
    use Http\Discovery\StreamFactoryDiscovery;

    $client = new Client();

Configuring Client
------------------

You can use `cURL options <http://php.net/curl_setopt>`_ to configure Client::

    use Http\Client\Curl\Client;
    use Http\Discovery\MessageFactoryDiscovery;
    use Http\Discovery\StreamFactoryDiscovery;

    $options = [
        CURLOPT_CONNECTTIMEOUT => 10, // The number of seconds to wait while trying to connect.
    ];
    $client = new Client(null, null, $options);

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

.. include:: includes/further-reading-async.inc
