Error Plugin
============

The ``ErrorPlugin`` transforms responses with HTTP error status codes into exceptions:

 * 400-499 status code are transformed into ``Http\Client\Common\Exception\ClientErrorException``;
 * 500-599 status code are transformed into ``Http\Client\Common\Exception\ServerErrorException``

.. warning::

    Throwing an exception on a valid response violates the PSR-18 specification.
    This plugin is provided as a convenience when writing a small application.
    When providing a client to a third party library, this plugin must not be
    included, or the third party library will have problems with error handling.

Both exceptions extend the ``Http\Client\Exception\HttpException`` class, so you can fetch the request
and the response coming from them::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Client\Common\PluginClient;
    use Http\Client\Common\Plugin\ErrorPlugin;
    use Http\Client\Common\Exception\ClientErrorException;

    $errorPlugin = new ErrorPlugin();

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$errorPlugin]
    );

    ...

    try {
        $response = $pluginClient->sendRequest($request);
    } catch (ClientErrorException $e) {
        if ($e->getResponse()->getStatusCode() == 404) {
            // Something has not been found
        }
    }

The error plugin is intended for when an application operates with the client directly. When
writing a library around an API, the best practice is to have the client convert responses into
domain objects, and transform HTTP errors into meaningful domain exceptions. In that scenario,
the ErrorPlugin is not needed. It is more efficient to check the HTTP status codes yourself than
throwing and catching exceptions.

If your application handles responses with 4xx status codes, but needs exceptions for 5xx status codes only, 
you can set the option ``only_server_exception`` to ``true``::

    $errorPlugin = new ErrorPlugin(['only_server_exception' => true]);
