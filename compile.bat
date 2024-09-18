@echo off
gcc -o raypaint.exe main.c -std=c99 -Wall -Wextra -IC:\raylib\src -LC:\raylib\src -lraylib -lgdi32 -lwinmm -Wno-unused-parameter
raypaint.exe