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

.. note::

    An asynchronous request will never throw an exception directly but always
    return a promise. All exceptions SHOULD implement ``Http\Client\Exception``.
    See :doc:`../httplug/exceptions` for more information on the exceptions
    you might encounter.

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

The failure callback can also return a ``Promise``. This can be useful to implement a retry
mechanism, as follows::

    use Http\Discovery\HttpAsyncClientDiscovery;
    use Http\Discovery\Psr17FactoryDiscovery;

    $client = HttpAsyncClientDiscovery::find();
    $requestFactory = Psr17FactoryDiscovery::findRequestFactory();
    $retries = 2; // number of HTTP retries
    $request = $requestFactory->createRequest("GET", "http://localhost:8080/test");

    // success callback
    $success = function (ResponseInterface $response) {
        return $response;
    };
    // failure callback
    $failure = function (Exception $e) use ($client, $request) {
        // $request can be changed, e.g. using a Round-Robin algorithm

        // try another execution
        return $client->sendAsyncRequest($request);
    };

    $promise = $client->sendAsyncRequest($request);
    for ($i=0; $i < $retries; $i++) {
        $promise = $promise->then($success, $failure);
    }
    // Add the last callable to manage the exceeded maximum number of retries
    $promise->then($success, function(\Exception $e) {
        throw new \Exception(sprintf(
            "Exceeded maximum number of retries (%d): %s",
            $retries,
            $e->getMessage()
        ));
    });

.. _`Promise PSR`: https://groups.google.com/forum/?fromgroups#!topic/php-fig/wzQWpLvNSjs
.. _Promises/A+: https://promisesaplus.com
