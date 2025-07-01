#!/bin/bash
gcc paint.c -o paint `sdl2-config --cflags --libs`
./paint