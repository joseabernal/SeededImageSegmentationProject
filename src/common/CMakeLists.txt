file(GLOB_RECURSE common_sources *.cpp)
file(GLOB_RECURSE common_headers *.h)

include_directories(${PROJECT_SOURCE_DIR}/exceptions/)
include_directories(${external_includes})

add_library(common STATIC
        ${common_sources}
        ${common_headers}
)

target_link_libraries(common exceptions ${external_libs})