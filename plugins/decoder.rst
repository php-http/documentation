Decoder Plugin
==============

The ``DecoderPlugin`` decodes the body of the response with filters coming from the ``Transfer-Encoding``
or ``Content-Encoding`` headers::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\DecoderPlugin;

    $decoderPlugin = new DecoderPlugin();

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$decoderPlugin]
    );

The plugin can handle the following encodings:

 * ``chunked``: Decode a stream with a ``chunked`` encoding (no size in the ``Content-Length`` header of the response)
 * ``compress``: Decode a stream encoded with the ``compress`` encoding according to :rfc:`1950`
 * ``deflate``: Decode a stream encoded with the ``inflate`` encoding according to :rfc:`1951`
 * ``gzip``: Decode a stream encoded with the ``gzip`` encoding according to :rfc:`1952`

You can also use the decoder plugin to decode only the ``Transfer-Encoding`` header and not the ``Content-Encoding`` one
by setting the ``use_content_encoding`` configuration option to false::

    $decoderPlugin = new DecoderPlugin(['use_content_encoding' => false]);

Not decoding content is useful when you don't want to get the encoded response body, or acting as a proxy but sill
be able to decode message from the ``Transfer-Encoding`` header value.
