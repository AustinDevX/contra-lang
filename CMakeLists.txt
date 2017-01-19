cmake_minimum_required(VERSION 2.6)
project(contra_lang)

set(SOURCE_FILES
        src/frontend/source.h
        src/frontend/source.cc
        src/frontend/file_source.h
        src/frontend/file_source.cc
        src/frontend/string_source.h
        src/frontend/string_source.cc
        src/frontend/token.h
        src/frontend/token.cc
        src/frontend/word_token.h
        src/frontend/word_token.cc
        src/frontend/scanner.h
        src/frontend/scanner.cc

        test/frontend/source_test.cpp
        test/frontend/frontend_all_test.cpp
        test/frontend/scanner_test.cpp
        test/frontend/word_token_test.cc.cpp
        test/frontend/file_source_test.cc)

# requires google test 1.8.0+ which packages the gmock and gtest libraries together
include_directories(
#         $ENV{GTEST_HOME}/googlemock/include
#         $ENV{GTEST_HOME}/googletest/include
        /usr/local/lib/googletest-1.8/googlemock/include
        /usr/local/lib/googletest-1.8/googletest/include
)
link_directories(
        /usr/local/lib/googletest-1.8/build/googlemock
        /usr/local/lib/googletest-1.8/build/googlemock/gtest
#        $ENV{GTEST_HOME}/build/googlemock
#        $ENV{GTEST_HOME}/build/googlemock/gtest
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
add_executable(contra_lang ${SOURCE_FILES})
target_link_libraries(contra_lang gmock)
target_link_libraries(contra_lang gtest)
