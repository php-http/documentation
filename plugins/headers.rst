Header Plugins
==============

Header plugins are useful to manage request headers. Many operations are
possible with the provided plugins.

Default Headers Values
----------------------

The plugin ``HeaderDefaultsPlugin`` allows you to define default values for
given headers. If a header is not set, it will be added. However, if the header
is already present, the request is left unchanged::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\HeaderDefaultsPlugin;

    $defaultUserAgent = 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.1';

    $headerDefaultsPlugin = new HeaderDefaultsPlugin([
        'User-Agent' => $defaultUserAgent
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$headerDefaultsPlugin]
    );

Mandatory Headers Values
------------------------

The plugin ``HeaderSetPlugin`` allows you to fix values of given headers. That
means that any request passing through this plugin will be set to the specified
value. Existing values of the header will be overwritten.

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\HeaderSetPlugin;

    $userAgent = 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.1';

    $headerSetPlugin = new HeaderSetPlugin([
        'User-Agent' => $userAgent,
        'Accept' => 'application/json'
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$headerSetPlugin]
    );

Removing Headers
----------------

The plugin ``HeaderRemovePlugin`` allows you to remove headers from the request.

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\HeaderRemovePlugin;

    $headerRemovePlugin = new HeaderRemovePlugin([
        'User-Agent'
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$headerRemovePlugin]
    );

Appending Header Values
-----------------------

The plugin ``HeaderAppendPlugin`` allows you to add headers. The header will be
created if not existing yet. If the header already exists, the value will be
appended to the list of values for this header.

.. note::

    The use cases for this plugin are limited. One real world example of
    headers that can have multiple values is "Forwarded".

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\HeaderAppendPlugin;

    $myIp = '100.100.100.100';

    $headerAppendPlugin = new HeaderAppendPlugin([
        'Forwarded' => 'for=' . $myIp
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$headerAppendPlugin]
    );

Mixing operations
-----------------

Different header plugins can be mixed together to achieve different behaviors
and you can use the same plugin for identical operations.

The following example will force the ``User-Agent`` and the ``Accept`` header values while removing the ``Cookie`` header:

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\HeaderSetPlugin;
    use Http\Client\Common\Plugin\HeaderRemovePlugin;

    $userAgent = 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.1';

    $headerSetPlugin = new HeaderSetPlugin([
        'User-Agent' => $userAgent,
        'Accept' => 'application/json'
    ]);

    $headerRemovePlugin = new HeaderRemovePlugin([
        'Cookie'
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [
            $headerSetPlugin,
            $headerRemovePlugin
        ]
    );


