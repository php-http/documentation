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


The ``CachePlugin`` has also 2 factory methods to easily set up the plugin by caching type. See the example below.

.. code-block:: php

    // This will allow caching responses with the 'private' and/or 'no-store' cache directives
    $cachePlugin = CachePlugin::clientCache($pool, $streamFactory, $options);

    // Returns a cache plugin with the current default behavior
    $cachePlugin = CachePlugin::serverCache($pool, $streamFactory, $options);

.. note::

    The two factory methods have been added in version 1.3.0.

Options
-------

The third parameter to the ``CachePlugin`` constructor takes an array of options. The available options are:

+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| Name                                  | Default value                                      | Description                                                           |
+=======================================+====================================================+=======================================================================+
| ``default_ttl``                       | ``0``                                              | The default max age of a Response                                     |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| ``respect_cache_headers``             | ``true``                                           | Whether we should care about cache headers or not                     |
|                                       |                                                    | * This option is deprecated. Use  `respect_response_cache_directives` |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| ``hash_algo``                         | ``sha1``                                           | The hashing algorithm to use when generating cache keys               |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| ``cache_lifetime``                    | 30 days                                            | The minimum time we should store a cache item                         |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| ``methods``                           | ``['GET', 'HEAD']``                                | Which request methods to cache                                        |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| ``respect_response_cache_directives`` | ``['no-cache', 'private', 'max-age', 'no-store']`` | A list of cache directives to respect when caching responses          |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| ``cache_key_generator``               | ``new SimpleGenerator()``                          | A class implementing ``CacheKeyGenerator`` to generate a PSR-6 cache  |
|                                       |                                                    | key.                                                                  |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| ``cache_listeners``                   | ``[]``                                             | A array of classes implementing ``CacheListener`` to act on a         |
|                                       |                                                    | response with information on its cache status.                        |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+
| ``blacklisted_paths``                 | ``[]``                                             | A array of regular expressions to defined paths, that shall not be    |
|                                       |                                                    | cached.                                                               |
+---------------------------------------+----------------------------------------------------+-----------------------------------------------------------------------+


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
        'respect_response_cache_directives' => [],
    ];


Generating a cache key
``````````````````````

You may define a method how the PSR-6 cache key should be generated. The default generator is ``SimpleGenerator`` which
is using the request method, URI and body of the request. The cache plugin does also include a ``HeaderCacheKeyGenerator``
which allow you to specify what HTTP header you want include in the cache key.

Controlling cache listeners
```````````````````````````

One or more classes implementing ``CacheListener`` can be added through ``cache_listeners``. These classes receive a
notification on whether a request was a cache hit or miss, and can optionally mutate the response based on those signals.
As an example, adding the provided ``AddHeaderCacheListener`` will mutate the response, adding an ``X-Cache`` header with
a value ``HIT`` or ``MISS``, which can be useful in debugging.


Semantics of null values
````````````````````````

Setting null to the options ``cache_lifetime`` or ``default_ttl`` means "Store this as long as you can (forever)".
This could be a great thing when you requesting a pay-per-request API (e.g. GoogleTranslate).

Store a response as long the cache implementation allows::

    $options = [
        'default_ttl' => null,
        'respect_response_cache_directives' => [],
        'cache_lifetime' => null,
    ];


Ask the server if the response is valid at most ever hour. Store the cache item forever::

    $options = [
        'default_ttl' => 3600,
        'respect_response_cache_directives' => [],
        'cache_lifetime' => null,
    ];


Ask the server if the response is valid at most ever hour. If the response has not been used within one year it will be
removed from the cache::

    $options = [
        'default_ttl' => 3600,
        'respect_response_cache_directives' => [],
        'cache_lifetime' => 86400*365, // one year
    ];

Caching of different request methods
````````````````````````````````````

Most of the time you should not change the ``methods`` option. However if you are working for example with HTTPlug
based SOAP client you might want to additionally enable caching of ``POST`` requests::

    $options = [
        'methods' => ['GET', 'HEAD', 'POST'],
    ];

The ``methods`` setting overrides the defaults. If you want to keep caching ``GET`` and ``HEAD`` requests, you need
to include them. You can specify any uppercase request method which conforms to :rfc:`7230`.

.. note::

    If your system has both normal and SOAP clients you need to use two different ``PluginClient`` instances. SOAP
    client should use ``PluginClient`` with POST caching enabled and normal client with POST caching disabled.

Cache Control Handling
----------------------

By default this plugin does not cache responses with ``no-store``, ``no-cache`` or ``private`` instructions. Use
``CachePlugin::clientCache($pool, $streamFactory, $options);`` to cache ``no-store`` or ``private`` responses or change
the ``respect_response_cache_directives`` option to your needs.

It does store responses with cookies or a ``Set-Cookie`` header. Be careful with
the order of your plugins.

.. _PSR-6: http://www.php-fig.org/psr/psr-6/
