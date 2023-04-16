cmake_minimum_required(VERSION 2.8)
project( ClapDetection )

add_executable( third third.cpp )

LIST(APPEND CMAKE_PREFIX_PATH /usr/local/lib/portaudio/)
find_package( portaudio REQUIRED )
add_executable( fifth fifth.cpp )
TARGET_LINK_LIBRARIES(fifth portaudio)

add_executable( detectmic detectmic.cpp )
TARGET_LINK_LIBRARIES(detectmic portaudio)

add_executable( detectclap detectclap.cpp )
TARGET_LINK_LIBRARIES(detectclap portaudio)

add_executable( paex_record paex_record.cpp )
TARGET_LINK_LIBRARIES(paex_record portaudio)

add_executable( paex_record_c paex_record.c )
TARGET_LINK_LIBRARIES(paex_record_c portaudio)
