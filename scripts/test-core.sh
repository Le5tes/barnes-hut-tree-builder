g++ -std=c++11 lib/c++/tests/test-main.cpp
./a.out
TESTS_PASS=$?
rm a.out
exit $TESTS_PASS