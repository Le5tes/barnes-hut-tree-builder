npm run test-core
TEST_CORE_STATUS=$?

npm run build-core
BUILD_CORE_STATUS=$?

npm run test-wrapper
TEST_WRAPPER_STATUS=$?

if [ $(($TEST_CORE_STATUS+$BUILD_CORE_STATUS+$TEST_WRAPPER_STATUS)) == '0' ]
then
    echo ""
    echo "ALL TESTS PASSED! :D"
    echo ""
fi

exit $(($TEST_CORE_STATUS+$BUILD_CORE_STATUS+$TEST_WRAPPER_STATUS))