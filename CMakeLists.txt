cmake_minimum_required(VERSION 3.10)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include/SDL2)

link_directories(lib)

set(SOURCES
    MEDIA_PLAYER/mediaplayer.cpp
    MEDIA_PLAYER/playlist.cpp
    MEDIA_PLAYER/SongHistory.cpp
    MEDIA_PLAYER/Trackqueue.cpp
)

add_executable(player ${SOURCES})

target_link_libraries(player SDL2 SDL2_mixer)
