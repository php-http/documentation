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

If you need control on the React instances, you can inject them during
initialization::

    use Http\Adapter\React\Client;

    $systemDnsConfig = React\Dns\Config\Config::loadSystemConfigBlocking();
    if (!$config->nameservers) {
        $config->nameservers[] = '8.8.8.8';
    }

    $dnsResolverFactory = new React\Dns\Resolver\Factory();
    $dnsResolver = $factory->create($config);

    $connector = new React\Socket\Connector([
        'dns' => $dnsResolver,
    ]);
    $browser = new React\Http\Browser($connector);

    $adapter = new Client($browser);

You can also use a ``ReactFactory`` in order to initialize React instances::

    use Http\Adapter\React\ReactFactory;

    $reactHttp = ReactFactory::buildHttpClient();

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

Note that since v4 calling `wait` on `Http\Promise\Promise` is expected to run inside a fiber::

    use function React\Async\async;

    async(static function () {
        // Returns a Http\Promise\Promise
        $promise = $adapter->sendAsyncRequest(request);

        // Returns a Psr\Http\Message\ResponseInterface
        $response = $promise->wait();
    })();

.. include:: includes/further-reading-async.inc

.. _React HTTP client: https://github.com/reactphp/http-client
