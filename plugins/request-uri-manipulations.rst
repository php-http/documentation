Request URI Manipulations
=========================

Request URI manipulations can be done thanks to several plugins:

* ``AddHostPlugin``: Set host, scheme and port. Depending on configuration,
  the host is overwritten in every request or only set if not yet defined in the request.
* ``AddPathPlugin``: Prefix the request path with a path, leaving the host information untouched.
* ``BaseUriPlugin``: It's a combination of ``AddHostPlugin`` and ``AddPathPlugin``.

Each plugin uses the ``UriInterface`` to build the base request::

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

The ``AddPathPlugin``  will check if the path prefix is already present on the
URI. This will break for the edge case when the prefix is repeated. For example,
if ``https://example.com/api/api/foo`` is a valid URI on the server and the
configured prefix is ``/api``, the request to ``/api/foo`` is not rewritten.

For further details, please see the phpdoc on the ``AddPathPlugin`` source code.

No solution fits all use cases. This implementation works fine for the common
use cases. If you have a specific situation where this is not the right thing,
you can build a custom plugin that does exactly what you need.
