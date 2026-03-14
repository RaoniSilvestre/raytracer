file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(app_tests ${TEST_SOURCES})

target_link_libraries(app_tests PRIVATE core_lib GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(app_tests)
