Retry Plugin
============

The ``RetryPlugin`` can automatically attempt to re-send a request that failed,
to work around unreliable connections and servers. It re-sends the request when
an exception is thrown, unless the exception is a HttpException for a status
code in the 5xx server error range. Since version 2.0, responses with status
codes in the 5xx range are also retried. Each retry attempt is delayed by an
exponential backoff time.

See below for how to configure that behaviour.

.. warning::

    You should keep an eye on retried requests, as they add overhead. If a
    request fails due to a client side mistake, retrying is only a waste of
    time and resources.

Contrary to the :doc:`redirect`, the retry plugin does not restart the chain
but simply tries again from the current position.

Async
-----

This plugin is not fully compatible with asynchronous behavior, as the wait
between retries is done with a blocking call to a sleep function.

Options
-------

``retries``: int (default: 1)

Number of retry attempts to make before giving up.

``error_response_decider``: callable (default: retry if status code is in 5xx range)

A callback function that gets the request and response to decide whether the
request should be retried.

``exception_decider``: callable (default: retry if not a HttpException or status code is in 5xx range)

A callback function that gets a request and an exception to decide after a
failure whether the request should be retried.

``error_response_delay``: callable (default: exponential backoff)

A callback that gets a request and response and the current number of retries
and returns how many microseconds we should wait before trying again.

``exception_delay``: callable (default behaviour: exponential backoff)

A callback that receives a request, an exception, the current number of retries 
and returns how many microseconds we should wait before trying again.

Interaction with Exceptions
---------------------------

If you use the :doc:`ErrorPlugin <error>`, you should place it after the RetryPlugin in the
plugin chain::

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
