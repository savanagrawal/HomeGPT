# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )
set(CMAKE_CXX_STANDARD 17)

# Find packages
# find_library(${PROJECT_NAME}_MoodDetectionLib ${PROJECT_NAME}_MoodDetectionLib REQUIRED)
find_package( Threads REQUIRED )
find_package( OpenCV REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../peripherals )
# include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/spidevpp/libs )
# include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/mfrc522 )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../controller )
#include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../mood-detection )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../intruder-detection )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../intruder-mood-detection )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../clap-detection )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../rfid )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../utils )

# Set include directories
set(INCLUDE_DIRS
    ${OpenCV_INCLUDE_DIRS}

)

# Set source files
set( SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/ControllerThread.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/mood-detection/MoodThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/intruder-detection/IntruderThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/intruder-mood-detection/IntruderMoodThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clap-detection/ClapThread.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/clap-detection/AudioRecordThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rfid/RFIDThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/doors/DoorsThread.cpp
)

# Set header files
set( HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/CppThread.h
    #${CMAKE_CURRENT_SOURCE_DIR}/mood-detection/MoodThread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/intruder-detection/IntruderThread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/intruder-mood-detection/IntruderMoodThread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/clap-detection/ClapThread.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/clap-detection/AudioRecordThread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rfid/RFIDThread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/doors/DoorsThread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ControllerThread.h

)

# Create peripherals library
add_library( ${PROJECT_NAME}_ThreadLib SHARED ${SOURCES} )

# Link directories or libraries
target_link_libraries( ${PROJECT_NAME}_ThreadLib
    ${OpenCV_LIBS}
    spidevpp
    mfrc522
    ${PROJECT_NAME}_UtilsLib
    ${PROJECT_NAME}_PeripheralsLib
    #${PROJECT_NAME}_MoodDetectionLib
    ${PROJECT_NAME}_IntruderDetectionLib
    ${PROJECT_NAME}_IntruderMoodDetectionLib
    ${PROJECT_NAME}_ClapDetectionLib
)
