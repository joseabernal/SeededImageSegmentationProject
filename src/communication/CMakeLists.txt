include_directories(${external_includes})

set(communication_sources segmentationeventhandler.cpp segmentationeventhandler.cpp segmentationthread.cpp)
set(communication_headers segmentationeventhandler.h segmentationeventhandler.h segmentationthread.h)

add_library(communication SHARED
        ${communication_sources}
        ${communication_headers}
)

target_link_libraries(communication common exceptions math_tools ${external_libs})