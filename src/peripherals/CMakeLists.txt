# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
find_package( OpenCV REQUIRED )

# Set include directories
set(INCLUDE_DIRS

)

# Set source files
set( SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
)

# Set header files
set( HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.h
)

# Create peripherals library
add_library( ${PROJECT_NAME}_PeripheralsLib SHARED ${SOURCES} )

# Link directories or libraries
target_link_libraries( ${PROJECT_NAME}_PeripheralsLib
    ${OpenCV_LIBS}
)