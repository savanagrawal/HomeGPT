# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
list(APPEND CMAKE_PREFIX_PATH /usr/local/lib/portaudio/)
find_package( portaudio REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../peripherals )

# Set include directories
set( include_directories
)

# Set source files
set( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ClapDetection.cpp
)

# Set header files
set( HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/ClapDetection.h

)

# Create mood detection library
add_library( ${PROJECT_NAME}_ClapDetectionLib SHARED ${SOURCES} )

# Link directories or libraries
target_include_directories( ${PROJECT_NAME}_ClapDetectionLib PUBLIC ${INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME}_ClapDetectionLib 
    cpptimer
    portaudio
)

set_target_properties( ${PROJECT_NAME}_ClapDetectionLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/ClapDetection.h )