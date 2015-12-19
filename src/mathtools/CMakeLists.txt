file(GLOB_RECURSE math_tools_sources *.cpp *.cc)
file(GLOB_RECURSE math_tools_headers *.h *.hpp)

include_directories(${PROJECT_SOURCE_DIR}/exceptions/)
include_directories(${external_includes})

add_library(math_tools STATIC
        ${math_tools_sources}
        ${math_tools_headers}
)

target_link_libraries(math_tools exceptions ${external_libs})