Systemtap
=========

🎻 Week 1 (  ~ 5.27)
--------------------

- `systemtap_beginners_guide`_
- `Sourceware Bugzilla`_
- `SystemTap Tapset Reference Manual`_
- `ptrace internals`_
- `The Linux Kernel Module Programming Guide`_

.. code-block:: none

    The essential idea behind a SystemTap script is to name events, and to give 
    them handlers. 
    
    When SystemTap runs the script, SystemTap monitors for the event; once the 
    event occurs, the Linux kernel then runs the handler as a quick sub-routine 
    and then resumes its normal operation.




.. _systemtap_beginners_guide: https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html-single/systemtap_beginners_guide/index
.. _Sourceware Bugzilla: https://sourceware.org/bugzilla/token.cgi
.. _SystemTap Tapset Reference Manual: https://sourceware.org/systemtap/tapsets/
.. _ptrace internals: https://stackoverflow.com/questions/23928530/how-does-ptrace-work-in-linux
.. _The Linux Kernel Module Programming Guide: https://tldp.org/LDP/lkmpg/2.6/html/