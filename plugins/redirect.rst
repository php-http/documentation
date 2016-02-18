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
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\RedirectPlugin;

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

Options
-------

``preserve_header``: boolean|string[] (default: true)

When set to ``true``, all headers are kept for the next request. ``false`` means all headers are
removed. An array of strings is treated as a whitelist of header names to keep from the original
request.

``use_default_for_multiple``: bool (default: true)

Whether to follow the default direction on the multiple redirection status code 300. If set to
false, a status of 300 will raise the ``MultipleRedirectionException``.
