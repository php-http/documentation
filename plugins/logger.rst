Logger Plugin
=============

Install
-------

.. code-block:: bash

    $ composer require php-http/logger-plugin

Usage
-----

The ``LoggerPlugin`` converts requests, responses and exceptions to strings and logs them with a PSR3_
compliant logger::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\LoggerPlugin;
    use Monolog\Logger;

    $loggerPlugin = new LoggerPlugin(new Logger('http'));

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$loggerPlugin]
    );

The log level for exceptions is ``error``, the request and responses without exceptions are logged at level ``info``.
Request and response/errors can be correlated by looking at the ``uid`` of the log context.
If you don't want to normally log requests, you can set the logger to normally only log ``error`` but use the
``Fingerscrossed`` logger of Monolog to also log the request in case an exception is encountered.

By default it uses ``Http\Message\Formatter\SimpleFormatter`` to format the request or the response into a string.
You can use any formatter implementing the ``Http\Message\Formatter`` interface::

    $formatter = new \My\Formatter\Implementation();

    $loggerPlugin = new LoggerPlugin(new Logger('http'), $formatter);

.. _PSR3: http://www.php-fig.org/psr/psr-3/
