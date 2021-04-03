cmake_minimum_required(VERSION 3.0.0)
link_libraries(ctils)

add_executable(EchoTest echo.test.c)
add_executable(ConcatTest concat.test.c)
add_executable(CmpTest cmp.test.c)

set(TEST EchoTest)
add_test(
    NAME ${TEST}
    COMMAND ${TEST} "stop copying me"
)
set_tests_properties(
    ${TEST}
    PROPERTIES PASS_REGULAR_EXPRESSION "stop copying me"
)

set(TEST ConcatTest)
add_test(
    NAME    ${TEST}
    COMMAND ${TEST} "con" "ca" "te" "na" "tion"
)
set_tests_properties(
    ${TEST}
    PROPERTIES PASS_REGULAR_EXPRESSION "concatenation"
)

add_test(
    NAME    CmpTestEq
    COMMAND CmpTest "same" "same"
)

add_test(
    NAME    CmpTestNeq
    COMMAND CmpTest "same" "different"
)
set_tests_properties(
    CmpTestNeq
    PROPERTIES WILL_FAIL TRUE
)