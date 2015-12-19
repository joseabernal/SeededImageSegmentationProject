include_directories(${PROJECT_SOURCE_DIR}/)

include_directories(${external_includes})
include_directories(${PROJECT_SOURCE_DIR}/exceptions/)
include_directories(${PROJECT_SOURCE_DIR}/common/)
include_directories(${PROJECT_SOURCE_DIR}/math_tools/)
include_directories(${PROJECT_SOURCE_DIR}/communication/)
include_directories(${PROJECT_SOURCE_DIR}/gui/)

set(app_programs main)

foreach(app ${app_programs})
    add_executable(${app} ${app}.cpp)
    target_link_libraries(${app}
                          exceptions
                          common
                          math_tools
                          communication
                          gui
                          ${external_libs})
endforeach()