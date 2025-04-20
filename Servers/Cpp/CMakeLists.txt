cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BabbleChat LANGUAGES CXX)

add_subdirectory(ThirdParty/GoogleTest)

# По умолчанию тип сборки Debug.
if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Debug")
endif()

# Установка директорий для артефактов сборки.
set(BABBLE_CHAT_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/Output")
set(BABBLE_CHAT_OUTPUT_DEBUG_DIR "${BABBLE_CHAT_OUTPUT_DIR}/Debug")
set(BABBLE_CHAT_OUTPUT_RELEASE_DIR "${BABBLE_CHAT_OUTPUT_DIR}/Release")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BABBLE_CHAT_OUTPUT_DEBUG_DIR}/Library/Static")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BABBLE_CHAT_OUTPUT_RELEASE_DIR}/Library/Static")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BABBLE_CHAT_OUTPUT_DEBUG_DIR}/Library/Shared")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BABBLE_CHAT_OUTPUT_RELEASE_DIR}/Library/Shared")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BABBLE_CHAT_OUTPUT_DEBUG_DIR}/Binary")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BABBLE_CHAT_OUTPUT_RELEASE_DIR}/Binary")

# Вывод основных параметров сборки.
message(STATUS "*==================================*")
message(STATUS "| Build type       : ${CMAKE_BUILD_TYPE}")
message(STATUS "| Generator        : ${CMAKE_GENERATOR}")
message(STATUS "| Compiler for C++ : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "| Operating system : ${CMAKE_SYSTEM_NAME}")
message(STATUS "| Architecture     : ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "*==================================*")

add_subdirectory(Src)