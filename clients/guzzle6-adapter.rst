Guzzle 6 Adapter
================

An HTTPlug adapter for the `Guzzle 6 HTTP client`_.

Installation
------------

To install the Guzzle adapter, which will also install Guzzle itself (if it was
not yet included in your project), run:

.. code-block:: bash

    $ composer require php-http/guzzle6-adapter

Usage
-----

Begin by creating a Guzzle client, passing any configuration parameters you
like::

    use GuzzleHttp\Client as GuzzleClient;

    $config = [
        'verify' => false,
        'timeout' => 2,
        'handler' => //...
        // ...
    ];
    $guzzle = new GuzzleClient($config);

Then create the adapter::

    use Http\Adapter\Guzzle6\Client as GuzzleAdapter;

    $adapter = new GuzzleAdapter($guzzle);

.. note::

    You can also use the quicker `createWithConfig()` function::

        use Http\Adapter\Guzzle6\Client as GuzzleAdapter;

        $config = ['verify' => false ];
        $adapter = GuzzleAdapter::createWithConfig($config);

And use it to send synchronous requests::

    use GuzzleHttp\Psr7\Request;

    $request = new Request('GET', 'http://httpbin.org');

    // Returns a Psr\Http\Message\ResponseInterface
    $response = $adapter->sendRequest($request);

Or send asynchronous ones::

    use GuzzleHttp\Psr7\Request;

    $request = new Request('GET', 'http://httpbin.org');

    // Returns a Http\Promise\Promise
    $promise = $adapter->sendAsyncRequest(request);


.. include:: includes/further-reading-async.inc

.. _Guzzle 6 HTTP client: http://docs.guzzlephp.org/
