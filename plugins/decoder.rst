Decoder Plugin
==============

Decoder Plugin decodes the body of the response with filters coming from the `Transfer-Encoding` or `Content-Encoding`
headers::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Plugins\PluginClient;
    use Http\Plugins\DecoderPlugin;

    $decoderPlugin = new DecoderPlugin();

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$decoderPlugin]
    );

Actually it can decodes 4 different filters:

 * chunked: Decode a stream with a chunked encoding (no size in the `Content-Length` header of the response)
 * compress: Decode a stream encoded with the compress filter according to `RFC 1950`_
 * Deflate: Decode a stream encoded with the inflate filter according to `RFC 1951`_
 * gzip: Decode a stream encoded with the gzip filter according to `RFC 1952`_

You can also use the decoder plugin to only decodes the `Transfer-Encoding` header and not the `Content-Encoding` one
by setting the first parameter of the constructor to false::

    $decoderPlugin = new DecoderPlugin(false);

This is useful when you want to get the encoded response body, or acting as a proxy.

.. _RFC 1950: https://tools.ietf.org/html/rfc1950
.. _RFC 1951: https://tools.ietf.org/html/rfc1951
.. _RFC 1952: https://tools.ietf.org/html/rfc1952
