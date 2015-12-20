find_package( PkgConfig REQUIRED )
pkg_search_module( EIGEN3 REQUIRED eigen3 )
pkg_search_module( OpenCV REQUIRED opencv )

find_package( GTest REQUIRED )
find_package( Qt4 REQUIRED )

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories( ${QT_INCLUDE_DIR} )
include_directories( ${EIGEN3_INCLUDE_DIRS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(external_libs ${QT_LIBRARIES} ${OpenCV_LIBRARIES} ${EIGEN3_LIBRARIES} ${GTest_LIBRARIES} "-lpthread")