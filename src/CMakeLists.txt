include_directories(${PROJECT_SOURCE_DIR}/)

include_directories(${external_includes})

add_subdirectory(exceptions)
add_subdirectory(common)
add_subdirectory(mathtools)
add_subdirectory(communication)
add_subdirectory(gui)
add_subdirectory(apps)