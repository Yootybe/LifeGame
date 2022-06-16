cmake_minimum_required(VERSION 3.16.0)

project(Tests VERSION 1.0.0 LANGUAGES CXX)

enable_testing()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} Tests.cpp)

include(GoogleTest)
add_test(GoogleTest ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CONAN_LIBS} LifeLib)