Building Custom Plugins
=======================

When writing your own Plugin, you need to be aware that the Plugin Client is async first.
This means that every plugin must be written with Promises. More about this later.

Each plugin must implement the ``Http\Client\Plugin\Plugin`` interface.

This interface defines the ``handleRequest`` method that allows to modify behavior of the call::

    /**
     * Handles the request and returns the response coming from the next callable.
     *
     * @param RequestInterface $request Request to use.
     * @param callable         $next    Callback to call to have the request, it muse have the request as it first argument.
     * @param callable         $first   First element in the plugin chain, used to to restart a request from the beginning.
     *
     * @return Promise
     */
    public function handleRequest(RequestInterface $request, callable $next, callable $first);

The ``$request`` comes from an upstream plugin or Plugin Client itself.
You can replace it and pass a new version downstream if you need.

.. note::

    Be aware that the request is immutable.

The ``$next`` callable is the next plugin in the execution chain. When you need to call it, you must pass the ``$request``
as the first argument of this callable.

For example a simple plugin setting a header would look like this::

    public function handleRequest(RequestInterface $request, callable $next, callable $first)
    {
        $newRequest = $request->withHeader('MyHeader', 'MyValue');

        return $next($newRequest);
    }

The ``$first`` callable is the first plugin in the chain. It allows you to completely reboot the execution chain, or send
another request if needed, while still going through all the defined plugins.
Like in case of the ``$next`` callable, you must pass the ``$request`` as the first argument::

    public function handleRequest(RequestInterface $request, callable $next, callable $first)
    {
        if ($someCondition) {
            $newRequest = new Request();
            $promise = $first($newRequest);

            // Use the promise to do some jobs ...
        }

        return $next($request);
    }

.. warning::

    In this example the condition is not superfluous:
    you need to have some way to not call the ``$first`` callable each time
    or you will end up in an infinite execution loop.

The ``$next`` and ``$first`` callables will return a :doc:`/components/promise`.
You can manipulate the ``ResponseInterface`` or the ``Exception`` by using the
``then`` method of the promise::

    public function handleRequest(RequestInterface $request, callable $next, callable $first)
    {
        $newRequest = $request->withHeader('MyHeader', 'MyValue');

        return $next($request)->then(function (ResponseInterface $response) {
            return $response->withHeader('MyResponseHeader', 'value');
        }, function (Exception $exception) {
            echo $exception->getMessage();

            throw $exception;
        });
    }

.. warning::

    Contract for the ``Http\Promise\Promise`` is temporary until a
    PSR_ is released. Once it is out, we will use this PSR in HTTPlug and
    deprecate the old contract.

To better understand the whole process check existing implementations in the
`plugin repository`_.

Contributing Your Plugins to PHP-HTTP
-------------------------------------

We are open to contributions. If the plugin is of general interest and is not too complex, the best
is to do a Pull Request to ``php-http/plugins``. Please see the :doc:`contribution guide <../development/contributing>`.
We don't promise that every plugin gets merged into the core. We need to keep the core as small as
possible with only the most widely used plugins to keep it maintainable.

The alternative is providing your plugins in your own repository. Please let us know when you do,
we would like to add a list of existing third party plugins to the list of plugins.

.. _PSR: https://groups.google.com/forum/?fromgroups#!topic/php-fig/wzQWpLvNSjs
.. _plugin repository: https://github.com/php-http/plugins