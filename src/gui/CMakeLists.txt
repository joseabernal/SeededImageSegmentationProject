include_directories(${PROJECT_SOURCE_DIR}/)

include_directories(${external_includes})

set(gui_sources displaywindow.cpp mainwindow.cpp seedinputwindow.cpp application.cpp)
set(gui_headers displaywindow.h mainwindow.h seedinputwindow.h application.h)

add_library(gui STATIC
        ${gui_sources}
        ${gui_headers}
)

target_link_libraries(gui communication ${external_libs})