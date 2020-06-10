VCR Plugin - Record and Replay Responses
========================================

The VCR plugins allow you to record & replay HTTP responses. It's very useful for test purpose (using production-like predictable fixtures and avoid making actual HTTP request).
You can also use it during your development cycle, when the endpoint you're contacting is not ready yet.

Unlike the :doc:`php-http/mock-client </clients/mock-client>`, where you have to manually define responses, the responses are **automatically** generated from the previously recorded ones.

Install
-------

.. code-block:: bash

    $ composer require --dev php-http/vcr-plugin

Usage
-----

To record or replay a response, you will need two components, a **naming strategy** and a **recorder**.

The naming strategy
*******************

The naming strategy turn a request into a deterministic and unique identifier.
The identifier must be safe to use with a file system.
The plugin provide a default naming strategy, the ``PathNamingStrategy``. You can define two options:

* **hash_headers**: the list of header(s) that make the request unique (Ex: 'Authorization'). The name & content of the header will be hashed to generate a unique signature. By default no header is used.
* **hash_body_methods**: indicate for which request methods the body makes requests distinct. (Default: PUT, POST, PATCH)

This naming strategy will turn a GET request to https://example.org/my-path to the ``example.org_GET_my-path`` name, and optionally add hashes if the request
contain a header defined in the options, or if the method is not idempotent.

To create your own strategy, you need to create a class implementing ``Http\Client\Plugin\Vcr\NamingStrategy\NamingStrategyInterface``.

The recorder
************

The recorder records and replays responses. The plugin provides two recorders:

* ``FilesystemRecorder``: Saves the response on your file system using Symfony's `filesystem component`_ and `Guzzle PSR7`_ library.
* ``InMemoryRecorder``: Saves the response in memory. **Response will be lost at the end of the running process**

To create your own recorder, you need to create a class implementing the following interfaces:

* ``Http\Client\Plugin\Vcr\Recorder\RecorderInterface`` used by the RecordPlugin.
* ``Http\Client\Plugin\Vcr\Recorder\PlayerInterface`` used by the ReplayPlugin.

The plugins
***********

There are two plugins, one to record responses, the other to replay them.

* ``Http\Client\Plugin\Vcr\ReplayPlugin``, use a ``PlayerInterface`` to replay previously recorded responses.
* ``Http\Client\Plugin\Vcr\RecordPlugin``, use a ``RecorderInterface`` instance to record the responses,

Both plugins add a response header to indicate either under which name the response has been stored (RecordPlugin, ``X-VCR-RECORD`` header), or which response name has been used to replay the request (ReplayPlugin, ``X-VCR-REPLAYED`` header).

If you plan on using both plugins at the same time (Replay or Record), the ``ReplayPlugin`` **must always** come first.
Please also note that by default, the ``ReplayPlugin`` throws an exception when it cannot replay a request. If you want the plugin to continue the request (possibly to the actual server), set the third constructor argument to ``false`` (See example below).

Example
*******

.. code-block:: php

    <?php

    use Http\Client\Common\PluginClient;
    use Http\Client\Plugin\Vcr\NamingStrategy\PathNamingStrategy;
    use Http\Client\Plugin\Vcr\Recorder\FilesystemRecorder;
    use Http\Client\Plugin\Vcr\RecordPlugin;
    use Http\Client\Plugin\Vcr\ReplayPlugin;
    use Http\Discovery\HttpClientDiscovery;

    $namingStrategy = new PathNamingStrategy([
        'hash_headers' => ['X-Custom-Header'], // None by default
        'hash_body_methods' => ['POST'], // Default: PUT, POST, PATCH
    ]);
    $recorder = new FilesystemRecorder('some/dir/in/vcs'); // You can use InMemoryRecorder as well

    // To record responses:
    $record = new RecordPlugin($namingStrategy, $recorder);

    // To replay responses:
    // Third argument prevent the plugin from throwing an exception when a request cannot be replayed
    $replay = new ReplayPlugin($namingStrategy, $recorder, false);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$replay, $record] // Replay should always go first
    );

    /** @var \Psr\Http\Message\RequestInterface $request */
    $request = new MyRequest('GET', 'https://httplug.io');

    // Will be recorded in "some/dir/in/vcs"
    $client->sendRequest($request);

    // Will be replayed from "some/dir/in/vcs"
    $client->sendRequest($request);

.. _filesystem component: https://symfony.com/doc/current/components/filesystem.html
.. _Guzzle PSR7: https://github.com/guzzle/psr7
