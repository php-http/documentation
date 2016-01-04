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

Collect requests
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

Fake responses and exceptions
-----------------------------

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

.. include:: includes/further-reading-async.inc
