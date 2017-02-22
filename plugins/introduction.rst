Introduction
============

Install
-------

The plugin client and the core plugins are available in the `php-http/client-common`_ package:

.. code-block:: bash

    $ composer require php-http/client-common

.. _php-http/client-common: https://github.com/php-http/client-common

.. versionadded:: 1.1
    The plugins were moved to the clients-common package in version 1.1.
    If you work with version 1.0, you need to require the separate `php-http/plugins` package
    and the namespace is ``Http\Client\Plugin`` instead of ``Http\Client\Common``


How it works
------------

In the plugin package, you can find the following content:

- the ``PluginClient`` itself which acts as a wrapper around any kind of HTTP client (sync/async);
- the ``Plugin`` interface;
- a set of core plugins (see the full list in the left side navigation).

The ``PluginClient`` accepts an HTTP client implementation and an array of plugins.
Let’s see an example::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\RetryPlugin;
    use Http\Client\Common\Plugin\RedirectPlugin;

    $retryPlugin = new RetryPlugin();
    $redirectPlugin = new RedirectPlugin();

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [
            $retryPlugin,
            $redirectPlugin,
        ]
    );

The ``PluginClient`` accepts and implements both ``Http\Client\HttpClient`` and
``Http\Client\HttpAsyncClient``, so you can use both ways to send a request. In
case the passed client implements only one of these interfaces, the ``PluginClient``
"emulates" the other behavior as a fallback.

It is important to note that the order of plugins matters. During the request,
plugins are executed in the order they have been specified in the constructor,
from first to last. Once a response has been received, the plugins are called
again in reversed order, from last to first.

For our previous example, the execution chain will look like this:

.. code::

    Request  ---> PluginClient ---> RetryPlugin ---> RedirectPlugin ---> HttpClient ----
                                                                                       | (processing call)
    Response <--- PluginClient <--- RetryPlugin <--- RedirectPlugin <--- HttpClient <---

In order to achieve the intended behavior in the global process, you need to
pay attention to what each plugin does and define the correct order accordingly.

For example, the ``RetryPlugin`` should probably be at the end of the chain to
keep the retry process as short as possible. However, if one of the other
plugins is doing a fragile operation that might need a retry, place the retry
plugin before that.

The recommended way to order plugins is the following:

 1. Plugins that modify the request should be at the beginning (like Authentication or Cookie Plugin);
 2. Plugins which intervene in the workflow should be in the "middle" (like Retry or Redirect Plugin);
 3. Plugins which log information should be last (like Logger or History Plugin).

.. note::

    There can be exceptions to these rules. For example, for security reasons you might not want
    to log the authentication information (like ``Authorization`` header) and choose to put the
    :doc:`Authentication Plugin <authentication>` after the :doc:`Logger Plugin <logger>`.

Configuration Options
---------------------

The ``PluginClient`` accepts an array of configuration options to tweak its behavior.

.. _plugin-client.max-restarts:

``max_restarts``: int (default 10)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To prevent issues with faulty plugins or endless redirects, the ``PluginClient`` injects a security
check to the start of the plugin chain. If the same request is restarted more than specified by
that value, execution is aborted and an error is raised.

.. _plugin-client.debug-plugins:

``debug_plugins``: array of Plugin
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The debug plugins are injected between each normal plugin. This can be used to
log the changes each plugin does on the request and response objects.

.. _plugin-client.libraries:

Libraries that Require Plugins
------------------------------

When :doc:`writing a library based on HTTPlug <../httplug/library-developers>`, you might require
specific plugins to be active. The recommended way for doing this is to provide a factory method
for the ``PluginClient`` that library users should use. This allows them to inject their own
plugins or configure a different client. For example::

    $myApiClient = new My\Api\Client('https://api.example.org', My\Api\HttpClientFactory::create('john', 's3cr3t'));

    use Http\Client\HttpClient;
    use Http\Client\Common\Plugin;
    use Http\Client\Common\Plugin\AuthenticationPlugin;
    use Http\Client\Common\Plugin\ErrorPlugin;
    use Http\Discovery\HttpClientDiscovery;

    class HttpClientFactory
    {
        /**
         * Build the HTTP client to talk with the API.
         *
         * @param string     $user    Username for the application on the API
         * @param string     $pass    Password for the application on the API
         * @param Plugin[]   $plugins List of additional plugins to use
         * @param HttpClient $client  Base HTTP client
         *
         * @return HttpClient
         */
        public static function create($user, $pass, array $plugins = [], HttpClient $client = null)
        {
            if (!$client) {
                $client = HttpClientDiscovery::find();
            }
            $plugins[] = new ErrorPlugin();
            $plugins[] = new AuthenticationPlugin(
                 // This API has it own authentication algorithm
                new ApiAuthentication(Client::AUTH_OAUTH_TOKEN, $user, $pass)
            );
            return new PluginClient($client, $plugins);
        }
    }
