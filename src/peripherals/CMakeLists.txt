# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
find_package( OpenCV REQUIRED )
find_library( bcm2835 PATHS /usr/local/lib )
# find_library( mfrc522 PATHS /home/pi/mfrc522/mfrc522-cpp/build/libs/mfrc522 )
# include_directories( /home/pi/mfrc522/mfrc522-cpp/libs/mfrc522 )
# link_directories( /home/pi/mfrc522/mfrc522-cpp/build/libs/mfrc522 )

# Set include directories
set(INCLUDE_DIRS

)

# Set source files
set( SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/libmfrc522.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPIODriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RFID.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RelayBoard.cpp
)

# Set header files
set( HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/libmfrc522.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPIODriver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RFID.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RelayBoard.h
)

# Create peripherals library
add_library( ${PROJECT_NAME}_PeripheralsLib SHARED ${SOURCES} )

# Link directories or libraries
target_link_libraries( ${PROJECT_NAME}_PeripheralsLib
    # /home/pi/mfrc522/mfrc522-cpp/build/libs/mfrc522/libmfrc522.a
    ${OpenCV_LIBS}
)

set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/libmfrc522.h )

set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/GPIODriver.h )

set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/RFID.h )

set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/RelayBoard.h )
