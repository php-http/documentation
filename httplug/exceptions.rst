Exceptions
==========

HTTPlug defines one Exception interface: ``Http\Client\Exception``. All HTTP
client exceptions must implement this interface.

``HttpClient::sendRequest()`` can throw one of the following exceptions.

================================== ====================== ===================
Exception                          Thrown when            Methods available
================================== ====================== ===================
TransferException                  ???
└ RequestException                 the request is invalid ``getRequest()``
 |nbsp| |nbsp| └ NetworkException  no response received
                                   due to network issues  ``getRequest()``
 |nbsp| |nbsp| └ HttpException     error response         ``getRequest()``
                                                          ``getResponse()``
================================== ====================== ===================

.. |nbsp| unicode:: U+00A0 .. non-breaking space
