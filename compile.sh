#!/bin/bash
printf "\033c"
gcc main.c -lSDL2 -lSDL2_ttf -lm -o main.out
