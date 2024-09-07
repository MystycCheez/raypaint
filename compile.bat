@echo off
gcc -o raypaint.exe main.c -std=c99 -Wall -Wextra -lraylib -Wno-unused-parameter raylib.h
raypaint.exe