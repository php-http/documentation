HTTPlug tutorial
================

This tutorial should give you an idea how to use HTTPlug in your project. HTTPlug has two main use cases:

1. Usage in your project;
2. Usage in a reusable package.

This tutorial will start with the first use case and then explain the special considerations to
take into account when building a reusable package.

We use Composer_ for dependency management. Install it if you don't have it yet.

Setting up the project
----------------------

.. code-block:: bash

    mkdir httplug-tutorial
    cd httplug-tutorial
    composer init
    # specify your information as you want. say no to defining the dependencies interactively
    composer require php-http/guzzle6-adapter

The last command will install Guzzle as well as the Guzzle HTTPlug adapter and the required interface repositories.
We are now ready to start coding.


Writing some simple code
------------------------

Create a file ``demo.php`` in the root folder and write the following code::

    <?php
    require('vendor/autoload.php');

    TODO: create client instance with discovery and do some requests


Using an asynchronous client
----------------------------

Asynchronous client accepts a PSR-7 ``RequestInterface`` and returns a ``Http\Promise\Promise``::

    use Http\Discovery\HttpAsyncClientDiscovery;

    $httpAsyncClient = HttpAsyncClientDiscovery::find();
    $promise = $httpAsyncClient->sendAsyncRequest($request);

Using callback system
^^^^^^^^^^^^^^^^^^^^^

This promise allows you to add callbacks for when the response is available or an errors happens by using the then method::

    $promise->then(function (ResponseInterface $response) {
        // onFulfilled callback
        echo 'The response is available';

        return $response;
    }, function (Exception $e) {
        // onRejected callback
        echo 'An error happens';

        throw $e;
    });

This method will return another promise so you can manipulate the response and/or exception and
still provide a way to interact with this object for your users::

    $promise->then(function (ResponseInterface $response) {
        // onFulfilled callback
        echo 'The response is available';

        return $response;
    }, function (Exception $e) {
        // onRejected callback
        echo 'An error happens';

        throw $e;
    })->then(function (ResponseInterface $response) {
        echo 'Response still available';

        return $response;
    }, function (Exception $e) {
         throw $e
    });

In order to achieve the chain callback, if you read previous examples carefully,
callbacks provided to the ``then`` method *must*  return a PSR-7_ ``ResponseInterface`` or throw a ``Http\Client\Exception``.
For both of the callbacks, if it returns a PSR-7 ``ResponseInterface``  it will call the ``onFulfilled`` callback for
the next element in the chain, if it throws a ``Http\Client\Exception`` it will call the ``onRejected`` callback.

i.e. you can inverse the behavior of a call::

    $promise->then(function (ResponseInterface $response) use($request) {
        // onFulfilled callback
        echo 'The response is available, but it\'s not ok...';

        throw new HttpException('My error message', $request, $response);
    }, function (Exception $e) {
        // onRejected callback
        echo 'An error happens, but it\'s ok...';

        return $exception->getResponse();
    });

Calling the ``wait`` method on the promise will wait for the response or exception to be available and
invoke callback provided in the ``then`` method.

Using the promise directly
^^^^^^^^^^^^^^^^^^^^^^^^^^

If you don't want to use the callback system, you can also get the state of the promise with ``$promise->getState()``
will return of one ``Promise::PENDING``, ``Promise::FULFILLED`` or ``Promise::REJECTED``.

Then you can get the response of the promise if it's in ``FULFILLED`` state with ``$promise->getResponse()`` call or
get the error of the promise if it's in ``REJECTED`` state with ``$promise->getRequest()`` call

Example
^^^^^^^

Here is a full example of a classic usage when using the ``sendAsyncRequest`` method::

    use Http\Discovery\HttpAsyncClientDiscovery;

    $httpAsyncClient = HttpAsyncClientDiscovery::find();

    $promise = $httpAsyncClient->sendAsyncRequest($request);
    $promise->then(function (ResponseInterface $response) {
       echo 'The response is available';

       return $response;
    }, function (Exception $e) {
       echo 'An error happens';

       throw $e;
    });

    // Do some stuff not depending on the response, calling another request, etc ..
    ...

    // We need now the response for our final treatment
    $promise->wait();

    if (Promise::FULFILLED === $promise->getState()) {
        $response = $promise->getResponse();
    } else {
        throw new \Exception('Response not available');
    }

    // Do your stuff with the response
    ...

Handling errors
---------------

TODO: explain how to handle exceptions, distinction between network exception and HttpException.

Writing a reusable package
--------------------------

See :ref:`httplug-building-reusable-library`
