VCR Plugin
==========

The VCR plugins allow you to record & replay HTTP responses.

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
The identifier must be safe to use with a filesystem.
The plugin provide a default naming strategy, the ``PathNamingStrategy``. You can define two options:

* **hash_headers**: the list of header names to hash (Ex: Authorization),
* **hash_body_methods**: methods for which the body will be hashed (Default: PUT, POST, PATCH)

This naming strategy will turn a GET request to https://example.org/my-path to the ``example.org_GET_my-path`` name, and optionally add hashes if the request
contain a header defined in the options, or if the method is not idempotent.

To create your own strategy, you need to create a class implementing ``Http\Client\Plugin\Vcr\NamingStrategy\NamingStrategyInterface``.

The recorder
************

The recorder records and replays responses. The plugin provide a two recorders:

* ``FilesystemRecorder``: Saves the response on your filesystem using Symfony's `filesystem component`_ and `Guzzle PSR7`_ library.
* ``InMemoryRecorder``: Saves the response in memory. **Response will be lost at the end of the running process**

To create your own recorder, you need to create a class implementing the following interfaces:

* ``Http\Client\Plugin\Vcr\Recorder\RecorderInterface`` used by the RecordPlugin.
* ``Http\Client\Plugin\Vcr\Recorder\PlayerInterface`` used by the ReplayPlugin.

The plugins
***********

VCR come built-in with two plugins:

* ``Http\Client\Plugin\Vcr\ReplayPlugin``, use a ``PlayerInterface`` to replay previously recorded responses.
* ``Http\Client\Plugin\Vcr\RecordPlugin``, use a ``RecorderInterface`` instance to record the responses,

If you plan on using both plugins at the same time (Replay or Record), the ``ReplayPlugin`` **must always** come first.
Please also note that by default, the ``ReplayPlugin`` throw an exception when it cannot replay a request, unless you set the third constructor argument to ``false`` (See example below).

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

    // Will be recorded in "some/dir/in/vcs"
    $client->sendRequest(//...);

    // Will be replayed from "some/dir/in/vcs"
    $client->sendRequest(//...);

.. _filesystem component: https://symfony.com/doc/current/components/filesystem.html
.. _Guzzle PSR7: https://github.com/guzzle/psr7