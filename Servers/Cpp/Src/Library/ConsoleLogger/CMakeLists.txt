set(TARGET_NAME "ConsoleLoggerLib")

add_library(${TARGET_NAME} ConsoleLogger.cpp)
target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_INCLUDE_DIRS})

target_compile_options(${TARGET_NAME} PRIVATE
   "-Wall"
   "-Wextra"
   "-Wpedantic"
   "-Werror"
   "-Wconversion"
   "-Wshadow"
   "-Wundef")

include("${PROJECT_SOURCE_DIR}/ThirdParty/PvsCMakeModule/PVS-Studio.cmake")
pvs_studio_add_target(TARGET ${TARGET_NAME}.analyze ALL
                      OUTPUT FORMAT json
                      ANALYZE ${TARGET_NAME}
                      MODE GA:1,2,3 OP CS
                      LOG PvsReport.json
                      ARGS -e /path/to/exclude-path)