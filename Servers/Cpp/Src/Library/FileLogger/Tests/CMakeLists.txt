set(TARGET_NAME "FileLoggerLibTests")

add_executable(${TARGET_NAME} FileLoggerTests.cpp)
target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} gtest gtest_main FileLoggerLib)
target_compile_options(${TARGET_NAME} PRIVATE 
   "-Wall"
   "-Wextra"
   "-Wpedantic"
   "-Werror"
   "-Wconversion"
   "-Wshadow"
   "-Wundef")