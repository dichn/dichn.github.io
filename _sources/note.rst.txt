Note
====

🎻 Network
----------

🎺 mutual TLS
.............

mutual TLS means: you (client) verifies the server, and server verifies you

``--cert`` and ``--key`` cause you to pass a certificate to the server, so the server can verify you. That's one side.

The server **always** provides you a cert, and ``--cacert`` controls where you look in order to verify that cert, that's the other side.

Client verifying the server is enabled by default, ``--cacert`` doesn't enable or disable it, it just changes the default path where it will look for certs to verify the server.

Check the default ``--cacert`` by 

.. code-block:: none
    
    strace curl https://example.com --key my.key --cert my.cert|& grep open

In `requests library`_ , this list of trusted CAs can also be specified through the ``REQUESTS_CA_BUNDLE`` environment variable. If ``REQUESTS_CA_BUNDLE`` is not set, ``CURL_CA_BUNDLE`` will be used as fallback.

.. _requests library: https://requests.readthedocs.io/en/master/user/advanced/#ssl-cert-verification