# Authentication Plugin

This plugin uses the [authentication component](http://docs.httplug.io/en/latest/components/authentication/)
from `php-http/message` to authenticate requests sent through the client.


``` php
use Http\Discovery\HttpClientDiscovery;
use Http\Message\Authentication\BasicAuth;
use Http\Plugins\PluginClient;
use Http\Plugins\AuthenticationPlugin;

$authentication = new BasicAuth('username', 'password');
$authenticationPlugin = new AuthenticationPlugin($authentication);

$pluginClient = new PluginClient(
    HttpClientDiscovery::find(),
    [$authenticationPlugin]
);
```

Check the [authentication component documentation](http://docs.httplug.io/en/latest/components/authentication/)
for the list of available authentication methods.
