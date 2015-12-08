include_directories(${external_includes})

file(GLOB_RECURSE common_sources *.cpp)
file(GLOB_RECURSE common_headers *.h)

add_library(common SHARED
        ${common_sources}
        ${common_headers}
)

target_link_libraries(common exceptions ${external_libs})