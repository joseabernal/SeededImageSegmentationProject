include_directories(${external_includes})

set(math_tools_sources seededsegmentation.cpp)
set(math_tools_headers seededsegmentation.h)

add_library(math_tools SHARED
        ${math_tools_sources}
        ${math_tools_headers}
)

target_link_libraries(math_tools ${external_libs})