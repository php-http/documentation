Seekable Body Plugins
=====================

``RequestSeekableBodyPlugin`` and ``ResponseSeekableBodyPlugin`` ensure that body used in request and response is always seekable.
This allows a lot of components, reading the stream, to rewind it in order to be used later by another component::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\RequestSeekableBodyPlugin;
    use Http\Client\Common\Plugin\ResponseSeekableBodyPlugin;

    $options = [
        'use_file_buffer' => true,
        'memory_buffer_size' => 2097152,
    ];
    $requestSeekableBodyPlugin = new RequestSeekableBodyPlugin($options);
    $responseSeekableBodyPlugin = new ResponseSeekableBodyPlugin($options);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$requestSeekableBodyPlugin, $responseSeekableBodyPlugin]
    );

Those plugins support the following options (which are passed to the ``BufferedStream`` class):

 * ``use_file_buffer``: Whether it should use a temporary file to buffer the body of a stream if it's too big
 * ``memory_buffer_size``: Maximum memory to use for buffering the stream before it switch to a file

``RequestSeekableBodyPlugin`` should be added in top of your plugins, then next plugins can seek request body (i.e. for logging purpose).
``ResponseSeekableBodyPlugin`` should be the last plugin, then previous plugins can seek response body.
