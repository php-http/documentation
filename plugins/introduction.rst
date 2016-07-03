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

- the Plugin Client itself which acts as a wrapper around any kind of HTTP Client (sync/async)
- a Plugin interface
- a set of core plugins (see the full list in the left side navigation)

The Plugin Client accepts an HTTP Client implementation and an array of plugins.

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

The Plugin Client accepts and implements both ``Http\Client\HttpClient`` and ``Http\Client\HttpAsyncClient``, so you can use
both ways to send a request. In case the passed client implements only one of these interfaces, the Plugin Client
"emulates" the other behavior as a fallback.

It is important, that the order of plugins matters. During the request, plugins are called in the order they have
been added, from first to last. Once a response has been received, they are called again in reversed order,
from last to first.

In case of our previous example, the execution chain will look like this::

    Request  ---> PluginClient ---> RetryPlugin ---> RedirectPlugin ---> HttpClient ----
                                                                                       | (processing call)
    Response <--- PluginClient <--- RetryPlugin <--- RedirectPlugin <--- HttpClient <---

In order to have correct behavior over the global process, you need to understand well how each plugin is used,
and manage a correct order when passing the array to the Plugin Client.

Retry Plugin will be best at the end to optimize the retry process, but it can also be good
to have it as the first plugin, if one of the plugins is inconsistent and may need a retry.

The recommended way to order plugins is the following:

 1. Plugins that modify the request should be at the beginning (like Authentication or Cookie Plugin)
 2. Plugins which intervene in the workflow should be in the "middle" (like Retry or Redirect Plugin)
 3. Plugins which log information should be last (like Logger or History Plugin)

.. note::

    There can be exceptions to these rules. For example, for security reasons you might not want
    to log the authentication information (like ``Authorization`` header) and choose to put the
    :doc:`Authentication Plugin <authentication>` after the doc:`Logger Plugin <logger>`.


Configuration Options
---------------------

The PluginClient accepts an array of configuration options that can tweak its behavior.

.. _plugin-client.max-restarts:

``max_restarts``: int (default 10)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To prevent issues with faulty plugins or endless redirects, the ``PluginClient`` injects a security
check to the start of the plugin chain. If the same request is restarted more than specified by
that value, execution is aborted and an error is raised.

.. _plugin-client.debug-plugins:

``debug_plugins``: array of Plugin
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A debug plugin is injected between each normal plugin. This could be used to log the changes each
plugin does on the Request and Response objects.

.. _plugin-client.libraries:

Libraries that Require Plugins
------------------------------

When :doc:`writing a library based on HTTPlug <../httplug/library-developers>`, you might require
specific plugins to be active. The recommended way for doing this is to provide a factory method
for the ``PluginClient`` that your library users should use. This allows them to inject their own
plugins or configure a different client. For example::

    $myApiClient = new My\Api\Client('https://api.example.org', My\Api\HttpClientFactory::create('john', 's3cr3t'));

    use Http\Client\HttpClient;
    use Http\Client\Common\Plugin\AuthenticationPlugin;
    use Http\Client\Common\Plugin\ErrorPlugin;
    use Http\Discovery\HttpClientDiscovery;

    class HttpClientFactory
    {
        /**
         * Build the HTTP client to talk with the API.
         *
         * @param string     $user   Username
         * @param string     $pass   Password
         * @param HttpClient $client Base HTTP client
         *
         * @return HttpClient
         */
        public static function create($user, $pass, HttpClient $client = null)
        {
            if (!$client) {
                $client = HttpClientDiscovery::find();
            }
            return new PluginClient($client, [
                new ErrorPlugin(),
                new AuthenticationPlugin(
                     // This API has it own authentication algorithm
                    new ApiAuthentication(Client::AUTH_OAUTH_TOKEN, $user, $pass)
                ),
            ]);
        }
