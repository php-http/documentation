Buzz Adapter
============

An HTTPlug adapter for the `Buzz HTTP client`_.

Installation
------------

To install the Buzz adapter, which will also install Buzz itself (if it was
not yet included in your project), run:

.. code-block:: bash

    $ composer require php-http/buzz-adapter

.. include:: includes/install-message-factory.inc

.. include:: includes/install-discovery.inc

Usage
-----

Begin by creating a Buzz client, you may pass any listener or configuration parameters to it
like::

    use Buzz\Browser;
    use Buzz\Client\Curl;
    use Buzz\Listener\CookieListener;

    $browser = new Browser();

    $client = new Curl();
    $client->setMaxRedirects(0);
    $browser->setClient($client);

    // Create CookieListener
    $listener = new CookieListener();
    $browser->addListener($listener);

Then create the adapter::

    use Http\Adapter\Buzz\Client as BuzzAdapter;
    use Http\Message\MessageFactory\GuzzleMessageFactory;

    $adapter = new BuzzAdapter($browser, new GuzzleMessageFactory());

Or if you installed the :doc:`discovery </discovery>` layer::

    use Http\Adapter\Buzz\Client as BuzzAdapter;

    $adapter = new BuzzAdapter($browser);

.. warning::

    The message factory parameter is mandatory if the discovery layer is not installed.

Be Aware
--------

This adapter violates the Liskov substitution principle in a rare edge case. When the adapter is configured to use
Buzz' Curl client, it does not send request bodies for request methods such as GET, HEAD and TRACE. A ``RequestException``
will be thrown if this ever happens.

If you need GET request with a body (e.g. for Elasticsearch) you need to use the Buzz FileGetContents client or choose a different HTTPlug client like Guzzle 6.

.. include:: includes/further-reading-sync.inc

.. _Buzz HTTP client: https://github.com/kriswallsmith/Buzz
