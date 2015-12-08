include_directories(${external_includes})

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