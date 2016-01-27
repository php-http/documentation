React Adapter
=============

An HTTPlug adapter for the `React Http client`_.

Installation
------------

Use Composer_ to install the React adapter. It will also install React as it's a
dependency.

.. code-block:: bash

    $ composer require php-http/react-adapter

.. include:: includes/install-message-factory.inc

.. include:: includes/install-discovery.inc

Usage
-----

The React client adapter needs a :ref:`message factory <message-factory>` in
order to to work::

    use Http\Adapter\React\Client;

    $client = new Client($messageFactory);

For simplicity, all required objects are instantiated automatically if not
explicitly specified:

:React\EventLoop\LoopInterface: The event loop used inside the React engine.
:React\HttpClient\Client: The HTTP client instance that must be adapted.

If you need more control on the React instances, you can inject them during
initialization::

    use Http\Adapter\React\Client;

    $eventLoop = React\EventLoop\Factory::create();
    $dnsResolverFactory = new React\Dns\Resolver\Factory();
    $dnsResolver = $dnsResolverFactory->createCached('8.8.8.8', $loop);

    $factory = new React\HttpClient\Factory();
    $reactHttp = $factory->create($loop, $dnsResolver);

    $adapter = new Client($messageFactory, $eventLoop, $reactHttp);

If you choose to inject a custom React HTTP client, you must inject the loop
used during its construction. But if you already use an EventLoop inside your
code, you can inject only this object.

You can also use a ``ReactFactory`` in order to initialize React instances::

    use Http\Adapter\React\ReactFactory;

    $eventLoop = ReactFactory::buildEventLoop();
    $reactHttp = ReactFactory::buildHttpClient($eventLoop);

Then you can use the adapter to send synchronous requests::

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

.. _React HTTP client: https://github.com/reactphp/http-client
