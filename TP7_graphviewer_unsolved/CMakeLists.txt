cmake_minimum_required(VERSION 3.17)
project(CAL-TP_classes)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

file(GLOB TP7_GRAPHVIEWER_FILES CONFIGURE_DEPENDS
        "TP7_graphviewer/*.cpp"
        )

add_executable(TP7_graphviewer
        ${TP7_GRAPHVIEWER_FILES}
        )

target_link_libraries(TP7_graphviewer graphviewer)
