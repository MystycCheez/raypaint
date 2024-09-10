@echo off
gcc -o raypaint.exe main.c -std=c99 -Wall -Wextra -lraylib -IC:\raylib\src -LC:\raylib\src -lgdi32 -lwinmm -Wno-unused-parameter raylib.h
raypaint.exe