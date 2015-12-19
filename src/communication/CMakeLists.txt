file(GLOB_RECURSE communication_sources *.cpp)
file(GLOB_RECURSE communication_headers *.h)

include_directories(${external_includes})
include_directories(${PROJECT_SOURCE_DIR}/common/)
include_directories(${PROJECT_SOURCE_DIR}/exceptions/)
include_directories(${PROJECT_SOURCE_DIR}/math_tools/)

add_library(communication STATIC
        ${communication_sources}
        ${communication_headers}
)

target_link_libraries(communication common exceptions math_tools ${external_libs})