Artax Adapter
=============

An HTTPlug adapter for the `Artax HTTP client`_.

Installation
------------

To install the Artax adapter, which will also install Artax itself (if it was
not yet included in your project), run:

.. code-block:: bash

    $ composer require php-http/artax-adapter

Usage
-----

Begin by creating a Artax adapter::

    use Amp\Artax\DefaultClient;
    use Http\Adapter\Artax\Client as ArtaxAdapter;
    use Http\Message\MessageFactory\GuzzleMessageFactory;

    $adapter = new ArtaxAdapter(new DefaultClient(), new GuzzleMessageFactory());

Or relying on :doc:`discovery </discovery>`::

    use Http\Adapter\Artax\Client as ArtaxAdapter;

    $adapter = new ArtaxAdapter();

.. include:: includes/further-reading-async.inc

.. _Artax HTTP client: https://github.com/amphp/artax
