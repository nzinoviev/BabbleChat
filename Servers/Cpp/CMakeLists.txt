cmake_minimum_required(VERSION 3.28)

project(BabbleChat LANGUAGES CXX)

# По умолчанию тип сборки Debug.
if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Debug")
endif()

# Вывод основных параметров сборки.
message(STATUS "*==================================*")
message(STATUS "| Build type       : ${CMAKE_BUILD_TYPE}")
message(STATUS "| Generator        : ${CMAKE_GENERATOR}")
message(STATUS "| Compiler for C++ : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "| Operating system : ${CMAKE_SYSTEM_NAME}")
message(STATUS "| Architecture     : ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "*==================================*")

add_subdirectory(Src)