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

        plugins:
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
                enabled: true
                cache_pool: 'my_cache_pool'
                stream_factory: 'httplug.stream_factory'
                config:
                    default_ttl: 3600
                    respect_cache_headers: true
            cookie:
                enabled: true
                cookie_jar: my_cookie_jar
            decoder:
                enabled: true
                use_content_encoding: true
            history:
                enabled: true
                journal: my_journal
            logger:
                enabled: true
                logger: 'logger'
                formatter: null
            redirect:
                enabled: true
                preserve_header: true
                use_default_for_multiple: true
            retry:
                enabled: true
                retry: 1
            stopwatch:
                enabled: true
                stopwatch: 'debug.stopwatch'

        toolbar:
            enabled: true
            formatter: null # Defaults to \Http\Message\Formatter\FullHttpMessageFormatter
            captured_body_length: 0

        discovery:
            client: 'auto'
            async_client: false

        clients:
            acme:
                factory: 'httplug.factory.guzzle6'
                plugins: ['httplug.plugin.authentication.my_wsse', 'httplug.plugin.cache', 'httplug.plugin.retry']
                flexible_client: false      # Can only be true if http_methods_client is false
                http_methods_client: false  # Can only be true if flexible_client is false
                config:
                    verify: false
                    timeout: 2
                    # more options to the Guzzle 6 constructor

