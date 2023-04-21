# Project Details
cmake_minimum_required( VERSION 3.0 )

project( HomeGPT VERSION 0.1 )

# Find packages
find_package( OpenCV REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../utils )

# Set include directories
set(INCLUDE_DIRS

)

# Set source files
set( SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPIODriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RFID.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RelayBoard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ServoMotor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LEDController.cpp
)

# Set header files
set( HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GPIODriver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RFID.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RelayBoard.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ServoMotor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LEDController.h
)

# Create peripherals library
add_library( ${PROJECT_NAME}_PeripheralsLib SHARED ${SOURCES} )

# Link directories or libraries
target_link_libraries( ${PROJECT_NAME}_PeripheralsLib
    ${OpenCV_LIBS}
    spidevpp
    mfrc522
    ${PROJECT_NAME}_UtilsLib
)

set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/GPIODriver.h )

set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/RFID.h )

set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/RelayBoard.h )

set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/ServoMotor.h )
  
set_target_properties( ${PROJECT_NAME}_PeripheralsLib PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/LEDController.h )
