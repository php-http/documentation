Symfony Bundle
==============

The usage documentation is split into two parts. First we explain how to configure the bundle in an application. The second part is for developing reusable Symfony bundles that depend on an HTTP client defined by the Httplug interface.

For information how to write applications with the services provided by this bundle, have a look at the [Httplug documentation](http://docs.php-http.org).


Use in Applications
-------------------

Custom services
```````````````

+----------------------------------+---------------------------------------------------------------------+
| Service id                       | Description                                                         |
+==================================+=====================================================================+
| httplug.message_factory          | Service* that provides the `Http\Message\MessageFactory`            |
+----------------------------------+---------------------------------------------------------------------+
| httplug.uri_factory              | Service* that provides the `Http\Message\UriFactory`                |
+----------------------------------+---------------------------------------------------------------------+
| httplug.stream_factory           | Service* that provides the `Http\Message\StreamFactory`             |
+----------------------------------+---------------------------------------------------------------------+
| httplug.client.[name]            | | This is your Httpclient that you have configured.                 |
|                                  | | With the configuration below the name would be `acme_client`.     |
+----------------------------------+---------------------------------------------------------------------+
| httplug.client                   | This is the first client configured or a client named `default`.    |
+----------------------------------+---------------------------------------------------------------------+
| | httplug.plugin.content_length  | | These are plugins that are enabled by default.                    |
| | httplug.plugin.decoder         | | These services are not public and may only be used when configure |
| | httplug.plugin.error           | | HttpClients or other services.                                    |
| | httplug.plugin.logger          |                                                                     |
| | httplug.plugin.redirect        |                                                                     |
| | httplug.plugin.retry           |                                                                     |
| | httplug.plugin.stopwatch       |                                                                     |
+----------------------------------+---------------------------------------------------------------------+
| | httplug.plugin.cache           | | These are plugins that are disabled by default.                   |
| | httplug.plugin.cookie          | | They need to be configured before they can be used.               |
| | httplug.plugin.history         | | These services are not public and may only be used when configure |
|                                  | | HttpClients or other services.                                    |
+----------------------------------+---------------------------------------------------------------------+

\* *These services are always an alias to another service. You can specify your own service or leave the default, which is the same name with `.default` appended. The default services in turn use the service discovery mechanism to provide the best available implementation. You can specify a class for each of the default services to use instead of discovery, as long as those classes can be instantiated without arguments.*


If you need a more custom setup, define the services in your application configuration and specify your service in the `main_alias` section. For example, to add authentication headers, you could define a service that decorates the service `httplug.client.default` with a plugin that injects the authentication headers into the request and configure `httplug.main_alias.client` to the name of your service.

.. code-block:: yaml

    httplug:
        clients:
            acme_client: # This is the name of the client
            factory: 'httplug.factory.guzzle6'

        main_alias:
            client: httplug.client.default
            message_factory: httplug.message_factory.default
            uri_factory: httplug.uri_factory.default
            stream_factory: httplug.stream_factory.default
        classes:
            # uses discovery if not specified
            client: ~
            message_factory: ~
            uri_factory: ~
            stream_factory: ~


Configuration without auto discovery
````````````````````````````````````

By default we use Puli to auto discover factories. If you do not want to use auto discovery you could use the following configuration (Guzzle):

.. code-block:: yaml

    httplug:
        classes:
            client: Http\Adapter\Guzzle6\Client
            message_factory: Http\Message\MessageFactory\GuzzleMessageFactory
            uri_factory: Http\Message\UriFactory\GuzzleUriFactory
            stream_factory: Http\Message\StreamFactory\GuzzleStreamFactory


Configure your client
`````````````````````

You can configure your clients with some good default options. The clients are later registered as services.

.. code-block:: yaml

    httplug:
        clients:
            my_guzzle5:
                factory: 'httplug.factory.guzzle5'
                config:
                    # These options are given to Guzzle without validation.
                    defaults:
                        base_uri: 'http://google.se/'
                        verify_ssl: false
                        timeout: 4
                        headers:
                            Content-Type: 'application/json'
            acme:
                factory: 'httplug.factory.guzzle6'
                config:
                    base_uri: 'http://google.se/'

.. code-block:: php

    $httpClient = $this->container->get('httplug.client.my_guzzle5');
    $httpClient = $this->container->get('httplug.client.acme');


Plugins
```````

You can configure the clients with plugins.

.. code-block:: yaml

    // services.yml
    acme_plugin:
          class: Acme\Plugin\MyCustonPlugin
          arguments: ["%api_key%"]

.. code-block:: yaml

    // config.yml
    httpug:
        plugins:
            cache:
                cache_pool: 'my_cache_pool'
        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins: ['acme_plugin', 'httplug.plugin.cache', ''httplug.plugin.retry']
                config:
                    base_uri: 'http://google.se/'


Authentication
``````````````

.. code-block:: yaml

    // config.yml
    httpug:
        plugins:
            authentication:
                my_basic:
                    type: 'basic'
                    username: 'my_username'
                    password: 'p4ssw0rd'
                my_wsse:
                    type: 'wsse'
                    username: 'my_username'
                    password: 'p4ssw0rd'
                my_brearer:
                    type: 'bearer'
                    token: 'authentication_token_hash'
                my_service:
                    type: 'service'
                    service: 'my_authentication_service'

        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins: ['httplug.plugin.authentication.my_wsse']



Use for Reusable Bundles
------------------------

Rather than code against specific HTTP clients, you want to use the Httplug `Client` interface. To avoid building your own infrastructure to define services for the client, simply `require: php-http/httplug-bundle` in your bundles `composer.json`. You SHOULD provide configuration for each of your services that needs an HTTP client to specify the service to use, defaulting to `httplug.client`. This way, the default case needs no additional configuration for your users.

The only steps they need is `require` one of the adapter implementations in their projects `composer.json` and instantiating the HttplugBundle in their kernel.
