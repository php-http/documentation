Content-Length Plugin
=====================

The ``ContentLengthPlugin`` sets the correct ``Content-Length`` header value based on the size of the body stream of the
request. This helps HTTP servers to handle the request::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\ContentLengthPlugin;

    $contentLengthPlugin = new ContentLengthPlugin();

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$contentLengthPlugin]
    );

If the size of the stream can not be determined, the plugin sets the Encoding header to ``chunked``, as defined in
:rfc:`7230#section-4.1`

This is useful when you want to transfer data of unknown size to an HTTP application without consuming memory.

As an example, let's say you want to send a tar archive of the current directory to an API. Normally you would
end up doing this in 2 steps, first saving the result of the tar archive into a file or into the memory of
PHP with a variable, then sending this content with an HTTP Request.

With this plugin you can achieve this behavior without doing the first step::

    proc_open("/usr/bin/env tar c .", [["pipe", "r"], ["pipe", "w"], ["pipe", "w"]], $pipes, "/path/to/directory");
    $tarResource  = $pipes[1];

    $request = MessageFactoryDiscovery::find()->createRequest('POST', '/url/to/api/endpoint', [], $tarResource);
    $response = $pluginClient->sendRequest($request);

In this case the tar output is directly streamed to the server without using memory on the PHP side.
