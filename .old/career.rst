Career
=========

🎻 Soft Skills
--------------

🎺 Share summary with teammates right after a meeting or small discuss
......................................................................

This tip came from a dicuss/meeting about improve integration test automation for exodus-gw. we disscuss the difficult part, easy part, and what can be worked on simultaneously.

After the meeting, I think it would be better to send a summary message in Google chat room for teammates.

Summary should be simple, clear and well-format.

.. code-block:: none

    1. Trigger
    2. write autotests code
    3. access PostgreSQL container(in Pod) in OCP

🎺 Tips for Document
....................

- Attach links to JIRA issue, help teammates get more info easily.

🎺 Dev Env and Debug Strategy 
.............................

When learning language or framework, **Fast Feedback** is important.

A good development environment should consider **long-term maintenance** and **easy to use**.

A good example of complex dev env is `exodus-gw`_. 

- `localstack`_ container used for fake AWS S3 and DynamoDB
- Container platform-sidecar is used as the `reverse proxy`_ (This proxy performs authentication via mutual TLS, and authorization via a static configuration file)
- PostgreSQL container
- `dramatiq worker`_
- `sscg`_ for cert management

The dev env management includes systemd, `tox`_ for cmd mangement(eg. dramatiq), podman for containers

.. _exodus-gw: https://release-engineering.github.io/exodus-gw/#
.. _localstack: https://github.com/localstack/localstack
.. _dramatiq worker: https://github.com/release-engineering/exodus-gw/blob/master/scripts/systemd/exodus-gw-worker.service
.. _tox: https://github.com/release-engineering/exodus-gw/blob/master/tox.ini
.. _sscg: https://github.com/sgallagher/sscg
.. _reverse proxy: https://youtu.be/SqqrOspasag
