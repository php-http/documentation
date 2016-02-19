.. _message-factory:

Message Factory
===============

**Factory interfaces for PSR-7 HTTP Message.**

Rationale
---------

While it should be possible to use every PSR-7 aware HTTP client with any RequestInterface implementation,
creating the request objects will still tie the code to a specific implementation.
If each reusable library is tied to a specific message implementation,
an application could end up installing several message implementations.
The factories abstract away from this.

The FIG was pretty straightforward by NOT putting any construction logic into PSR-7.
The ``MessageFactory`` aims to provide an easy way to construct messages.

Usage
-----

.. _stream-factory:

This package provides interfaces for PSR-7 factories including:

- ``MessageFactory``
- ``ServerRequestFactory`` - WIP (PRs welcome)
- ``StreamFactory``
- ``UploadedFileFactory`` - WIP (PRs welcome)
- ``UriFactory``
