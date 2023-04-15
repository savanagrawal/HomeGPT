cmake_minimum_required(VERSION 2.8)
project( ClapDetection )
find_package( portaudio REQUIRED )
add_executable( fifth fifth.cpp )
TARGET_LINK_LIBRARIES(fifth portaudio_static)

add_executable( detectmic detectmic.cpp )
TARGET_LINK_LIBRARIES(detectmic portaudio_static)

add_executable( detectclap detectclap.cpp )
TARGET_LINK_LIBRARIES(detectclap portaudio)
