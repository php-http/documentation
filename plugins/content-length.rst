Content-Length Plugin
=====================

The Content-Length Plugin allows you to make your HTTP Request compliant with most of the servers.
It's main purpose is to set the correct `Content-Length` Header value based on your stream size.

However if it's failed to get the size of a stream, it will set the correct header and decorate the body of the request
with Chunked transfer encoding as defined in the `RFC 2145`_::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\ContentLengthPlugin;

    $contentLengthPlugin = new ContentLengthPlugin();

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$contentLengthPlugin]
    );

One of the main advantage of using this plugin, is when you want to transfer information from an existing stream
to an http application without consuming memory.

As an example, let's say you want to send an archive tar of the current directory to an api. Normally you will
end up doing this in 2 steps, first saving the result of the tar archive into a file our into the memory of
PHP with a variable, then sending this content with an HTTP Request.

With this plugin you can achieve this behavior without doing the first step::

    proc_open("/usr/bin/env tar c .", [["pipe", "r"], ["pipe", "w"], ["pipe", "w"]], $pipes, "/path/to/directory");
    $tarResource  = $pipes[1];

    $request = MessageFactoryDiscovery::find()->createRequest('POST', '/url/to/api/endpoint', [], $tarResource);
    $response = $pluginClient->sendRequest($request);

In this case the tar output is directly streamed to the server without using memory on the PHP side.

.. _RFC 2145: https://www.ietf.org/rfc/rfc2145.txt
