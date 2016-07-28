Exceptions
==========

HTTPlug defines a common interface for all exceptions thrown by HTTPlug implementations.
Every exception thrown by a HTTP client must implement ``Http\Client\Exception``.

``HttpClient::sendRequest()`` can throw one of the following exceptions.

================================== ============================= ===================
Exception                          Thrown when                   Methods available
================================== ============================= ===================
TransferException                  something unexpected happened \-
└ RequestException                 the request is invalid        ``getRequest()``
 |nbsp| |nbsp| └ NetworkException  no response received
                                   due to network issues         ``getRequest()``
 |nbsp| |nbsp| └ HttpException     error response                ``getRequest()``
                                                                 ``getResponse()``
================================== ============================= ===================

.. note::
    By default clients will always return a PSR-7 response instead of throwing a HttpException. Configure your client
    or use the :doc:`/plugins/error` to make sure the HttpException is thrown.

.. note::

    The ``sendAsyncRequest`` should never throw an exception but always return a
    :doc:`../components/promise`. The exception classes used in ``Promise::wait`` and the ``then``
    callback are however the same as explained here.

.. |nbsp| unicode:: U+00A0 .. non-breaking space
