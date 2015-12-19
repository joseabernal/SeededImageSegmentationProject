file(GLOB_RECURSE exceptions_sources *.cpp)
file(GLOB_RECURSE exceptions_headers *.h)

include_directories(${external_includes})

add_library(exceptions STATIC
        ${exceptions_sources}
        ${exceptions_headers}
)

target_link_libraries(exceptions ${external_libs})