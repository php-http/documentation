Cookie Plugin
=============

The ``CookiePlugin`` allow you to store cookies in a ``CookieJar`` and reuse them on consequent requests according
to :rfc:`6265#section-4` specification::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Message\CookieJar;
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\CookiePlugin;

    $cookiePlugin = new CookiePlugin(new CookieJar());

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$cookiePlugin]
    );
