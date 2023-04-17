# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
# find_library(${PROJECT_NAME}_MoodDetectionLib ${PROJECT_NAME}_MoodDetectionLib REQUIRED)
find_package(Threads REQUIRED)
find_package( OpenCV REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../peripherals )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../controller )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../mood-detection )

# Set include directories
set(INCLUDE_DIRS
    ${OpenCV_INCLUDE_DIRS}

)

# Set source files
set( SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/ControllerThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mood-detection/MoodThread.cpp

)

# Set header files
set( HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/CppThread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mood-detection/MoodThread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ControllerThread.h

)

# Create peripherals library
add_library( ${PROJECT_NAME}_ThreadLib SHARED ${SOURCES} )

# Link directories or libraries
target_link_libraries( ${PROJECT_NAME}_ThreadLib
    ${OpenCV_LIBS}
    ${PROJECT_NAME}_MoodDetectionLib
)