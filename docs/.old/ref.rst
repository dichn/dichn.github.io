Reference
=========

🎻 Testing Guide
----------------

- `Test Desiderata`_
- `Google Testing Blog`_
- `All Your Tests Are Terrible - Titus Winters and Hyrum Wright - CppCon 2015`_
- `A Reflection on Software Testing - Richard Jones - PyConline AU 2020`_
- `Acceptance Testing for Continuous Delivery - Dave Farley - GOTO 2016`_
- `The difference between unit functional acceptance and integration testing`_


🎺 Things that hinder understanding
...................................

- Mutable or otherwise complicated mocks
- Conditional branches
- Tests are not focused

🎺 Tips
.......

- Fast is better than slow
- Test **behavior** not **implementation**
- Tests must be isolated from each other
- Be focused(i.e. tests should not execute too much code)
- No conditional branches in tests

.. _Google Testing Blog: https://testing.googleblog.com
.. _Test Desiderata: https://medium.com/@kentbeck_7670/test-desiderata-94150638a4b3
.. _All Your Tests Are Terrible - Titus Winters and Hyrum Wright - CppCon 2015: https://youtu.be/u5senBJUkPc
.. _A Reflection on Software Testing - Richard Jones - PyConline AU 2020: https://youtu.be/rY45dmzrCu4
.. _The difference between unit functional acceptance and integration testing: https://stackoverflow.com/questions/4904096/whats-the-difference-between-unit-functional-acceptance-and-integration-test
.. _Acceptance Testing for Continuous Delivery - Dave Farley - GOTO 2016: https://youtu.be/SBhgteA2szg
