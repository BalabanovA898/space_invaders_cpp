#/bin/bash

g++ $(pkg-config --cflags --libs sdl2) main.cpp 
