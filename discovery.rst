Discovery
=========

The discovery service allows to find and use installed resources.

Consumers of libraries using discovery still need to make sure they install one of the implementations.
Discovery can only find installed code, not fetch code from other sources.

Currently available discovery services:

- HTTP Client Discovery
- HTTP Async Client Discovery
- PSR-7 Message Factory Discovery
- PSR-7 URI Factory Discovery
- PSR-7 Stream Factory Discovery

The principle is always the same: you call the static ``find`` method on the discovery service if no explicit
implementation was specified. The discovery service will try to locate a suitable implementation.
If no implementation is found, an ``Http\Discovery\Exception\NotFoundException`` is thrown.

.. versionadded:: 0.9
    The exception ``Http\Discovery\NotFoundException`` has been moved to ``Http\Discovery\Exception\NotFoundException``.

Discovery is simply a convenience wrapper to statically access clients and factories for when
Dependency Injection is not an option. Discovery is useful in libraries that want to offer
zero-configuration services relying on the virtual packages.


Strategies
----------

The package supports multiple discovery strategies and comes with two out-of-the-box:

- A built-in strategy supporting the HTTPlug adapters, clients and factories (including Guzzle, Diactoros and Slim Framework)
- A strategy supporting the beta version of `Puli`_

Strategies provide candidates of a type which gets evaluated by the discovery service.
When it finds the best candidate, it caches it and stops looking in further strategies.


Installation
------------

.. code-block:: bash

    $ composer require php-http/discovery


Using Puli
^^^^^^^^^^

`Puli`_ is a first class citizen, but completely optional strategy in discovery.
It provides better flexibility than the built-in strategy, but requires more configuration.

There are two kinds of installation:

- In an application
- In a reusable library (for development)

In both cases you have to install the discovery package itself and set up Puli.
The easiest way is installing the composer-plugin which automatically configures
all the composer packages to act as Puli modules.

For applications, simply do:

.. code-block:: bash

    $ composer require puli/composer-plugin


If you need the composer-plugin for development or testing in a reusable library,
make it a development dependency instead:

.. code-block:: bash

    $ composer require --dev puli/composer-plugin

All of our packages provide Puli resources too, so if Puli is installed, discovery will use it as the primary strategy
and fall back to the built-in list.

Read more about setting up Puli in their `official documentation`_.


Common Errors
-------------

Could not find resource using any discovery strategy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you get an error saying "*Could not find resource using any discovery strategy.*" it means that all the
discovery [#strategies]_ have failed. The cause of this is probably because you have not installed message factories
and/or a PSR-7 implementation. See the :doc:`user documentation <httplug/users>`.

To resolve this you may run

.. code-block:: bash

        $ composer require php-http/curl-client guzzlehttp/psr7 php-http/message

Puli Factory is not available
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you get an error that says "*Puli Factory is not available*", it means that you have failed to install Puli.
Using Puli is optional and you will be able to use common clients and message factories without Puli
(:doc:`see how <httplug/users>`). If you want to use Puli, make sure to install the latest version of
``puli/composer-plugin``.

.. code-block:: bash

        $ composer require puli/composer-plugin

No factories found
^^^^^^^^^^^^^^^^^^

The error "*No message factories found. To use Guzzle, Diactoros or Slim Framework factories install php-http/message
and the chosen message implementation.*"
tells you that no discovery strategy could not find an installed implementation of PSR-7 and/or factories for that
implementation. You need to install those libraries. If you want to use Guzzle you may run:

.. code-block:: bash

        $ composer require php-http/message guzzlehttp/psr7

No HTTPlug clients found
^^^^^^^^^^^^^^^^^^^^^^^^

The error "No HTTPlug clients found. Make sure to install a package providing 'php-http/client-implementation'*" says that
we cant find a client. See our :doc:`list of clients <clients>` and install one of them.

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
        protected $httpClient;

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
        protected $httpAsyncClient;

        /**
         * @param HttpAsyncClient|null $httpAsyncClient Client to do HTTP requests, if not set, auto discovery will be used to find an asynchronous client.
         */
        public function __construct(HttpAsyncClient $httpAsyncClient = null)
        {
            $this->httpAsyncClient = $httpAsyncClient ?: HttpAsyncClientDiscovery::find();
        }
    }

PSR-7 Message Factory Discovery
-------------------------------

This type of discovery finds a :ref:`message-factory` for a PSR-7_ Message
implementation::

    use Http\Message\MessageFactory;
    use Http\Discovery\MessageFactoryDiscovery;

    class MyClass
    {
        /**
         * @var MessageFactory
         */
        protected $messageFactory;

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

This type of discovery finds a URI factory for a PSR-7_ URI implementation::

    use Http\Message\UriFactory;
    use Http\Discovery\UriFactoryDiscovery;

    class MyClass
    {
        /**
         * @var UriFactory
         */
        protected $uriFactory;

        /**
         * @param UriFactory|null $uriFactory to create UriInterface instances from strings.
         */
        public function __construct(UriFactory $uriFactory = null)
        {
            $this->uriFactory = $uriFactory ?: UriFactoryDiscovery::find();
        }
    }

Integrating your own implementation with the discovery mechanism using Puli
---------------------------------------------------------------------------

If you use `Puli`_ you can easily make your own HTTP Client or Message Factory discoverable:
you have to configure it as a Puli resource (`binding`_ in Puli terminology).

A binding must have a type, called `binding-type`_. All of our interfaces are registered as binding types.

For example: a client ``Http\Client\MyClient`` should be bind to ``Http\Client\HttpClient``

Puli uses a ``puli.json`` file for configuration (placed in the package root).
Use the CLI tool for configuring bindings. It is necessary, because each binding must have a unique identifier.
Read more in Puli's documentation (`Providing Resources`_).

.. _`Puli`: http://puli.io
.. _official documentation: http://docs.puli.io/en/latest
.. _`binding`: http://docs.puli.io/en/latest/glossary.html#glossary-binding
.. _`binding-type`: http://docs.puli.io/en/latest/glossary.html#glossary-binding-type
.. _Providing Resources: http://docs.puli.io/en/latest/discovery/providing-resources.html
