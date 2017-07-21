Content-Type Plugin
===================

The ``ContentTypePlugin`` sets the correct ``Content-Type`` header value based on the content of the body stream of the
request. This helps HTTP servers to handle the request::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\ContentTypePlugin;

    $contentTypePlugin = new ContentTypePlugin();

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$contentTypePlugin]
    );

For now, the plugin can only detect JSON or XML content. If the content of the stream can not be determined, the plugin does nothing.