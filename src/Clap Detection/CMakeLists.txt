cmake_minimum_required(VERSION 2.8)
project( ClapDetection )

LIST(APPEND CMAKE_PREFIX_PATH /usr/local/lib/portaudio/)
find_package( portaudio REQUIRED )

add_executable( final_r final_r.cpp )

add_executable( detectclap detectclap.cpp )
TARGET_LINK_LIBRARIES(detectclap portaudio)
