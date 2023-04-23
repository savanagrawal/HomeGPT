# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )
set(CMAKE_CXX_STANDARD 17)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/DatasetCreator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DatasetTrainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IntruderDetection.cpp
    
)

# Set Headers
set( HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/DatasetCreator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/DatasetTrainer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IntruderDetection.h

)

# Create intruder detection library
add_library( ${PROJECT_NAME}_IntruderDetectionLib SHARED ${SOURCES} )

# Link directories or libraries
target_include_directories( ${PROJECT_NAME}_IntruderDetectionLib PUBLIC ${INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME}_IntruderDetectionLib 
    cpptimer
    ${OpenCV_LIBS}
    ${PROJECT_NAME}_UtilsLib
)

set_target_properties( ${PROJECT_NAME}_IntruderDetectionLib PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/DatasetCreator.h )

set_target_properties( ${PROJECT_NAME}_IntruderDetectionLib PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/DatasetTrainer.h )

set_target_properties( ${PROJECT_NAME}_IntruderDetectionLib PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/IntruderDetection.h )