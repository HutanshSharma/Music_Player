# Overview

This is a terminal-based music player developed in C++ with SDL3 for handling audio playback. It simulates key functionalities of modern music players such as playlist looping, play history, and a song queue — all managed through well-defined data structures. The project is designed for learning and demonstrating data structures in a practical context.

# Features

· Add, remove, or view songs in the playlist

· Loop playback for a single song

· Play, pause, resume, stop functionalities

· Automatically proceed to the next song

· Navigate backward and forward in the playlist

· Queue specific songs to play next

· Track history of played songs

# Data Structures Used

1. Doubly Circular Linked List (Playlist)

· Custom-implemented

· Allows smooth looping of songs in both directions

2. Stack (History)

· Tracks recently played songs

· Supports viewing and managing playback history

3. Deque (Queue)

· Flexible system to schedule songs to play next

· Supports insertion/removal at both ends

# Technology Stack

· Language: C++17

· Audio Engine: SDL3, SDL_mixer

· Build System: CMake

· Terminal Interface: Console-based (no GUI)

· Filesystem: Uses std::filesystem to validate paths and list songs

· Development Environment: Recommended with Visual Studio Code

# Sample Audio Files

Sample .ogg and .mp3 audio files have been included in the repository under the /songs directory to help you test the functionality right away.

# Building and Running

## Prerequisites

· C++17-compatible compiler (e.g., g++, clang++)

· CMake 3.15+

· SDL3 and SDL3_mixer development libraries installed and discoverable. SDL2 headers are included under the terms of the LGPL v2.1 license. See SDL website for more info.

## VS Code Instructions

The project is set up for Visual Studio Code with CMake Tools extension.

1. Open the project in VS Code

2. Press Ctrl + Shift + B to build the project using CMake

3. Press F5 to run the executable

The terminal will launch the music player with interactive menu options.

## CLI Alternative

If you're not using VS Code:

mkdir build

cd build

cmake ..

cmake --build .

./music_player

and then run the player.exe file which would be in the bin directory.
