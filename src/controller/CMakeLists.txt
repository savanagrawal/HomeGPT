# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages

# Set include directories
set(INCLUDE_DIRS

)

# Set source files
set( SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp

)

# Set header files
set( HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.h

)

# Create peripherals library
add_library( ${PROJECT_NAME}_ControllerLib SHARED ${SOURCES} )

# Link directories or libraries