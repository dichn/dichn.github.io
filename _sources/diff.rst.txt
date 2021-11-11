Difficulty
==========

2021.11
-------

1. GElf_Dyn -> symbols information
2. tclsh with regexp
3. curl: (58) could not load PEM client certificate, OpenSSL error error:140AB18E:SSL routines:SSL_CTX_use_certificate:ca md too weak, (no key found, wrong pass phrase, or wrong file format?)
    **solution**: ``sudo update-crypto-policies --set DEFAULT:FEDORA32``
4. curl -> cloudfront, 503 error with "x-cache: LambdaExecutionError from cloudfront"
