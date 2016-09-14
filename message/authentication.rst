Authentication
==============

The Authentication component allows you to to implement authentication methods which can simply update the request
with authentication detail (for example by adding an ``Authorization`` header).
This is useful when you have to send multiple requests to the same endpoint. Using an authentication implementation,
these details can be separated from the actual requests.


Installation
^^^^^^^^^^^^

.. code-block:: bash

    $ composer require php-http/message

Authentication methods
^^^^^^^^^^^^^^^^^^^^^^

+----------------+---------------------------------------------------+-----------------------------------------------------+
|Method          | Parameters                                        | Behavior                                            |
+================+===================================================+=====================================================+
| `Basic Auth`_  | Username and password                             | ``Authorization`` header of the HTTP specification  |
+----------------+---------------------------------------------------+-----------------------------------------------------+
|Bearer          | Token                                             | ``Authorization`` header of the HTTP specification  |
+----------------+---------------------------------------------------+-----------------------------------------------------+
|WSSE_           | Username and password                             | ``Authorization`` header of the HTTP specification  |
+----------------+---------------------------------------------------+-----------------------------------------------------+
|Query Params    | Array of param-value pairs                        | URI parameters                                      |
+----------------+---------------------------------------------------+-----------------------------------------------------+
|Chain           | Array of authentication instances                 | Behaviors of the underlying authentication methods  |
+----------------+---------------------------------------------------+-----------------------------------------------------+
|Matching        | An authentication instance and a matcher callback | Behavior of the underlying authentication method if |
|                |                                                   | the matcher callback passes                         |
+----------------+---------------------------------------------------+-----------------------------------------------------+

.. _`Basic Auth`: https://en.wikipedia.org/wiki/Basic_access_authentication
.. _WSSE: http://www.xml.com/pub/a/2003/12/17/dive.html

Integration with HTTPlug
^^^^^^^^^^^^^^^^^^^^^^^^

Normally requests must be authenticated "by hand" which is not really convenient.

If you use HTTPlug, you can integrate this component into the client using the
:doc:`authentication plugin </plugins/authentication>`.


Examples
^^^^^^^^

General usage looks like the following::

    $authentication = new AuthenticationMethod();

    /** @var Psr\Http\Message\RequestInterface */
    $authentication->authenticate($request);

Basic Auth
**********

.. code-block:: php

    use Http\Message\Authentication\BasicAuth;

    $authentication = new BasicAuth('username', 'password');

Bearer
******

.. code-block:: php

    use Http\Message\Authentication\Bearer;

    $authentication = new Bearer('token');

WSSE
****

.. code-block:: php

    use Http\Message\Authentication\Wsse;

    $authentication = new Wsse('username', 'password');

Query Params
************

``http://api.example.com/endpoint?access_token=9zh987g86fg87gh978hg9g79``::


    use Http\Message\Authentication\QueryParam;

    $authentication = new QueryParam([
        'access_token' => '9zh987g86fg87gh978hg9g79',
    ]);

.. warning::

    Using query parameters for authentication is not safe.
    Only use it when this is the only authentication method offered by a third party application.

Chain
*****

The idea behind this authentication method is that in some cases you might need to
authenticate the request with multiple methods.

For example it's a common practice to protect development APIs with Basic Auth and the regular token authentication as well
to protect the API from unnecessary processing::

    use Http\Message\Authentication\Chain;

    $authenticationChain = [
        new AuthenticationMethod1(),
        new AuthenticationMethod2(),
    ];

    $authentication = new Chain($authenticationChain);

Matching
********

With this authentication method you can conditionally add authentication details to your request by passing a callable
to it. When a request is passed, the callable is called and used as a boolean value in order to decide whether
the request should be authenticated or not.
It also accepts an authentication method instance which does the actual authentication when the condition is
fulfilled.

For example a common use case is to authenticate requests sent to certain paths::

    use Http\Message\Authentication\Matching;
    use Psr\Http\Message\RequestInterface;

    $authentication = new Matching(
        new AuthenticationMethod1(),
        function (RequestInterface $request) {
            $path = $request->getUri()->getPath();

            return 0 === strpos($path, '/api');
        }
    );

In order to ease creating matchers for URLs/paths, there is a static factory method for this purpose: ``createUrlMatcher``
The first argument is an authentication method, the second is a regular expression to match against the URL::

    use Http\Message\Authentication\Matching;

    $authentication = Matching::createUrlMatcher(new AuthenticationMethod(), '\/api');


Implement your own
^^^^^^^^^^^^^^^^^^

Implementing an authentication method is easy: only one method needs to be implemented::

    use Http\Message\Authentication\Authentication;
    use Psr\Http\Message\RequestInterface;

    class MyAuth implements Authentication
    {
        public function authenticate(RequestInterface $request)
        {
            // do something with the request

            // keep in mind that the request is immutable - return the updated
            // version of the request with the authentication information added
            // to it.
            return $request;
        }
    }
