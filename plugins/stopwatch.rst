Stopwatch Plugin
================

Install
-------

.. code-block:: bash

    $ composer require php-http/stopwatch-plugin

Usage
-----

The ``StopwatchPlugin`` records the duration of HTTP requests with a
``Symfony\Component\Stopwatch\Stopwatch`` instance::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\StopwatchPlugin;
    use Symfony\Component\Stopwatch\Stopwatch;

    $stopwatch = new Stopwatch();

    $stopwatchPlugin = new StopwatchPlugin($stopwatch);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$stopwatchPlugin]
    );

    // ...

    foreach ($stopwatch->getSections() as $section) {
        foreach ($section->getEvents() as $name => $event) {
            echo sprintf('Request %s took %s ms and used %s bytes of memory', $name, $event->getDuration(), $event->getMemory());
        }
    }

.. warning::

    The results of the stop watch will be unreliable when using an asynchronous client. Execution
    time can be longer than it really was, depending on when the status was checked again, and
    memory consumption will be mixed up with other code that was executed while waiting for the
    response.
