Cookie Plugin
=============

Cookie plugins allow you to sore cookies information in a `CookieJar` and reuses them on consequent requests according
to `RFC 6265`_ specification::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Message\CookieJar;
    use Http\Plugins\PluginClient;
    use Http\Plugins\CookiePlugin;

    $cookiePlugin = new CookiePlugin(new CookieJar());

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$cookiePlugin]
    );

.. _RFC 6265: https://tools.ietf.org/html/rfc6265
