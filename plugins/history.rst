History Plugin
==============

History plugin use a `Http\Client\Plugin\Journal` to collect successful or failed calls of an Http Client. This is
mainly used for debugging like in the Symfony Bundle to get information in the debug toolbar with a DataCollector::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\HistoryPlugin;

    $historyPlugin = new HistoryPlugin(new \My\Journal\Implementation());

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$historyPlugin]
    );

