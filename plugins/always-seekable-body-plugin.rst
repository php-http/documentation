Always Seekable Body Plugin
===========================

``AlwaysSeekableBodyPlugin`` ensure that the body used in request and response is always seekable.
This allows a lot of components, reading the stream, to rewind it in order to be used later by another component::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\AlwaysSeekableBodyPlugin;

    $options = [
        'use_file_buffer' => true,
        'memory_buffer_size' => 2097152,
    ];
    $alwaysSeekableBodyPlugin = new AlwaysSeekableBodyPlugin($options);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$alwaysSeekableBodyPlugin]
    );

This plugin supports the following options (which are passed to the ``BufferedStream`` class):

 * ``use_file_buffer``: Whether it should use a temporary file to buffer the body of a stream if it's too big
 * ``memory_buffer_size``: Maximum memory to use for buffering the stream before it switch to a file
