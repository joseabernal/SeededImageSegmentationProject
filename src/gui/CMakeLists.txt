file(GLOB_RECURSE gui_sources *.cpp *.cc)
file(GLOB_RECURSE gui_headers *.h *.hpp)

include_directories(${external_includes})
include_directories(${PROJECT_SOURCE_DIR}/communication/)

add_library(gui STATIC
        ${gui_sources}
        ${gui_headers}
)

target_link_libraries(gui communication ${external_libs})