Backwards compatibility
=======================

Backwards compatibility is an important topic for us, as it should be in every open source project. We follow
[Semver](http://semver.org/) which allows us to only break backwards compatibility between major versions. We use
deprecation notices to inform you about the changes made before they are removed.

Our backwards compatibility promise does not include classes or functions with the ``@internal`` annotation.

Symfony Bundle
--------------

The HttplugBundle is just a Symfony integration for HTTPlug and it does not have any classes which falls under the BC
promise. The backwards compatibility of the bundle is only the configuration and its values (and of course the behavior
of those values).

Discovery
---------

The order of which the strategies are included is not part of our BC promise. The strategies them self is marked
with ``@internal`` so they are also not part of our BC promise.
However, we do promise that we will not remove a strategy neither will we remove classes from the `
``CommonClassesStrategy``. We will also support the following Puli versions:
* 1.0.0-beta10

The consequences of the BC promise on the discovery library is that you can never be sure *what* client that is
being returned but you can be sure that if discovery finds you a client we will not make an update that will break
discovery for you.
