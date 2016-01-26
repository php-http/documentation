Promise
=======

A promise represents a single result of an asynchronous operation.
It is not necessarily available at a specific time, but should become in the future.

The PHP-HTTP promise follows the `Promises/A+`_ standard.

.. note::

    Work is underway for a `Promise PSR`_. When that PSR has been released, we
    will use it in HTTPlug and deprecate our ``Http\Promise\Promise`` interface.

Asynchronous requests
---------------------

Asynchronous requests enable non-blocking HTTP operations.
When sending asynchronous HTTP requests, a promise is returned. The promise acts
as a proxy for the response or error result, which is not yet known.

To execute such a request with HTTPlug::

    $request = $messageFactory->createRequest('GET', 'http://php-http.org');

    // Where $client implements HttpAsyncClient
    $promise = $client->sendAsyncRequest($request);

    // This code will be executed right after the request is sent, but before
    // the response is returned.
    echo 'Wow, non-blocking!';

See :ref:`message-factory` on how to use message factories.

Although the promise itself is not restricted to resolve a specific result type,
in HTTP context it resolves a PSR-7 ``Psr\Http\Message\ResponseInterface`` or fails with an ``Http\Client\Exception``.

Wait
----

The ``$promise`` that is returned implements ``Http\Promise\Promise``. At this
point in time, the response is not known yet. You can be polite and wait for
that response to arrive::

    try {
        $response = $promise->wait();
    } catch (\Exception $exception) {
        echo $exception->getMessage();
    }

Then
----

Instead of waiting, however, you can handle things asynchronously. Call the
``then`` method with two arguments: one callback that will be executed if the
request turns out to be successful and/or a second callback that will be
executed if the request results in an error::

    $promise->then(
        // The success callback
        function (ResponseInterface $response) {
            echo 'Yay, we have a shiny new response!';

            // Write status code to some log file
            file_put_contents('responses.log', $response->getStatusCode() . "\n", FILE_APPEND);

            return $response;
        },

        // The failure callback
        function (\Exception $exception) {
            echo 'Oh darn, we have a problem';

            throw $exception;
        }
    );

.. _`Promise PSR`: https://groups.google.com/forum/?fromgroups#!topic/php-fig/wzQWpLvNSjs
.. _Promises/A+: https://promisesaplus.com
