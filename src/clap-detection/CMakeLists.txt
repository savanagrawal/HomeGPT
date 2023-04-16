# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
list(APPEND CMAKE_PREFIX_PATH /usr/local/lib/portaudio/)
find_package(portaudio REQUIRED)
include_directories(${PORTAUDIO_INCLUDE_DIRS})

# Set include directories
set(INCLUDE_DIRS

)

# Set source files
set( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ClapDetection.cpp
)

# Set header files
set( HEADERS

)

# Create clap detection library
add_library( ${PROJECT_NAME}_ClapDetectionLib SHARED ${SOURCES} )

# Link directories or libraries
# target_link_libraries(program ${PORTAUDIO_LIBRARIES})
