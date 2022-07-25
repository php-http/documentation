Symfony Bundle
==============

This bundle integrates HTTPlug with the Symfony framework. The bundle helps to
register services for all your clients and makes sure all the configuration is
in one place. The bundle also features a profiling plugin with information about
your requests.

This guide explains how to configure HTTPlug in the Symfony framework. See the
:doc:`../httplug/tutorial` for examples how to use HTTPlug in general.

Installation
````````````

HTTPlug works with any HTTP client implementation that provides PSR-18 or a
HTTPlug adapter. The flex recipe installs the `php-http` curl client. See
:doc:`../clients` for a list of clients known to work with the bundle.

You can find all available configuration at the
:doc:`full configuration </integrations/symfony-full-configuration>` page.

Using Symfony Flex
------------------

HttplugBundle has a `Symfony Flex`_ recipe that will set it up with default configuration:

.. code-block:: bash

    $ composer require php-http/httplug-bundle

Without Symfony Flex
--------------------

Install the HTTPlug bundle with composer and enable it in your AppKernel.php.

.. code-block:: bash

    $ composer require php-http/httplug-bundle [some-adapter?]

If you already added the HTTPlug client requirement to your project, then you
only need to add ``php-http/httplug-bundle``. Otherwise, you also need to
specify an HTTP client to use - see :doc:`../clients` for a list of available
clients.

Activate Bundle in Symfony 4 and newer
""""""""""""""""""""""""""""""""""""""

.. code-block:: php

    // config/bundles.php
    return [
        ...
        Http\HttplugBundle\HttplugBundle::class => ['all' => true],
   ];

