Error Plugin
============

The ``ErrorPlugin`` transforms responses with HTTP error status codes into exceptions:

 * 400-499 status code are transformed into ``Http\Client\Common\Exception\ClientErrorException``;
 * 500-599 status code are transformed into ``Http\Client\Common\Exception\ServerErrorException``

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
