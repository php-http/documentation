Backwards compatibility
=======================

Backwards compatibility is an important topic for us, as it should be in every open source project. We follow
Semver_ which allows us to only break backwards compatibility between major versions. We use
deprecation notices to inform you about the changes made before they are removed.

Our backwards compatibility promise does not include classes or functions with the ``@internal`` annotation.

Symfony Bundle
--------------

The HttplugBundle is just a Symfony integration for HTTPlug and it does not have any classes which falls under the BC
promise. The backwards compatibility of the bundle is only the configuration and its values (and of course the behavior
of those values).

Discovery
---------

The order of the strategies is not part of our BC promise. The strategies themselves are marked
as ``@internal`` so they are also not part of our BC promise.
However, we do promise that we will not remove a strategy neither will we remove classes from the
``CommonClassesStrategy``.

The consequences of the BC promise for the discovery library is that you can not rely on the *same* client to be
returned in the future. However, if discovery does find a client now, you can be sure that after future updates it will still discover a client.

.. _Semver: http://semver.org/
