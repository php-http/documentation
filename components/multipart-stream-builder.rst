Multipart Stream Builder
========================

A multipart stream is a special kind of stream that is used to transfer files over HTTP. There is currently no PSR-7 support for multipart streams as they are considered to be normal streams with a special content. A multipart stream HTTP request may look like this:

.. code-block:: none

    POST / HTTP/1.1
    Host: example.com
    Content-Type: multipart/form-data; boundary="578de3b0e3c46.2334ba3"

    --578de3b0e3c46.2334ba3
    Content-Disposition: form-data; name="foo"
    Content-Length: 15

    A normal stream
    --578de3b0e3c46
    Content-Disposition: form-data; name="bar"; filename="bar.png"
    Content-Length: 71
    Content-Type: image/png

    ?PNG
    
    ???
    IHDR??? ??? ?????? ???? IDATxc???51?)?:??????IEND?B`?
    --578de3b0e3c46.2334ba3
    Content-Type: text/plain
    Content-Disposition: form-data; name="baz"
    Content-Length: 6

    string
    --578de3b0e3c46.2334ba3--


In the request above you see a set of HTTP headers and a body with two streams. The body starts and ends with a "boundary" and it is also this boundary that separates the streams. That boundary also needs to be specified in the ``Content-Type`` header.

Building a Multipart Stream
```````````````````````````

To build a multipart stream you may use the ``MultipartStreamBuilder``. It is not coupled to any stream implementation so it needs a ``StreamFactory`` to create the streams.

.. code-block:: php

    $streamFactory = StreamFactoryDiscovery::find();
    $builder = new MultipartStreamBuilder($streamFactory);
    $builder
      ->addResource('foo', $stream)
      ->addResource('bar', fopen($filePath, 'r'), ['filename' => 'bar.png'])
      ->addResource('baz', 'string', ['headers' => ['Content-Type' => 'text/plain']]);

    $multipartStream = $builder->build();
    $boundary = $builder->getBoundary();

    $request = MessageFactoryDiscovery::find()->createRequest(
      'POST',
      'http://example.com',
      ['Content-Type' => 'multipart/form-data; boundary="'.$boundary.'"'],
      $multipartStream
    );

    $response = HttpClientDiscovery::find()->sendRequest($request);

The second parameter of ``MultipartStreamBuilder::addResource()`` is the content of the stream. The supported input is the same as ``StreamFactory::createStream()``.
