# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
find_package( OpenCV REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../peripherals )

# Set include directories
set( INCLUDE_DIRS
    ${OpenCV_INCLUDE_DIRS}
)

# Set source files
set( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MoodDetection.cpp
)

# Set header files
set( HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/MoodDetection.h

)

# Create mood detection library
add_library( ${PROJECT_NAME}_MoodDetectionLib SHARED ${SOURCES} )

# Link directories or libraries
target_include_directories( ${PROJECT_NAME}_MoodDetectionLib PUBLIC ${INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME}_MoodDetectionLib 
    cpptimer
    ${OpenCV_LIBS}
)

set_target_properties( ${PROJECT_NAME}_MoodDetectionLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/MoodDetection.h )