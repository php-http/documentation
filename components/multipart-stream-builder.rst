Multipart Stream Builder
========================

A multipart stream is a special kind of stream that is used to transfer files over HTTP. There is currently no PSR-7 support for multipart streams as they are considered to be normal streams with a special content. A multipart stream HTTP request may look like this:

.. code-block:: none

    POST / HTTP1/1
    User-Agent: curl/7.21.2 (x86_64-apple-darwin)
    Host: localhost:8080
    Accept: */*
    Content-Length: 1143
    Expect: 100-continue
    Content-Type: multipart/form-data; boundary=----------------------------83ff53821b7c

    ------------------------------83ff53821b7c
    Content-Disposition: form-data; name="img"; filename="a.png"
    Content-Type: application/octet-stream

    ?PNG

    IHD?wS??iCCPICC Profilex?T?kA?6n??Zk?x?"IY?hE?6?bk
    Y?<ߡ)??????9Nyx?+=?Y"|@5-?M?S?%?@?H8??qR>?׋??inf???O?????b??N?????~N??>?!?
    ??V?J?p?8?da?sZHO?Ln?}&???wVQ?y?g????E??0
     ??
       IDAc????????-IEND?B`?
    ------------------------------83ff53821b7c
    Content-Disposition: form-data; name="foo"

    bar
    ------------------------------83ff53821b7c--


In the request above you see a set of HTTP headers and a body with two streams. The body starts and ends with a "boundary" and it is also this boundary that separates the streams. That boundary also needs to be specified in the ``Content-Type`` header.

Building a multipart stream
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
      ['Content-Type' => 'multipart/form-data; boundary='.$boundary],
      $multipartStream
    );

    $response = HttpClientDiscovery::find()->sendRequest($request);

The second parameter of ``MultipartStreamBuilder::addResource()`` is the content of the stream. The supported input is the same as ``StreamFactory::createStream()``.
