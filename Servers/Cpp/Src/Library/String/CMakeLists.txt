set(TARGET_NAME "StringLib")

add_library(${TARGET_NAME} STATIC "String.cpp")
target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_INCLUDE_DIRS})

add_subdirectory(UnitTest)