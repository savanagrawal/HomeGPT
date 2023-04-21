# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
# find_library(${PROJECT_NAME}_MoodDetectionLib ${PROJECT_NAME}_MoodDetectionLib REQUIRED)

# Set include directories
set(INCLUDE_DIRS

)

# Set source files
set( SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.cpp

)

# Set header files
set( HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.h

)

# Create peripherals library
add_library( ${PROJECT_NAME}_UtilsLib SHARED ${SOURCES} )

set_target_properties( ${PROJECT_NAME}_UtilsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.h )