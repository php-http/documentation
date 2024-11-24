Full configuration
==================

This page shows an example of all configuration values provided by the bundle.

.. hint::

    See :doc:`the plugin documentation <../plugins/index>` for more information
    on the plugins.

    If a plugin is not listed in the configuration reference below, you can
    configure it as a service and reference the plugin by service id as you
    would do for a :ref:`custom plugin <symfony_custom_plugin>`.

.. code-block:: yaml

    // config.yml
    httplug:
        # allows to disable autowiring of the clients
        default_client_autowiring: true
        # define which service to use as httplug.<type>
        # this does NOT change autowiring, which will always go to the "default" client
        main_alias:
            client: httplug.client.default
            psr17_request_factory: httplug.psr17_request_factory.default
            psr17_response_factory: httplug.psr17_response_factory.default
            psr17_uri_factory: httplug.psr17_uri_factory.default
            psr17_stream_factory: httplug.psr17_stream_factory.default
        classes:
            # uses discovery if not specified
            client: ~
            psr17_request_factory: ~
            psr17_response_factory: ~
            psr17_uri_factory: ~
            psr17_stream_factory: ~

        plugins: # Global plugin configuration. When configured here, plugins need to be explicitly added to clients by service name.
            authentication:
                # The names can be freely chosen, the authentication type is specified in the "type" option
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
                my_query_param:
                    type: 'query_param'
                    params:
                        access_token: '9zh987g86fg87gh978hg9g79'
                my_header:
                    type: 'header'
                    header_name: 'ApiKey'
                    header_value: '9zh987g86fg87gh978hg9g79'
                my_service:
                    type: 'service'
                    service: 'my_authentication_service'
            cache: # requires the php-http/cache-plugin package to be installed in your package
                cache_pool: 'my_cache_pool'
                stream_factory: 'httplug.stream_factory'
                config:
                    default_ttl: 3600
                    respect_response_cache_directives: ['no-cache', 'private', 'max-age', 'no-store']
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
            error:
                enabled: false
                only_server_exception: false
            throttle:
                name: default
                key: null
                tokens: 1
                max_time: 1

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
                public: null                # Set to true if you really cannot use dependency injection and need to make the client service public
                config:
                    # Options to the Guzzle 6 constructor
                    timeout: 2
                plugins:
                    # Can reference a globally configured plugin service
                    - 'httplug.plugin.authentication.my_wsse'
                    # Configure a plugin using a custom PluginConfigurator
                    - configurator:
                        id: App\Httplug\Plugin\MyPluginConfigurator
                        config:
                            foo: 'bar'
                            baz: 'qux'
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
                    # Set content-type header based on request body, if the header is not already set
                    - content_type:
                        # skip content-type detection if body is larger than size_limit
                        skip_detection: true
                        # size_limit in bytes for when skip_detection is enabled
                        size_limit: 200000
                    # Append headers to the request. If the header already exists the value will be appended to the current value.
                    - header_append:
                        # Keys are the header names, values the header values
                        headers:
                            'X-FOO': bar # contrary to default symfony behavior, hyphens "-" are NOT translated to underscores "_" for the headers.
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
                    # Sets query parameters to default value if they are not present in the request.
                    - query_defaults:
                        parameters:
                            locale: en
                    # Plugins to ensure the request resp response body is seekable
                    - request_seekable_body:
                        use_file_buffer: true
                        memory_buffer_size: 2097152
                    - response_seekable_body:
                        use_file_buffer: true
                        memory_buffer_size: 2097152
                    # Enable VCR plugin integration (Must be installed first).
                    - vcr:
                        mode: replay # record | replay | replay_or_record
                        fixtures_directory: '%kernel.project_dir%/fixtures/http' # mandatory for "filesystem" recorder
                        # recorder: filesystem  ## Can be filesystem, in_memory or the id of your custom recorder
                        # naming_strategy: service_id.of.naming_strategy # or "default"
                        # naming_strategy_options: # options for the default naming strategy, see VCR plugin documentation
                        #     hash_headers: []
                        #     hash_body_methods: []
