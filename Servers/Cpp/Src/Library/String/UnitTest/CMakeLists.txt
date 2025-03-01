set(TARGET_NAME "StringLibTest")

add_executable(${TARGET_NAME} StringTest.cpp)
target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} StringLib)