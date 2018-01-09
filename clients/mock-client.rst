Mock Client
===========


The mock client is a special type of client. It is a test double that does not
send the requests that you pass to it, but collects them instead. You can then
retrieve those request objects and make assertions about them. Additionally, you
can fake HTTP server responses and exceptions to validate how your code handles
them. This behavior is most useful in tests.

To install the Mock client, run:

.. code-block:: bash

    $ composer require php-http/mock-client

Collect Requests
----------------

To make assertions::

    use Http\Mock\Client;

    class YourTest extends \PHPUnit_Framework_TestCase
    {
        public function testRequests()
        {
            // $firstRequest and $secondRequest are Psr\Http\Message\RequestInterface
            // objects

            $client = new Client();
            $client->sendRequest($firstRequest);
            $client->sendRequest($secondRequest);

            $bothRequests = $client->getRequests();

            // Do your assertions
            $this->assertEquals('GET', $bothRequests[0]->getMethod());
            // ...
        }
    }

Fake Responses and Exceptions
-----------------------------

By default, the mock client returns an empty response with status 200.
You can set responses and exceptions the mock client should return / throw.
You can set several exceptions and responses, to have the client first throw
each exception once and then each response once on subsequent calls to send().
Additionally you can set a default response or a default exception to be used
instead of the empty response.

Test how your code behaves when the HTTP client throws exceptions or returns
certain responses::

    use Http\Mock\Client;

    class YourTest extends \PHPUnit_Framework_TestCase
    {
        public function testClientReturnsResponse()
        {
            $client = new Client();

            $response = $this->getMock('Psr\Http\Message\ResponseInterface');
            $client->addResponse($response);

            // $request is an instance of Psr\Http\Message\RequestInterface
            $returnedResponse = $client->sendRequest($request);
            $this->assertSame($response, $returnedResponse);
            $this->assertSame($request, $client->getLastRequest());
        }
    }

Or set a default response::

    use Http\Mock\Client;

    class YourTest extends \PHPUnit_Framework_TestCase
    {
        public function testClientReturnsResponse()
        {
            $client = new Client();

            $response = $this->getMock('Psr\Http\Message\ResponseInterface');
            $client->setDefaultResponse($response);

            // $firstRequest and $secondRequest are instances of Psr\Http\Message\RequestInterface
            $firstReturnedResponse = $client->sendRequest($firstRequest);
            $secondReturnedResponse = $client->sendRequest($secondRequest);
            $this->assertSame($response, $firstReturnedResponse);
            $this->assertSame($response, $secondReturnedResponse);
        }
    }

To fake an exception being thrown::

    use Http\Mock\Client;

    class YourTest extends \PHPUnit_Framework_TestCase
    {
        /**
         * @expectedException \Exception
         */
        public function testClientThrowsException()
        {
            $client = new Client();

            $exception = new \Exception('Whoops!');
            $client->addException($exception);

            // $request is an instance of Psr\Http\Message\RequestInterface
            $returnedResponse = $client->sendRequest($request);
        }
    }

Or set a default exception::

    use Http\Mock\Client;

    class YourTest extends \PHPUnit_Framework_TestCase
    {
        /**
         * @expectedException \Exception
         */
        public function testClientThrowsException()
        {
            $client = new Client();

            $exception = new \Exception('Whoops!');
            $client->setDefaultException($exception);

            $response = $this->getMock('Psr\Http\Message\ResponseInterface');
            $client->addResponse($response);

            // $firstRequest and $secondRequest are instances of Psr\Http\Message\RequestInterface
            // The first request will returns the added response.
            $firstReturnedResponse = $client->sendRequest($firstRequest);
            // There is no more added response, the default exception will be thrown.
            $secondReturnedResponse = $client->sendRequest($secondRequest);
        }
    }


.. hint::

    If you're using the :doc:`/integrations/symfony-bundle`, the mock client is available as a service with ``httplug.client.mock`` id.

.. include:: includes/further-reading-async.inc
