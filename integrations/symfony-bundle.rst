Symfony Bundle
==============

This bundle integrate HTTPlug with the Symfony framework. The bundle helps to register services for all your clients and makes sure all the configuration is in one place. The bundle also feature a toolbar plugin with information about your requests.

This guide explains how to configure HTTPlug in the Symfony framework. See the :doc:`../httplug/tutorial` for examples how to use HTTPlug in general.

Installation
````````````

Install the HTTPlug bundle with composer and enable it in your AppKernel.php.

.. code-block:: bash

    $ composer require php-http/httplug-bundle

.. code-block:: php

    public function registerBundles()
    {
        $bundles = array(
            // ...
            new Http\HttplugBundle\HttplugBundle(),
        );
    }

You will find all available configuration at the :doc:`full configuration </integrations/symfony-full-configuration>` page.

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
                    verify: false
                    timeout: 2

.. code-block:: php

    $request = $this->container->get('httplug.message_factory')->createRequest('GET', 'http://example.com');
    $response = $this->container->get('httplug.client.acme')->sendRequest($request);


Web Debug Toolbar
`````````````````
.. image:: /assets/img/debug-toolbar.png
    :align: right
    :width: 120px

When using a client configured with ``HttplugBundle``, you will get debug information in the web debug toolbar. It will tell you how many request were made and how many of those that were successful or not. It will also show you detailed information about each request.

Discovery of Factory Classes
````````````````````````````

If you want the bundle to automatically find usable factory classes, install and enable ``puli/symfony-bundle``. If you do not want use auto discovery, you need to specify all the factory classes for you client. The following example show how you configure factory classes using Guzzle:

.. code-block:: yaml

    httplug:
        classes:
            client: Http\Adapter\Guzzle6\Client
            message_factory: Http\Message\MessageFactory\GuzzleMessageFactory
            uri_factory: Http\Message\UriFactory\GuzzleUriFactory
            stream_factory: Http\Message\StreamFactory\GuzzleStreamFactory



Configure Clients
`````````````````

You can configure your clients with default options. These default values will be specific to you client you are using. The clients are later registered as services.

.. code-block:: yaml

    httplug:
        clients:
            my_guzzle5:
                factory: 'httplug.factory.guzzle5'
                config:
                    # These options are given to Guzzle without validation.
                    defaults:
                        verify_ssl: false
                        timeout: 4
            acme:
                factory: 'httplug.factory.curl'
                config:
                    78: 4 #CURLOPT_CONNECTTIMEOUT

.. code-block:: php

    $httpClient = $this->container->get('httplug.client.my_guzzle5');
    $httpClient = $this->container->get('httplug.client.curl');

    // will be the same as ``httplug.client.my_guzzle5``
    $httpClient = $this->container->get('httplug.client');

The bundle has client factory services that you can use to build your client. If you need a very custom made client you could create your own factory service implementing ``Http\HttplugBudle\ClientFactory\ClientFactory``. The built-in services are:

* ``httplug.factory.curl``
* ``httplug.factory.guzzle5``
* ``httplug.factory.guzzle6``
* ``httplug.factory.react``
* ``httplug.factory.socket``

Plugins
```````

You can configure the clients with plugins. You can choose to use a built in plugin in the ``php-http/plugins`` package or provide a plugin of your own. The order of the specified plugin does matter.

.. code-block:: yaml

    // services.yml
    acme_plugin:
          class: Acme\Plugin\MyCustomPlugin
          arguments: ["%some_parameter%"]

.. code-block:: yaml

    // config.yml
    httplug:
        plugins:
            cache:
                cache_pool: 'my_cache_pool'
        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins: ['acme_plugin', 'httplug.plugin.cache', 'httplug.plugin.retry']


Authentication
``````````````

You can configure a client with authentication. Valid authentication types are ``basic``, ``bearer``, ``service`` and ``wsse``. See more examples at the :doc:`full configuration </integrations/symfony-full-configuration>`.

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

Rather than code against specific HTTP clients, you want to use the HTTPlug ``Client`` interface. To avoid building your own infrastructure to define services for the client, simply ``require: php-http/httplug-bundle`` in your bundles ``composer.json``. You SHOULD provide a configuration option to specify the which HTTP client service to use for each of your services. This option should default to ``httplug.client``. This way, the default case needs no additional configuration for your users, but they have the option of using specific clients with each of your services.

The only steps they need is ``require`` one of the adapter implementations in their projects ``composer.json`` and instantiating the ``HttplugBundle`` in their kernel.
