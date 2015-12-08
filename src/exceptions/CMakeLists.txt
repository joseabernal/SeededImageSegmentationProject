include_directories(${external_includes})

set(exceptions_sources exception.cpp mathexception.cpp userinputexception.cpp)
set(exceptions_headers exception.h mathexception.h userinputexception.h)

add_library(exceptions SHARED
        ${exceptions_sources}
        ${exceptions_headers}
)

target_link_libraries(exceptions ${external_libs})