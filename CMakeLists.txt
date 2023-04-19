# Project Details
cmake_minimum_required( VERSION 3.0 )

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project( HomeGPT VERSION 0.1 )


# Find packages
find_package( Threads REQUIRED )
find_package( Boost COMPONENTS system filesystem REQUIRED)

# Add all subdirectories for project
add_subdirectory( src/peripherals )
add_subdirectory( src/dependencies/spidevpp/libs )
add_subdirectory( src/dependencies/mfrc522 )
# add_subdirectory( src/controller )
add_subdirectory( src/utils )
add_subdirectory( src/thread )
add_subdirectory( src/clap-detection )
add_subdirectory( src/intruder-detection )
add_subdirectory( src/intruder-mood-detection )
add_subdirectory( src/mood-detection )

include_directories( src/thread
    ${Boost_INCLUDE_DIRS}

)

# Set include directories
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mood-detection
    ${CMAKE_CURRENT_SOURCE_DIR}/src/intruder-mood-detection
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clap-detection
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thread
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clap-detection
)

# Set source files
set( SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# Set header files
set( HEADERS 

)

# Create project library for testing
add_library( ${PROJECT_NAME}_Lib SHARED ${SOURCES} )
# target_link_directories( ${PROJECT_NAME}_Lib PUBLIC ${INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME}_Lib 
    ${CMAKE_THREAD_LIBS_INIT}
    rt
    pigpio
    stdc++fs
    cpptimer
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    # ${PROJECT_NAME}_PeripheralsLib
    ${PROJECT_NAME}_ClapDetectionLib
    ${PROJECT_NAME}_MoodDetectionLib
    ${PROJECT_NAME}_IntruderDetectionLib
    ${PROJECT_NAME}_IntruderMoodDetectionLib
    ${PROJECT_NAME}_ThreadLib
)

# Create an executable for raspberry pi to run
add_executable(${PROJECT_NAME} src/main.cpp)
set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)

# Link directories or libraries
# target_link_directories( ${PROJECT_NAME} PUBLIC ${INCLUDE_DIR} )
target_link_libraries( ${PROJECT_NAME} ${PROJECT_NAME}_Lib )

# Enable testing command
enable_testing()
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/test )