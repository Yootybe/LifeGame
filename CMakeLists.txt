cmake_minimum_required(VERSION 3.16.0)

project(Life VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES FieldProcessor.h FieldProcessor.cpp)

add_subdirectory(QAs)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(LifeLib ${SOURCES})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} LifeLib)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})