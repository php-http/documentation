Client Common
=============

The client-common package provides some useful tools for working with HTTPlug.
Include them in your project with composer:

.. code-block:: bash

    composer require php-http/client-common "^1.0"

HttpMethodsClient
-----------------

This client wraps the HttpClient and provides convenience methods for common HTTP requests like ``GET`` and ``POST``.
To be able to do that, it also wraps a message factory::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Discovery\MessageFactoryDiscovery

    $client = new HttpMethodsClient(
        HttpClientDiscovery::find(),
        MessageFactoryDiscovery::find()
    );

    $foo = $client->get('http://example.com/foo');
    $bar = $client->get('http://example.com/bar', ['accept-encoding' => 'application/json']);
    $post = $client->post('http://example.com/update', [], 'My post body');

BatchClient
-----------

This client wraps a HttpClient and extends it with the possibility to send an array of requests and to retrieve
their responses as a ``BatchResult``::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Discovery\MessageFactoryDiscovery;

    $messageFactory = MessageFactoryDiscovery::find();

    $requests = [
        $messageFactory->createRequest('GET', 'http://example.com/foo'),
        $messageFactory->createRequest('POST', 'http://example.com/update', [], 'My post body'),
    ];

    $client = new BatchClient(
        HttpClientDiscovery::find()
    );

    $batchResult = $client->sendRequests($requests);

The ``BatchResult`` itself is an object that contains responses for all requests sent.
It provides methods that give appropriate information based on a given request::

    $requests = [
        $messageFactory->createRequest('GET', 'http://example.com/foo'),
        $messageFactory->createRequest('POST', 'http://example.com/update', [], 'My post body'),
    ];

    $batchResult = $client->sendRequests($requests);

    if ($batchResult->hasResponses()) {
        $fooSuccessful = $batchResult->isSuccessful($requests[0]);
        $updateResponse = $batchResult->getResponseFor($request[1]);
    }

If one or more of the requests throw exceptions, they are added to the
``BatchResult`` and the ``BatchClient`` will ultimately throw a
``BatchException`` containing the ``BatchResult`` and therefore its exceptions::

    $requests = [
        $messageFactory->createRequest('GET', 'http://example.com/update'),
    ];

    try {
        $batchResult = $client->sendRequests($requests);
    } catch (BatchException $e) {
        var_dump($e->getResult()->getExceptions());
    }

PluginClient
------------

See :doc:`the documentation about plugins </plugins/introduction>`

HttpClientPool
--------------

The ``HttpClientPool`` allows to balance requests between a pool of ``HttpClient`` and/or ``HttpAsyncClient``.

The use cases are:

- Using a cluster (like an Elasticsearch service with multiple master nodes)
- Using fallback servers with the combination of the ``RetryPlugin`` (see :doc:`/plugins/retry`)

You can attach HTTP clients to this kind of client by using the ``addHttpClient`` method::

    use Http\Client\Common\HttpClientPool\LeastUsedClientPool;
    use Http\Discovery\HttpAsyncClientDiscovery;
    use Http\Discovery\HttpClientDiscovery;
    use Http\Discovery\MessageFactoryDiscovery;

    $messageFactory = MessageFactoryDiscovery::find();

    $httpClient = HttpClientDiscovery::find();
    $httpAsyncClient = HttpAsyncClientDiscovery::find();

    $httpClientPool = new LeastUsedClientPool();
    $httpClientPool->addHttpClient($httpClient);
    $httpClientPool->addHttpClient($httpAsyncClient);

    $httpClientPool->sendRequest($messageFactory->createRequest('GET', 'http://example.com/update'));

