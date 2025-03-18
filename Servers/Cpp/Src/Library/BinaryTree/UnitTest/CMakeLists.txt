set(TARGET_NAME "BinaryTreeLibTest")

add_executable(${TARGET_NAME} BinaryTreeTest.cpp)
target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} gtest gtest_main)