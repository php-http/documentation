Always Seekable Body Plugin
===========================

The ``AlwaysSeekableBodyPlugin`` ensure that body of the request and body of the response are always seekable.
This allows a lot of components that read the stream to rewind it in order to be used later by another component::

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

The plugin supports the following options:

 * ``use_file_buffer``: Whether it should use a temporary file to buffer the body of a stream if it's too big
 * ``memory_buffer_size``: Maximum memory to use for buffering the stream before it switch to a file
