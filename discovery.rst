Discovery
=========

The discovery service allows to find and use installed resources.

Consumers of libraries using discovery still need to make sure they install one of the implementations.
Discovery can only find installed code, not fetch code from other sources.

Currently available discovery services:

- HTTP Client Discovery
- HTTP Async Client Discovery
- PSR-17 Factory Discovery
- PSR-18 HTTP Client Discovery
- Mock Client Discovery (not enabled by default)
- PSR-7 Message Factory Discovery (deprecated)
- PSR-7 URI Factory Discovery (deprecated)
- PSR-7 Stream Factory Discovery (deprecated)

The principle is always the same: you call the static ``find`` method on the discovery service if no explicit
implementation was specified. The discovery service will try to locate a suitable implementation.
If no implementation is found, an ``Http\Discovery\Exception\NotFoundException`` is thrown.

.. versionadded:: 0.9
    The exception ``Http\Discovery\NotFoundException`` has been moved to ``Http\Discovery\Exception\NotFoundException``.

Discovery is simply a convenience wrapper to statically access clients and factories for when
Dependency Injection is not an option. Discovery is useful in libraries that want to offer
zero-configuration services relying on the virtual packages.

.. _discovery-strategies:

Strategies
----------

The package supports multiple discovery strategies and comes with two out-of-the-box:

- A built-in strategy supporting the HTTPlug adapters, clients and factories (including Symfony, Guzzle, Diactoros and Slim Framework)

Strategies provide candidates of a type which gets evaluated by the discovery service.
When it finds the best candidate, it caches it and stops looking in further strategies.


Installation
------------

.. code-block:: bash

    $ composer require php-http/discovery


Common Errors
-------------

Could not find resource using any discovery strategy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you get an error saying "*Could not find resource using any discovery strategy.*"
it means that all the discovery :ref:`strategies <discovery-strategies>` have failed.
Most likely, your project is missing the message factories and/or a PRS-7 implementation.
See the :doc:`user documentation <httplug/users>`.

To resolve this you may run

.. code-block:: bash

        $ composer require php-http/curl-client guzzlehttp/psr7 php-http/message

No factories found
^^^^^^^^^^^^^^^^^^

The error "*No message factories found. To use Guzzle, Diactoros or Slim Framework
factories install php-http/message and the chosen message implementation.*" tells
you that no discovery strategy could find an installed implementation of PSR-7
and/or factories for that implementation. You need to install those libraries.
If you want to use Guzzle you may run:

.. code-block:: bash

        $ composer require php-http/message guzzlehttp/psr7

No HTTPlug clients found
^^^^^^^^^^^^^^^^^^^^^^^^

The error "*No HTTPlug clients found. Make sure to install a package providing
'php-http/client-implementation'*" says that we cannot find a client. See our
:doc:`list of clients <clients>` and install one of them.

.. code-block:: bash

        $ composer require php-http/curl-client

HTTP Client Discovery
---------------------

This type of discovery finds an HTTP Client implementation::

    use Http\Client\HttpClient;
    use Http\Discovery\HttpClientDiscovery;

    class MyClass
    {
        /**
         * @var HttpClient
         */
        private $httpClient;

        /**
         * @param HttpClient|null $httpClient Client to do HTTP requests, if not set, auto discovery will be used to find a HTTP client.
         */
        public function __construct(HttpClient $httpClient = null)
        {
            $this->httpClient = $httpClient ?: HttpClientDiscovery::find();
        }
    }

HTTP Asynchronous Client Discovery
----------------------------------

This type of discovery finds a HTTP asynchronous Client implementation::

    use Http\Client\HttpAsyncClient;
    use Http\Discovery\HttpAsyncClientDiscovery;

    class MyClass
    {
        /**
         * @var HttpAsyncClient
         */
        private $httpAsyncClient;

        /**
         * @param HttpAsyncClient|null $httpAsyncClient Client to do HTTP requests, if not set, auto discovery will be used to find an asynchronous client.
         */
        public function __construct(HttpAsyncClient $httpAsyncClient = null)
        {
            $this->httpAsyncClient = $httpAsyncClient ?: HttpAsyncClientDiscovery::find();
        }
    }

PSR-17 Factory Discovery
------------------------

This type of discovery finds a factory for a PSR-17_ implementation::

    use Psr\Http\Message\RequestFactoryInterface;
    use Psr\Http\Message\ResponseFactoryInterface;
    use Http\Discovery\Psr17FactoryDiscovery;

    class MyClass
    {
        /**
         * @var RequestFactoryInterface
         */
        private $requestFactory;

        /**
         * @var ResponseFactoryInterface
         */
        private $responseFactory;

        /**
         * @var ServerRequestFactoryInterface
         */
        private $serverRequestFactory;

        /**
         * @var StreamFactoryInterface
         */
        private $streamFactory;

        /**
         * @var UploadedFileFactoryInterface
         */
        private $uploadedFileFactory;

        /**
         * @var UriFactoryInterface
         */
        private $uriFactory;

        public function __construct(
            RequestFactoryInterface $requestFactory = null,
            ResponseFactoryInterface $responseFactory = null,
            ServerRequestFactoryInterface $serverRequestFactory = null,
            StreamFactoryInterface $streamFactory = null,
            UploadedFileFactoryInterface $uploadedFileFactory = null,
            UriFactoryInterface = $uriFactoryInterface = null
        ) {
            $this->requestFactory = $requestFactory ?: Psr17FactoryDiscovery::findRequestFactory();
            $this->responseFactory = $responseFactory ?: Psr17FactoryDiscovery::findResponseFactory();
            $this->serverRequestFactory = $serverRequestFactory ?: Psr17FactoryDiscovery::findServerRequestFactory();
            $this->streamFactory = $streamFactory ?: Psr17FactoryDiscovery::findStreamFactory();
            $this->uploadedFileFactory = $uploadedFileFactory ?: Psr17FactoryDiscovery::findUploadedFileFactory();
            $this->uriFactory = $uriFactory ?: Psr17FactoryDiscovery::findUriFactory();
        }
    }

