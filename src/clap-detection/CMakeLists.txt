cmake_minimum_required(VERSION 2.8)
project( ClapDetection )

LIST(APPEND CMAKE_PREFIX_PATH /usr/local/lib/portaudio/)
find_package( portaudio REQUIRED )

add_executable( detectClapAMP detectClapAMP.cpp )
TARGET_LINK_LIBRARIES(detectClapAMP portaudio)

add_executable( detectClapFFT detectClapFFT.cpp )
TARGET_LINK_LIBRARIES(detectClapFFT portaudio)
