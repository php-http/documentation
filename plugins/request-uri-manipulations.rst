Request URI Manipulations
=========================

Request URI manipulations can be done thanks to several plugins:

* ``AddHostPlugin``: Set host, scheme and port. Depending on configuration,
  the host is overwritten in every request or only set if not yet defined in the request.
* ``AddPathPlugin``: Prefix the request path with a path, leaving the host information untouched.
* ``BaseUriPlugin``: It's a combination of ``AddHostPlugin`` and ``AddPathPlugin``.

Each plugin use the ``UriInterface`` to build the base request::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Discovery\UriFactoryDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\BaseUriPlugin;

    $plugin = new BaseUriPlugin(UriFactoryDiscovery::find()->createUri('https://domain.com:8000/api'), [
        // Always replace the host, even if this one is provided on the sent request. Available for AddHostPlugin.
        'replace' => true,
    ]));

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$plugin]
    );
