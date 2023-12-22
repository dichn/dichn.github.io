Difficulty
==========

**never put a link here**

2021.11
-------

**Week 1**

1. [readelf] GElf_Dyn -> symbols information
2. tclsh with regexp
3. curl: (58) could not load PEM client certificate, OpenSSL error error:140AB18E:SSL routines:SSL_CTX_use_certificate:ca md too weak, (no key found, wrong pass phrase, or wrong file format?)
    | **solution**: ``sudo update-crypto-policies --set DEFAULT:FEDORA32`` 
    | **others**: python-requests is still using openssl library under the hood
4. curl -> cloudfront, 503 error with "x-cache: LambdaExecutionError from cloudfront"
    | **culprit**: missing exodus-config in ``*-config-dev`` table 
    | **experience**: debugging with check cloudwatch -> log -> log groups
5. CREATE_FAILED: CodePipelineCloudTrail: Resource handler returned message: "Invalid request provided: User: {id} already has 5 trails in us-east-1.
    | **culprit**: there is a CloudTrail limit (5 cloudtrail per account limit)
6. Do we want "frame_unwind.c::(handle_cfi -> expr_eval)" to be externally accessible?
    | **Q1**: I am little bit nervous in case making some mistakes when interacting with contributors. Not sure whether asking help to contributors is a good idea.

**Week 2**

1. Preprocessor-Options: ``gcc test.c -E -fdirectives-only | vim -``
2. Use dwfl_module_register_names to get the register names
3. [X] Call Frame Information (CFI) Handling
4. stack/register unwind
    | **kb**:  get the register values for a given stack frame
5. find a dynamic symbol table via phdrs
    | **ref**: libdwfl/dwfl_module_getdwarf.c:find_dynsym()