Clients added to the pool are decorated with the ``HttpClientPoolItem`` class unless they already are an instance of this class.
The pool item class lets the pool be aware of the number of requests currently being processed by that client.
It is also used to deactivate clients when they receive errors.
Deactivated clients can be reactivated after a certain amount of time, however, by default, they stay deactivated forever.
To enable the behavior, wrap the clients with the ``HttpClientPoolItem`` class yourself and specify the re-enable timeout::

    // Reactivate after 30 seconds
    $httpClientPool->addHttpClient(new HttpClientPoolItem($httpClient, 30));
    // Reactivate after each call
    $httpClientPool->addHttpClient(new HttpClientPoolItem($httpClient, 0));
    // Never reactivate the client (default)
    $httpClientPool->addHttpClient(new HttpClientPoolItem($httpClient, null));

``HttpClientPool`` is abstract. There are three concrete implementations with specific strategies on how to choose clients:

LeastUsedClientPool
*******************

``LeastUsedClientPool`` choose the client with the fewest requests in progress. As it sounds the best strategy for
sending a request on a pool of clients, this strategy has some limitations: :

- The counter is not shared between PHP process, so this strategy is not so useful in a web context, however it will make
  better sense in a PHP command line context.
- This pool only makes sense with asynchronous clients. If you use ``sendRequest``, the call is blocking, and the pool
  will only ever use the first client as its request count will be 0 once ``sendRequest`` finished.

A deactivated client will be removed for the pool until it is reactivated, if none are available it will throw a
``NotFoundHttpClientException``

RoundRobinClientPool
********************

``RoundRobinClientPool`` keeps an internal pointer on the pool. At each call the pointer is moved to the next client, if
the current client is disabled it will move to the next client, and if none are available it will throw a
``NotFoundHttpClientException``

The pointer is not shared across PHP processes, so for each new one it will always start on the first client.

RandomClientPool
****************

``RandomClientPool`` randomly choose an available client, throw a ``NotFoundHttpClientException`` if none are available.


HTTP Client Router
------------------

This client accepts pairs of clients and request matchers.
Every request is "routed" through the ``HttpClientRouter``, checked against the request matchers
and sent using the first matched client. If there is no matching client, an exception is thrown.

This allows a single client to be used for different requests.

In the following example we use the client router to access an API protected by basic auth
and also to download an image from a static host::

    use Http\Client\Common\HttpClientRouter;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\AuthenticationPlugin;
    use Http\Client\Common\Plugin\CachePlugin;
    use Http\Discovery\HttpClientDiscovery;
    use Http\Discovery\MessageFactoryDiscovery;
    use Http\Message\Authentication\BasicAuth;
    use Http\Message\RequestMatcher\RequestMatcher;

    $client = new HttpClientRouter();

    $requestMatcher = new RequestMatcher(null, 'api.example.com');
    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [new AuthenticationPlugin(new BasicAuth('user', 'password'))]
    );

    $client->addClient($pluginClient, $requestMatcher);


    $requestMatcher = new RequestMatcher(null, 'images.example.com');

    /** @var \Psr\Cache\CacheItemPoolInterface $pool */
    $pool = ...
    /** @var \Http\Message\StreamFactory $streamFactory */
    $streamFactory = ...

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [new CachePlugin($pool, $streamFactory)]
    );

    $client->addClient($pluginClient, $requestMatcher);


    $messageFactory = MessageFactoryDiscovery::find();

    // Get the user data
    $request = $messageFactory->createRequest('GET', 'https://api.example.com/user/1');

    $response = $client->send($request);
    $imagePath = json_decode((string) $response->getBody(), true)['image_path'];

    // Download the image and store it in cache
    $request = $messageFactory->createRequest('GET', 'https://images.example.com/user/'.$imagePath);

    $response = $client->send($request);

    file_put_contents('path/to/images/'.$imagePath, (string) $response->getBody());

    $request = $messageFactory->createRequest('GET', 'https://api2.example.com/user/1');

    // Throws an Http\Client\Exception\RequestException
    $client->send($request);


.. note::

    When you have small difference between the underlying clients (for example different credentials based on host)
    it's easier to use the ``RequestConditionalPlugin`` and the ``PluginClient``,
    but in that case the routing logic is integrated into the linear request flow
    which might make debugging harder.
