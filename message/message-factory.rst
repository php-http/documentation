.. _message-factory:
.. _stream-factory:

HTTP Factories (deprecated)
===========================

**Factory interfaces for PSR-7 HTTP objects.**

This package has been superseded by `PSR-17`_. Our HTTP-PHP factories have been
retired and the repository archived. The PHP-HTTP libraries switched to use the
PSR-17 factories. Please migrate your code to the PSR-17 factories too.

Rationale
---------

At the time of building this, PSR-17 did not yet exist. Read the documentation
of `PSR-17`_ to learn why a standard for factories is useful.

Factories
---------

The `php-http/message-factory` package defines interfaces for PSR-7 factories
including:

- ``RequestFactory``
- ``ResponseFactory``
- ``MessageFactory`` (combination of request and response factories)
- ``StreamFactory``
- ``UriFactory``

Implementations of the interfaces above for `Laminas Diactoros`_ (and its
abandoned predecessor `Zend Diactoros`_), `Guzzle PSR-7`_ and the
`Slim PSR-7`_ can be found in ``php-http/message``.

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
            $uri = $this->uriFactory->createUri('http://httplug.io');
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

.. _PSR-17: https://www.php-fig.org/psr/psr-17/
.. _Guzzle PSR-7: https://github.com/guzzle/psr7
.. _Laminas Diactoros: https://github.com/laminas/laminas-diactoros
.. _Slim PSR-7: https://github.com/slimphp/Slim-Psr7
.. _Zend Diactoros: https://github.com/zendframework/zend-diactoros
.. _Slim Framework: https://github.com/slimphp/Slim
