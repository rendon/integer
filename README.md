Integer
=======
My naive Big Integer class. I implemented this class some time ago in order to solve problems in programming contests since C/C++ doesn't have native support for these operations.

For practical pursposes its better to use a more reliable and faster libraries, such as GNU MP or Java BigInteger class, but if you want to understand how the things work(essencial in programming contests) this class can be useful to you.

My implementation is slow but I've tried to make the code as understandable as possible, in contrast with the other faster libraries.

Operations supported
====================
    - addition: `+` operator
    - subtraction: `-` operator
    - multiplication: `*` operator
    - division: `/` operator
    - modulo: `%` operator
    - exponentiation
    - modular exponentiation
    - gcd()
    - lcm()
    - bit shifting: operators <<, >>
    - Some others.

Tests
=====
In `test.cpp` there are some tests for each operatio that I've prepared using UnitTest++. Also, there is a test generator written in Ruby and a small bash script to automate the tests.


NOTES
=====
    - The number base used is 10
    - I've realized that base 10 wasn't the more appropiate since many operations are easier and faster using base 2: http://stackoverflow.com/questions/7212554/what-base-would-be-more-appropriate-for-my-biginteger-library
    - You can find a clean implementation (I think) of Karatsuba algorithm for multiplications
    - The `is_probable_prime()` method is still in experimentation.
