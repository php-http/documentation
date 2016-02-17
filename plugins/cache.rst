Cache Plugin
============

The ``CachePlugin`` allows you to cache responses from the server. It can use
any PSR-6 compatible caching engine. By default, the plugin respects the cache
control headers from the server as specified in :rfc:`7234`. It needs a
:ref:`stream <stream-factory>` and a `PSR-6`_ implementation::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\CachePlugin;

    /** @var \Psr\Cache\CacheItemPoolInterface $pool */
    $pool...
    /** @var \Http\Message\StreamFactory $streamFactory */
    $streamFactory...

    $options = [];
    $cachePlugin = new CachePlugin($pool, $streamFactory, $options);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$cachePlugin]
    );

By default, responses with no cache control headers are not cached. If you want
a default cache lifetime if the server specifies no ``max-age``, use::

    $options = [
        'default_ttl' => 42, // cache lifetime time in seconds
    ];

You can also tell the plugin to completely ignore the cache control headers
from the server and force caching for the default time to life. Note that in
this case, ``default_ttl`` is required::

    $options = [
        'default_ttl' => 3600, // cache for one hour
        'respect_cache_headers' => false,
    ];

Cache Control Handling
----------------------

This plugin does not cache responses with ``no-store`` or ``private`` instructions.

It does store responses with cookies or a ``Set-Cookie`` header. Be careful with
the order of your plugins.

.. _PSR-6: http://www.php-fig.org/psr/psr-6/
