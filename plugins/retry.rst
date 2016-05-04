Retry Plugin
============

The ``RetryPlugin`` can automatically attempt to re-send a request that failed, to work around
unreliable connections and servers. It relies on errors to throw exceptions, so you probably want
to place the :doc:`error` later in the plugin chain::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\ErrorPlugin;
    use Http\Client\Common\Plugin\RetryPlugin;

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [
            new RetryPlugin(),
            new ErrorPlugin(),
        ]
    );

.. warning::

    You should keep an eye on retried requests, as they add overhead. If some request fails due to
    a client side mistake, retrying is only a waste of time and resources.

Contrary to the :doc:`redirect` the retry plugin does not restart the chain but simply try again
from the current position.

Options
-------

``retries``: int (default: 1)

Number of retry attempts to make before giving up.
