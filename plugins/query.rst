Query plugin
============

Default Query parameters
------------------------

The plugin ``QueryDefaultsPlugin`` allows you to define default values for
query parameters. If a query parameter is not set, it will be added. However, if the query parameter
is already present, the request is left unchanged. Names and values must not be URL encoded as this
plugin will encode them::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\HeaderDefaultsPlugin;

    $queryDefaultsPlugin = new QueryDefaultsPlugin([
        'locale' => 'en'
    ]);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$queryDefaultsPlugin]
    );

