# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
find_package( OpenCV REQUIRED )

# Set Include Directories
set( INCLUDE_DIRS
    ${OpenCV_INCLUDE_DIRS}
)


# Set Soruces
set( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/dataset-creator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/detector.cpp
)

# Set Headers
set( HEADERS

)

# Create intruder detection library
add_library( ${PROJECT_NAME}_IntruderDetectionLib SHARED ${SOURCES} )

# Link directories or libraries
target_include_directories( ${PROJECT_NAME}_IntruderDetectionLib PUBLIC ${INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME}_IntruderDetectionLib 
    ${OpenCV_LIBS}
)