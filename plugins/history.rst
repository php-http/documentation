History Plugin
==============

The ``HistoryPlugin`` notifies a ``Http\Client\Plugin\Journal`` of all
successful and failed calls::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\HistoryPlugin;

    $historyPlugin = new HistoryPlugin(new \My\Journal\Implementation());

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$historyPlugin]
    );


As an example, HttplugBundle uses this plugin to collect responses and exceptions associated with
requests for the debug toolbar.

This plugin only collects data after resolution. For logging purposes, it is recommended to use
the :doc:`LoggerPlugin <logger>` instead, which logs events as they occur.
