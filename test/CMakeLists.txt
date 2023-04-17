cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

find_package( Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories( ${TEST_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
)
add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable( main main.cpp )

target_link_libraries( main ${PROJECT_NAME}_Lib
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(NAME main_test COMMAND main)