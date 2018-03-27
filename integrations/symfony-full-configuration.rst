Full configuration
==================

This page shows an example of all configuration values provided by the bundle.

.. code-block:: yaml

    // config.yml
    httplug:
        main_alias:
            client: httplug.client.default
            message_factory: httplug.message_factory.default
            uri_factory: httplug.uri_factory.default
            stream_factory: httplug.stream_factory.default
        classes:
            # uses discovery if not specified
            client: ~
            message_factory: ~
            uri_factory: ~
            stream_factory: ~

        plugins: # Global plugin configuration. Plugins need to be explicitly added to clients.
            authentication:
                my_basic:
                    type: 'basic'
                    username: 'my_username'
                    password: 'p4ssw0rd'
                my_wsse:
                    type: 'wsse'
                    username: 'my_username'
                    password: 'p4ssw0rd'
                my_bearer:
                    type: 'bearer'
                    token: 'authentication_token_hash'
                my_service:
                    type: 'service'
                    service: 'my_authentication_service'
            cache:
                cache_pool: 'my_cache_pool'
                stream_factory: 'httplug.stream_factory'
                config:
                    default_ttl: 3600
                    respect_cache_headers: true
                    cache_key_generator: null # This must be a service id to a service implementing 'Http\Client\Common\Plugin\Cache\Generator\CacheKeyGenerator'. If 'null' 'Http\Client\Common\Plugin\Cache\Generator\SimpleGenerator' will be used.
            cookie:
                cookie_jar: my_cookie_jar
            decoder:
                use_content_encoding: true
            history:
                journal: my_journal
            logger:
                logger: 'logger'
                formatter: null
            redirect:
                preserve_header: true
                use_default_for_multiple: true
            retry:
                retry: 1
            stopwatch:
                stopwatch: 'debug.stopwatch'

        profiling:
            enabled: true # Defaults to kernel.debug
            formatter: null # Defaults to \Http\Message\Formatter\FullHttpMessageFormatter
            captured_body_length: 0

        discovery:
            client: 'auto'
            async_client: false

        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                service: 'my_service'       # Can not be used with "factory" or "config"
                flexible_client: false      # Can only be true if http_methods_client is false
                http_methods_client: false  # Can only be true if flexible_client is false
                config:
                    # Options to the Guzzle 6 constructor
                    timeout: 2
                plugins:
                    # Can reference a globally configured plugin service
                    - 'httplug.plugin.authentication.my_wsse'
                    # Can configure a plugin customized for this client
                    - cache:
                        cache_pool: 'my_other_pool'
                        config:
                            default_ttl: 120
                    # Can configure plugins that can not be configured globally
                    - add_host:
                        # Host name including protocol and optionally the port number, e.g. https://api.local:8000
                        host: http://localhost:80 # Required
                        # Whether to replace the host if request already specifies it
                        replace: false
                    - add_path:
                        # Path to be added, e.g. /api/v1
                        path: /api/v1 # Required
                    - base_uri:
                        # Base Uri including protocol, optionally the port number and prepend path, e.g. https://api.local:8000/api
                        uri: http://localhost:80 # Required
                        # Whether to replace the host if request already specifies one
                        replace: false
                    # Append headers to the request. If the header already exists the value will be appended to the current value.
                    - header_append:
                        # Keys are the header names, values the header values
                        headers:
                            'X-FOO': bar # contrary to default symfony behaviour, hyphens "-" are NOT translated to underscores "_" for the headers.
                    # Set header to default value if it does not exist.
                    - header_defaults:
                        # Keys are the header names, values the header values
                        headers:
                            'X-FOO': bar
                    # Set headers to requests. If the header does not exist it wil be set, if the header already exists it will be replaced.
                    - header_set:
                        # Keys are the header names, values the header values
                        headers:
                            'X-FOO': bar
                    # Remove headers from requests.
                    - header_remove:
                        # List of header names to remove
                        headers: ["X-FOO"]
