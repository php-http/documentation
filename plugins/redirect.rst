Redirect Plugin
===============

The ``RedirectPlugin`` automatically follows redirection answers from a server. If the plugin
detects a redirection, it creates a request to the target URL and restarts the plugin chain.

The plugin attempts to detect circular redirects and will abort when such a redirect is
encountered. Note that a faulty server appending something on each request is not detected. This
situation is caught by the plugin client itself and can be controlled through the
:ref:`plugin-client.max-restarts` setting.

Initiate the redirect plugin as follows::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\RedirectPlugin;

    $redirectPlugin = new RedirectPlugin();

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$redirectPlugin]
    );

.. warning::

    Following redirects can increase the robustness of your application. But if you build some sort
    of API client, you want to at least keep an eye on the log files. Having your application
    follow redirects instead of going to the right end point directly makes your application slower
    and increases the load on both server and client.

.. note::

    Depending on the status code, redirecting should change POST/PUT requests to GET requests. This
    plugin implements this behavior - except if you set the ``strict`` option to true, as explained
    below. It removes the request body if the method changes, see ``stream_factory`` below.

    To understand the exact semantics of which HTTP status changes the method and which not, have a
    look at the configuration in the source code of the RedirectPlugin class.

Options
-------

``preserve_header``: boolean|string[] (default: true)

When set to ``true``, all headers are kept for the next request. ``false`` means all headers are
removed. An array of strings is treated as a whitelist of header names to keep from the original
request.

``use_default_for_multiple``: bool (default: true)

Whether to follow the default direction on the multiple redirection status code 300. If set to
false, a status of 300 will raise the ``Http\Client\Common\Exception\MultipleRedirectionException``.

``strict``: bool (default: false)

When set to ``true``, 300, 301 and 302 status codes will not modify original request's method and
body on consecutive requests. E. g. POST redirect requests are sent as POST requests instead of
POST redirect requests are sent as GET requests.

``stream_factory``: StreamFactoryInterface (default: auto discovered)

The PSR-17 stream factory is used to create an empty stream for removing the body of the request on
redirection. To keep the body on all redirections, set ``stream_factory`` to null.
The stream factory is discovered if either ``php-http/discovery`` is installed and provides a
factory, or ``nyholm/psr7`` or a new enough version of ``guzzlehttp/psr7`` are installed. If you
only have other implementations, you need to provide the factory in ``stream_factory``.

If no factory is found, the redirect plugin does not remove the body on redirection.
