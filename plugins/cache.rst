Cache Plugin
============

Install
-------

.. code-block:: bash

    $ composer require php-http/cache-plugin

Usage
-----

The ``CachePlugin`` allows you to cache responses from the server. It can use
any PSR-6 compatible caching engine. By default, the plugin respects the cache
control headers from the server as specified in :rfc:`7234`. It needs a
:ref:`stream <stream-factory>` and a `PSR-6`_ implementation::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\CachePlugin;

    /** @var \Psr\Cache\CacheItemPoolInterface $pool */
    $pool = ...
    /** @var \Http\Message\StreamFactory $streamFactory */
    $streamFactory = ...

    $options = [];
    $cachePlugin = new CachePlugin($pool, $streamFactory, $options);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$cachePlugin]
    );

Options
-------

The third parameter to the ``CachePlugin`` constructor takes an array of options. The plugin has four options you can
configure. Their default values and meaning is described by the table below.

+---------------------------+---------------------+------------------------------------------------------+
| Name                      | Default value       | Description                                          |
+===========================+=====================+======================================================+
| ``default_ttl``           | ``0``               | The default max age of a Response                    |
+---------------------------+---------------------+------------------------------------------------------+
| ``respect_cache_headers`` | ``true``            | Whatever or not we should care about cache headers   |
+---------------------------+---------------------+------------------------------------------------------+
| ``cache_lifetime``        | 30 days             | The minimum time we should store a cache item        |
+---------------------------+---------------------+------------------------------------------------------+
| ``methods``               | ``['GET', 'HEAD']`` | Which request methods to cache                       |
+---------------------------+---------------------+------------------------------------------------------+

.. note::

    A HTTP response may have expired but it is still in cache. If so, headers like ``If-Modified-Since`` and
    ``If-None-Match`` are added to the HTTP request to allow the server answer with 304 status code. When
    a 304 response is received we update the CacheItem and save it again for at least ``cache_lifetime``.

Using these options together you can control how your responses should be cached. By default, responses with no
cache control headers are not cached. If you want a default cache lifetime if the server specifies no ``max-age``, use::

    $options = [
        'default_ttl' => 42, // cache lifetime time in seconds
    ];

You can tell the plugin to completely ignore the cache control headers from the server and force caching the response
for the default time to live. The options below will cache all responses for one hour::

    $options = [
        'default_ttl' => 3600, // cache for one hour
        'respect_cache_headers' => false,
    ];

Semantics of null values
````````````````````````

Setting null to the options ``cache_lifetime`` or ``default_ttl`` means "Store this as long as you can (forever)".
This could be a great thing when you requesting a pay-per-request API (e.g. GoogleTranslate).

Store a response as long the cache implementation allows::

    $options = [
        'default_ttl' => null,
        'respect_cache_headers' => false,
        'cache_lifetime' => null,
    ];


Ask the server if the response is valid at most ever hour. Store the cache item forever::

    $options = [
        'default_ttl' => 3600,
        'respect_cache_headers' => false,
        'cache_lifetime' => null,
    ];


Ask the server if the response is valid at most ever hour. If the response has not been used within one year it will be
removed from the cache::

    $options = [
        'default_ttl' => 3600,
        'respect_cache_headers' => false,
        'cache_lifetime' => 86400*365, // one year
    ];

Caching of different request methods
````````````````````````````````````

Most of the time you should not change the ``methods`` option. However if you are working for example with HTTPlug
based SOAP client you might want to additionally enable caching of POST requests::

    $options = [
        'methods' => ['GET', 'HEAD', 'POST'],
    ];

You can cache any valid request method.

.. note::

    If your system has both normal and SOAP clients you need to use two different ``PluginClient`` instances. SOAP
    client should use ``PluginClient`` with POST caching enabled and normal client with POST caching disabled.

Cache Control Handling
----------------------

This plugin does not cache responses with ``no-store`` or ``private`` instructions.

It does store responses with cookies or a ``Set-Cookie`` header. Be careful with
the order of your plugins.

.. _PSR-6: http://www.php-fig.org/psr/psr-6/
