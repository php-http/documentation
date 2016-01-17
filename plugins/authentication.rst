Authentication Plugin
=====================

This plugin uses the :doc:`authentication component </message/authentication>`
from ``php-http/message`` to authenticate requests sent through the client::

    use Http\Discovery\HttpClientDiscovery;
    use Http\Message\Authentication\BasicAuth;
    use Http\Client\Plugin\PluginClient;
    use Http\Client\Plugin\AuthenticationPlugin;

    $authentication = new BasicAuth('username', 'password');
    $authenticationPlugin = new AuthenticationPlugin($authentication);

    $pluginClient = new PluginClient(
        HttpClientDiscovery::find(),
        [$authenticationPlugin]
    );

Check the :doc:`authentication component documentation </message/authentication>`
for the list of available authentication methods.