Activate Bundle in Symfony 3
""""""""""""""""""""""""""""

.. code-block:: php

    // app/AppKernel.php
    public function registerBundles()
    {
        $bundles = [
            // ...
            new Http\HttplugBundle\HttplugBundle(),
        ];
    }

Usage
`````

.. code-block:: yaml

    httplug:
        plugins:
            logger: ~
        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins: ['httplug.plugin.logger']
                config:
                    timeout: 2

.. code-block:: php

    $request = $this->container->get('httplug.message_factory')->createRequest('GET', 'http://example.com');
    $response = $this->container->get('httplug.client.acme')->sendRequest($request);

Autowiring
----------

The first configured client is considered the "default" client. It is available
for `autowiring`_ both for ``HttpClient`` and ``HttpAsyncClient``. This can be
convenient to build your application.

However, if you configured several different clients and need to be sure that
the correct client is used in each service, it can also hide mistakes.
Therefore you can disable autowiring with a configuration option:

.. code-block:: yaml

    httplug:
        default_client_autowiring: false

When using this bundle with Symfony 5.3 or newer, you can use the `#[Target]` attribute to select a
client by name:

.. code-block:: php

    final class MyService
    {
        public function __construct(
            #[Target('acme')] HttpClient $client
        ) {}
    }

Web Debug Toolbar
`````````````````
.. image:: /assets/img/debug-toolbar.png
    :align: right
    :width: 380px

When using a client configured with ``HttplugBundle``, you will get debug
information in the web debug toolbar. It will tell you how many request were
made and how many of those that were successful or not. It will also show you
detailed information about each request.

The web profiler page will show you lots of information about the request and
also how different plugins changes the message. See example screen shots below.

.. image:: /assets/img/symfony-profiler/dashboard.png
    :width: 200px
    :align: left

.. image:: /assets/img/symfony-profiler/request-stack.png
    :width: 200px
    :align: left

.. image:: /assets/img/symfony-profiler/error-plugin-failure.png
    :width: 200px
    :align: left

|clearfloat|

The body of the HTTP messages is not captured by default because of performance
reasons. Turn this on by changing the ``captured_body_length`` configuration.

.. code-block:: yaml

    httplug:
        profiling:
            captured_body_length: 1000 # Capture the first 1000 chars of the HTTP body

You can set ``captured_body_length`` to ``null`` to avoid body limitation size.

.. code-block:: yaml

    httplug:
        profiling:
            captured_body_length: ~ # Avoid truncation of body content

The profiling is automatically turned off when ``kernel.debug = false``. You can
also disable the profiling by configuration.

.. code-block:: yaml

    httplug:
        profiling: false

You can configure the bundle to show debug information for clients found with
discovery. You may also force a specific client to be found when a third party
library is using discovery. The configuration below makes sure the client with
service id ``httplug.client.my_guzzle5`` is returned when calling
``HttpClientDiscovery::find()`` . It does also make sure to show debug info for
asynchronous clients.

.. note::

    Ideally, you would always use dependency injection and never rely on auto discovery to find a client.

.. code-block:: yaml

    httplug:
        clients:
            my_guzzle5:
                factory: 'httplug.factory.guzzle5'
        discovery:
            client: 'httplug.client.my_guzzle5'
            async_client: 'auto'

For normal clients, the auto discovery debug info is enabled by default. For
async clients, debug is not enabled by default to avoid errors when using the
bundle with a client that can not do async. To get debug information for async
clients, set ``discovery.async_client`` to ``'auto'`` or an explicit client.

You can turn off all interaction of the bundle with auto discovery by setting
the value of ``discovery.client`` to ``false``.

Discovery of Factory Classes
````````````````````````````

You need to specify all the factory classes for you client. The following
example shows how you configure factory classes using Guzzle:

.. code-block:: yaml

    httplug:
        classes:
            client: Http\Adapter\Guzzle6\Client
            message_factory: Http\Message\MessageFactory\GuzzleMessageFactory
            uri_factory: Http\Message\UriFactory\GuzzleUriFactory
            stream_factory: Http\Message\StreamFactory\GuzzleStreamFactory

Configure Clients
`````````````````

You can configure your clients with default options. These default values will
be specific to you client you are using. The clients are later registered as
services.

.. code-block:: yaml

    httplug:
        clients:
            my_guzzle5:
                factory: 'httplug.factory.guzzle5'
                config:
                    # These options are given to Guzzle without validation.
                    defaults:
                        # timeout if connection is not established after 4 seconds
                        timeout: 4
            acme:
                factory: 'httplug.factory.curl'
                config:
                    # timeout if connection is not established after 4 seconds
                    CURLOPT_CONNECTTIMEOUT: 4
                    # throttle sending data if more than ~ 1MB / second
                    CURLOPT_MAX_SEND_SPEED_LARGE: 1000000

.. code-block:: php

    $httpClient = $this->container->get('httplug.client.my_guzzle5');
    $httpClient = $this->container->get('httplug.client.acme');

    // will be the same as ``httplug.client.my_guzzle5``
    $httpClient = $this->container->get('httplug.client');

The bundle has client factory services that you can use to build your client.
If you need a very custom made client you could create your own factory service
implementing ``Http\HttplugBundle\ClientFactory\ClientFactory``. The built-in
services are:

* ``httplug.factory.curl``
* ``httplug.factory.buzz``
* ``httplug.factory.guzzle5``
* ``httplug.factory.guzzle6``
* ``httplug.factory.react``
* ``httplug.factory.socket``
* ``httplug.factory.mock`` (Install ``php-http/mock-client`` first)

.. note::

    .. versionadded:: 1.10

        If you already have a client service registered you can skip using the ``factory``
        and use the ``service`` key instead.

        .. code-block:: yaml

            httplug:
                clients:
                    my_client:
                        service: 'my_custom_client_service'

    .. versionadded:: 1.17

        All configured clients are tagged with ``'httplug.client'`` (the value of the constant ``Http\HttplugBundle\DependencyInjection\HttplugExtension::HTTPLUG_CLIENT_TAG``),
        so they can be easily retrieved. This is useful for functional tests, where one might want to replace every
        configured client with a mock client, so they can be retrieved and configured later

        .. code-block:: php

            use Http\HttplugBundle\DependencyInjection\HttplugExtension;
            use Http\Mock\Client;
            use Symfony\Component\DependencyInjection\ContainerBuilder;

            /** @var ContainerBuilder $container */
            $serviceIds = array_keys($container->findTaggedServiceIds(HttplugExtension::HTTPLUG_CLIENT_TAG));

            foreach ($serviceIds as $serviceId) {
                $decoratingServiceId = \sprintf(
                    '%s.mock',
                    $serviceId
                );

                $container->register($decoratingServiceId, Client::class)
                    ->setDecoratedService($serviceId)
                    ->setPublic(true);
            }

Plugins
```````

Clients can have plugins that act on the request before it is sent out and/or
on the response before it is returned to the caller. Generic plugins from
``php-http/client-common`` (e.g. retry or redirect) can be configured globally.
You can tell the client which of those plugins to use, as well as specify the
service names of custom plugins that you want to use.

Additionally you can configure any of the ``php-http/plugins`` specifically on
a client. For some plugins this is the only place where they can be configured.
The order in which you specify the plugins **does** matter.

You can configure many of the plugins directly on the client:

.. code-block:: yaml

    // config.yml
    httplug:
        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins:
                    - error:
                        only_server_exception: true
                    - add_host:
                        host: "http://localhost:8000"
                    - header_defaults:
                        headers:
                            "X-FOO": bar
                    - authentication:
                        acme_basic:
                            type: 'basic'
                            username: 'my_username'
                            password: 'p4ssw0rd'


See :doc:`full configuration </integrations/symfony-full-configuration>` for
the full list of plugins you can configure.

Alternatively, the same configuration also works on a global level. With this,
you can configure plugins once and then use them in several clients. The plugin
service names follow the pattern ``httplug.plugin.<name>``:

.. code-block:: yaml

    // config.yml
    httplug:
        plugins:
            cache:
                cache_pool: 'my_cache_pool'
        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins:
                    - 'httplug.plugin.cache'
            app:
                plugins:
                    - 'httplug.plugin.cache'

.. note::

    To configure HTTP caching, you need to require ``php-http/cache-plugin`` in
    your project. It is available as a separate composer package.

To use a custom plugin or when you need specific configuration that is not
covered by the bundle configuration, you can configure the plugin as a normal
Symfony service and then reference that service name in the plugin list of your
client:

.. code-block:: yaml

    // services.yml
    acme_plugin:
        class: Acme\Plugin\MyCustomPlugin
        arguments: ["%some_parameter%"]

.. code-block:: yaml

    // config.yml
    httplug:
        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins:
                    - 'acme_plugin'

Authentication
``````````````

You can configure a client with authentication. Valid authentication types are
``basic``, ``bearer``, ``service``, ``wsse`` and ``query_param``. See more examples at the
:doc:`full configuration </integrations/symfony-full-configuration>`.

.. code-block:: yaml

    // config.yml
    httplug:
        plugins:
            authentication:
                my_wsse:
                    type: 'wsse'
                    username: 'my_username'
                    password: 'p4ssw0rd'

        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins: ['httplug.plugin.authentication.my_wsse']

.. warning::

    Using query parameters for authentication is :ref:`not safe <Authentication-QueryParams>`.
    The auth params will appear on the URL and we recommend to NOT log your request, especially on production side.

VCR Plugin
``````````

The :doc:`VCR Plugin </plugins/vcr>` allows to record and/or replay HTTP requests. You can configure the mode you want,
how to find recorded responses and how to match requests with responses. The mandatory options are:

.. code-block:: yaml

    // config.yml
    httplug:
        clients:
            acme:
                plugins:
                - vcr:
                    mode: replay # record | replay | replay_or_record
                    fixtures_directory: '%kernel.project_dir%/fixtures/http' # mandatory for "filesystem" recorder
                    # recorder: filesystem

See :doc:`Full configuration </integrations/symfony-full-configuration>` for the full list of configuration options.

.. warning::

    You have to explicitly require this plugin with composer (``composer require --dev php-http/vcr-plugin``) before
    using it, as it isn't included by default.

Special HTTP Clients
````````````````````

If you want to use the ``FlexibleHttpClient`` or ``HttpMethodsClient`` from the
``php-http/client-common`` package, you may specify that on the client configuration.

.. code-block:: yaml

    // config.yml
    httplug:
        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                flexible_client: true

            foobar:
                factory: 'httplug.factory.guzzle6'
                http_methods_client: true

List of Services
````````````````

+-------------------------------------+-------------------------------------------------------------------------+
| Service id                          | Description                                                             |
+=====================================+=========================================================================+
| ``httplug.message_factory``         | Service* that provides the `Http\Message\MessageFactory`                |
+-------------------------------------+-------------------------------------------------------------------------+
| ``httplug.uri_factory``             | Service* that provides the `Http\Message\UriFactory`                    |
+-------------------------------------+-------------------------------------------------------------------------+
| ``httplug.stream_factory``          | Service* that provides the `Http\Message\StreamFactory`                 |
+-------------------------------------+-------------------------------------------------------------------------+
| ``httplug.client.[name]``           | There is one service per named client.                                  |
+-------------------------------------+-------------------------------------------------------------------------+
| ``httplug.client``                  | | If there is a client named "default", this service is an alias to     |
|                                     | | that client, otherwise it is an alias to the first client configured. |
+-------------------------------------+-------------------------------------------------------------------------+
| | ``httplug.plugin.content_length`` | | These are plugins that are enabled by default.                        |
| | ``httplug.plugin.decoder``        | | These services are private and should only be used to configure       |
| | ``httplug.plugin.error``          | | clients or other services.                                            |
| | ``httplug.plugin.logger``         |                                                                         |
| | ``httplug.plugin.redirect``       |                                                                         |
| | ``httplug.plugin.retry``          |                                                                         |
| | ``httplug.plugin.stopwatch``      |                                                                         |
+-------------------------------------+-------------------------------------------------------------------------+
| | ``httplug.plugin.cache``          | | These are plugins that are disabled by default and only get           |
| | ``httplug.plugin.cookie``         | | activated when configured.                                            |
| | ``httplug.plugin.history``        | | These services are private and should only be used to configure       |
|                                     | | clients or other services.                                            |
+-------------------------------------+-------------------------------------------------------------------------+

\* *These services are always an alias to another service. You can specify your own service or leave the default, which is the same name with `.default` appended.*


Usage for Reusable Bundles
``````````````````````````

Rather than code against specific HTTP clients, you want to use the HTTPlug
``Client`` interface. To avoid building your own infrastructure to define
services for the client, simply ``require: php-http/httplug-bundle`` in your
bundles ``composer.json``. You SHOULD provide a configuration option to specify
which HTTP client service to use for each of your services. This option should
default to ``httplug.client``. This way, the default case needs no additional
configuration for your users, but they have the option of using specific
clients with each of your services.

The only steps they need is ``require`` one of the adapter implementations in
their projects ``composer.json`` and instantiating the ``HttplugBundle`` in
their kernel.

Mock Responses In Functional Tests
``````````````````````````````````

First thing to do is add the :doc:`php-http/mock-client </clients/mock-client>` to your ``require-dev`` section.
Then, use the mock client factory in your test environment configuration:

.. code-block:: yaml

    # config_test.yml
    httplug:
        clients:
            my_awesome_client:
                factory: 'httplug.factory.mock' # replace factory

To mock a response in your tests, do:

.. code-block:: php

    // SomeWebTestCase.php
    $client = static::createClient();

    // If your test has the client (BrowserKit) make multiple requests, you need to disable reboot as the kernel is rebooted on each request.
    // $client->disableReboot();

    $response = $this->createMock('Psr\Http\Message\ResponseInterface');
    $response->method('getBody')->willReturn(/* Psr\Http\Message\Interface instance containing expected response content. */);
    $client->getContainer()->get('httplug.client.mock')->addResponse($response);

.. |clearfloat|  raw:: html

    <div style="clear:left"></div>

.. _`Symfony Flex`: https://symfony.com/doc/current/setup/flex.html
.. _`autowiring`: https://symfony.com/doc/current/service_container/autowiring.html
