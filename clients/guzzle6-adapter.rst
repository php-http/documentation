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

To create a Guzzle6 adapter you should use the `createWithConfig()` function. It will let you to pass Guzzle configuration
to the client::

    use Http\Adapter\Guzzle6\Client as GuzzleAdapter;

    $config = [
        'timeout' => 2,
        'handler' => //...
        // ...
    ];
    $adapter = GuzzleAdapter::createWithConfig($config);

.. note::

    If you want even more control over your Guzzle object, you may give a Guzzle client as first argument to the adapter's
    constructor::

        use GuzzleHttp\Client as GuzzleClient;
        use Http\Adapter\Guzzle6\Client as GuzzleAdapter;

        $config = ['timeout' => 5];
        // ...
        $guzzle = new GuzzleClient($config);
        // ...
        $adapter = new GuzzleAdapter($guzzle);

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
