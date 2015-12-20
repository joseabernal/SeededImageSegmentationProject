include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

include_directories(${external_includes})

add_subdirectory(unit)

add_executable(test_mathtools
    test_all.cpp
    ${src_mathtools_all})

target_link_libraries(test_mathtools 
    ${GTEST_BOTH_LIBRARIES}
    math_tools
    common
    ${external_libs})