PSR-17 Factory
--------------

The package also provides an ``Http\Discovery\Psr17Factory`` class that can be instantiated
to get a generic PSR-17 factory::

    use Http\Discovery\Psr17Factory;

    $factory = new Psr17Factory();

    // use any PSR-17 methods, e.g.
    $request = $factory->createRequest();

Internally, this class relies on the concrete PSR-17 factories that are installed in your project
and can use discovery to find implementations if you do not specify them in the constructor.

``Psr17Factory`` provides two additional methods that allow creating
server requests or URI objects from the PHP super-globals::

    $serverRequest = $factory->createServerRequestFromGlobals();
    $uri = $factory->createUriFromGlobals();

.. versionadded:: 1.15
   The ``Psr17Factory`` class is available since version 1.15.

PSR-18 Client Discovery
-----------------------

This type of discovery finds a PSR-18_ HTTP Client implementation::

    use Psr\Http\Client\ClientInterface;
    use Http\Discovery\Psr18ClientDiscovery;

    class MyClass
    {
        /**
         * @var ClientInterface
         */
        private $httpClient;

        public function __construct(ClientInterface $httpClient = null)
        {
            $this->httpClient = $httpClient ?: Psr18ClientDiscovery::find();
        }
    }

PSR-7 Message Factory Discovery
-------------------------------

.. versionadded:: 1.6
    This is deprecated and will be removed in 2.0. Consider using PSR-17 Factory Discovery.

This type of discovery finds a :ref:`message-factory` for a PSR-7_ Message
implementation::

    use Http\Message\MessageFactory;
    use Http\Discovery\MessageFactoryDiscovery;

    class MyClass
    {
        /**
         * @var MessageFactory
         */
        private $messageFactory;

        /**
         * @param MessageFactory|null $messageFactory to create PSR-7 requests.
         */
        public function __construct(MessageFactory $messageFactory = null)
        {
            $this->messageFactory = $messageFactory ?: MessageFactoryDiscovery::find();
        }
    }

PSR-7 URI Factory Discovery
---------------------------

.. versionadded:: 1.6
    This is deprecated and will be removed in 2.0. Consider using PSR-17 Factory Discovery.

This type of discovery finds a URI factory for a PSR-7_ URI implementation::

    use Http\Message\UriFactory;
    use Http\Discovery\UriFactoryDiscovery;

    class MyClass
    {
        /**
         * @var UriFactory
         */
        private $uriFactory;

        /**
         * @param UriFactory|null $uriFactory to create UriInterface instances from strings.
         */
        public function __construct(UriFactory $uriFactory = null)
        {
            $this->uriFactory = $uriFactory ?: UriFactoryDiscovery::find();
        }
    }

Mock Client Discovery
---------------------------

You may find yourself testing parts of your application that are dependent on an
HTTP Client using the Discovery Service, but do not necessarily need to perform
the request nor contain any special configuration. In this case, the
``Http\Mock\Client`` from the ``php-http/mock-client`` package is typically used
to fake requests and keep your tests nicely decoupled. However, for the best
stability in a production environment, the mock client is not set to be found
via the Discovery Service. Attempting to run a test which relies on discovery
and uses a mock client will result in an ``Http\Discovery\Exception\NotFoundException``.
Thankfully, Discovery gives us a Mock Client strategy that can be added straight
to the Discovery. Let's take a look::

    use MyCustomService;
    use Http\Mock\Client as MockClient;
    use Http\Discovery\HttpClientDiscovery;
    use Http\Discovery\Strategy\MockClientStrategy;

    class MyCustomServiceTest extends TestCase
    {
        public function setUp()
        {
            HttpClientDiscovery::prependStrategy(MockClientStrategy::class);

            $this->service = new MyCustomService;
        }

        public function testMyCustomServiceDoesSomething()
        {
            // Test...
        }
    }
    
In the example of a test class above, we have our ``MyCustomService`` which
relies on an HTTP Client implementation. We do not need to test that the actual
request our custom service makes is successful in this test class, so it makes
sense to use the Mock Client. However, we do want to make sure that our
dependency injection using the Discovery service properly works, as this is a
major feature of our service. By calling the ``HttpClientDiscovery``'s
``prependStrategy`` method and passing in the ``MockClientStrategy`` namespace,
we have now added the ability to discover the mock client and our tests will
work as desired.

It is important to note that you must explicitly enable the ``MockClientStrategy``
and that it is not used by the Discovery Service by default. It is simply
provided as a convenient option when writing tests.

.. _PSR-17: http://www.php-fig.org/psr/psr-17
