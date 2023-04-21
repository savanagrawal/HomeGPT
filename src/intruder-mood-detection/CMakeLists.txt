# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
find_package( OpenCV REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../utils )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../peripherals )

# Set Include Directories
set( INCLUDE_DIRS
    ${OpenCV_INCLUDE_DIRS}
)


# Set Soruces
set( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IntruderMoodDetection.cpp
    
)

# Set Headers
set( HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/IntruderMoodDetection.h

)

# Create intruder mood detection library
add_library( ${PROJECT_NAME}_IntruderMoodDetectionLib SHARED ${SOURCES} )

# Link directories or libraries
target_include_directories( ${PROJECT_NAME}_IntruderMoodDetectionLib PUBLIC ${INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME}_IntruderMoodDetectionLib 
    cpptimer
    ${OpenCV_LIBS}
    ${PROJECT_NAME}_UtilsLib
)

set_target_properties( ${PROJECT_NAME}_IntruderMoodDetectionLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/IntruderMoodDetection.h )
