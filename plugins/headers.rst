Header Plugins
==============

Header plugins are useful to manage request headers. Many operations are possible:

Default headers values
----------------------

The plugin ``HeaderDefaultPlugin`` allows to set default values for given headers.
That means if a header is not set, it will be added.
However, if the header already is present, the request is left unchanged.

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Plugins\PluginClient;
    use Http\Plugins\HeaderDefaultPlugin;

    $defaultUserAgent = 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.1';

    $headerDefaultPlugin = new HeaderDefaultPlugin([
        'User-Agent' => $defaultUserAgent
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$headerDefaultPlugin]
    );

Mandatory headers values
------------------------

The plugin ``HeaderSetPlugin`` allows to fix values of given header. That means that any request passing through
this plugin will have the given value for given header.

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Plugins\PluginClient;
    use Http\Plugins\HeaderSetPlugin;

    $userAgent = 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.1';

    $headerSetPlugin = new HeaderSetPlugin([
        'User-Agent' => $userAgent,
        'Accept' => 'application/json'
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$headerSetPlugin]
    );



Removing headers
----------------

The plugin ``HeaderRemovePlugin`` allows to remove given headers from the request.

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Plugins\PluginClient;
    use Http\Plugins\HeaderRemovePlugin;

    $userAgent = 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.1';

    $headerRemovePlugin = new HeaderRemovePlugin([
        'User-Agent'
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$headerRemovePlugin]
    );


Appending header values
-----------------------

The plugin ``HeaderAppendPlugin`` allows to set headers or to add values to existing headers.
That means if the request already has the given headers then the value will be appended to the current value
but if the request does not already have the given header, it will be added to the request with the given value.

.. note::

    This plugin is very specific and is mostly useful for headers like "forwarded"

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Plugins\PluginClient;
    use Http\Plugins\HeaderAppendPlugin;

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

Different header plugins can be mixed to achieve different behaviors
and you can use the same plugin for identical operations.

The following example will force the ``User-Agent`` and the ``Accept`` header values while removing ``Cookie`` header:

.. code:: php

    use Http\Discovery\HttpClientDiscovery;
    use Http\Plugins\PluginClient;
    use Http\Plugins\HeaderSetPlugin;
    use Http\Plugins\HeaderRemovePlugin;

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


