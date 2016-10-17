.. _message-factory:
.. _stream-factory:

HTTP Factories
==============

**Factory interfaces for PSR-7 HTTP objects.**

Rationale
---------

While it should be possible to use every PSR-7 aware HTTP client with any
request, URI and stream implementation, instantiating objects explicitly would
still  tie the code to a specific implementation. If each reusable library is
tied to a specific message implementation, an application could end up
installing several message implementations. The factories move instantiation
out of the library code, further decoupling libraries from implementation.

The FIG was pretty straightforward by NOT putting any construction logic into PSR-7.
The ``MessageFactory`` aims to provide an easy way to construct messages.

Factories
---------

The `php-http/message-factory` package defines interfaces for PSR-7 factories including:

- ``RequestFactory``
- ``ResponseFactory``
- ``MessageFactory`` (combination of request and response factories)
- ``StreamFactory``
- ``UriFactory``

Implementations of the interfaces above for `Diactoros`_, `Guzzle PSR-7`_ and the `Slim Framework`_ can be found in ``php-http/message``.

Usage
-----

Instantiate the factories in your bootstrap code or use discovery for them.
Inject the factories into the rest of your code to limit the implementation
choice to the bootstrapping code::

    // ApiClient.php

    use Http\Message\RequestFactory;
    use Http\Message\StreamFactory;
    use Http\Message\UriFactory;

    class ApiClient
    {
        /**
         * @var RequestFactory
         */
        private $requestFactory;

        /**
         * @var StreamFactory
         */
        private $streamFactory;

        /**
         * @var UriFactory
         */
        private $uriFactory;

        public function __construct(
            RequestFactory $requestFactory,
            StreamFactory $streamFactory,
            UriFactory $uriFactory
        ) {
            $this->requestFactory = $requestFactory;
            $this->streamFactory = $streamFactory;
            $this->uriFactory = $uriFactory;
        }

        public function doStuff()
        {
            $request = $this->requestFactory->createRequest('GET', 'http://httplug.io');
            $stream = $this->streamFactory->createStream('stream content');
            $uri = $this->UriFactory->createUri('http://httplug.io');
            ...
        }
    }

The bootstrapping code could look like this::

    // bootstrap.php
    use Http\Message\MessageFactory\DiactorosMessageFactory;
    use Http\Message\StreamFactory\DiactorosStreamFactory;
    use Http\Message\UriFactory\DiactorosUriFactory;

    $apiClient = new ApiClient(
        new DiactorosMessageFactory(),
        new DiactorosStreamFactory(),
        new DiactorosUriFactory()
    );

You could also use :doc:`/discovery` to make the factory arguments optional and
automatically find an available factory in the client::

    // ApiClient.php

    use Http\Discovery\MessageFactoryDiscovery;
    use Http\Discovery\StreamFactoryDiscovery;
    use Http\Discovery\UriFactoryDiscovery;
    use Http\Message\RequestFactory;
    use Http\Message\StreamFactory;
    use Http\Message\UriFactory;

    class ApiClient
    {
        public function __construct(
            RequestFactory $requestFactory = null,
            StreamFactory $streamFactory = null,
            UriFactory $uriFactory = null
        ) {
            $this->requestFactory = $requestFactory ?: MessageFactoryDiscovery::find(),
            $this->streamFactory = $streamFactory ?: StreamFactoryDiscovery::find();
            $this->uriFactory = $uriFactory ?: UriFactoryDiscovery::find();;
        }

        ...
    }

.. hint::

    If you create requests only and no responses, use ``RequestFactory`` in the
    type hint, instead of the ``MessageFactory``. And vice versa if you create
    responses only.

Server Side Factories
---------------------

It would make sense to also provide factories for the server side constructs
``ServerRequestInterface`` and ``UploadedFileInterface``. We did not get around
to do that yet. Contributions are welcome if you want to define the
``ServerRequestFactory`` and ``UploadedFileFactory``.

.. _Diactoros: https://github.com/zendframework/zend-diactoros
.. _Guzzle PSR-7: https://github.com/guzzle/psr7
.. _Slim Framework: https://github.com/slimphp/Slim
