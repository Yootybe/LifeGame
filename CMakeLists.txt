cmake_minimum_required(VERSION 3.0)

project(Life VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
endif()

add_executable(${PROJECT_NAME} main.cpp FieldProcessor.h FieldProcessor.cpp)

if (TARGET CONAN_PKG::libx264)
    target_link_libraries(${PROJECT_NAME} CONAN_PKG::libx264 ${WIN_LIBS})
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE libx264 ${CONAN_TARGETS})
endif()
