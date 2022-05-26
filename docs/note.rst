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

.. code-block:: none
 
    # server
    $ sscg --subject-alt-name localhost .
    $ ssl-proxy -cert sscg/service.pem -key sscg/service-key.pem -from 0.0.0.0:7853 -to 127.0.0.1:3000
    2021/03/14 16:27:54 Assuming -to URL is using http://
    2021/03/14 16:27:54 Proxying calls from https://0.0.0.0:7853 (SSL/TLS) to http://127.0.0.1:3000
    
    # client
    $ curl https://localhost:7853/print -d "foo" --key service-key.pem --cert service.pem --cacert ca.crt
    foo

The example use `ssl-proxy`_, `sscg`_, `http server`_.

.. code-block:: none
 
    [dichen@arpeggio ssl-proxy]$ ./ssl-proxy -cert pulp-05.crt -key pulp-05.key -from 0.0.0.0:7853 -to 127.0.0.1:3000
    2021/03/19 23:30:42 Assuming -to URL is using http://
    2021/03/19 23:30:42 Proxying calls from https://0.0.0.0:7853 (SSL/TLS) to http://127.0.0.1:3000
    2021/03/19 23:30:49 http: TLS handshake error from [::1]:47732: local error: tls: bad record MAC
    2021/03/19 23:31:52 http: TLS handshake error from [::1]:47970: local error: tls: bad record MAC
    2021/03/19 23:36:02 http: TLS handshake error from [::1]:49050: local error: tls: bad record MAC

    # The reason is subjectAltName under [ v3_ca ] is required
    [dichen@arpeggio pulp_certs]$ vim openssl.cnf
    ...
    [ v3_ca ]
    # Include email address in subject alt name: another PKIX recommendation
    subjectAltName=email:move
    
By setting verify-full and an sslrootcert, you (as the client) are authenticating the identity of the server.  You need to provide a key only if you want the server also to authenticate you as the client using TLS (and not for example by a username & password).


.. _requests library: https://requests.readthedocs.io/en/master/user/advanced/#ssl-cert-verification
.. _ssl-proxy: https://github.com/suyashkumar/ssl-proxy
.. _sscg: https://github.com/sgallagher/sscg
.. _http server: https://github.com/dichen16/mewtwo/blob/master/rs/server/src/main.rs
