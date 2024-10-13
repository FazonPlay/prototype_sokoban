#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#ifndef __STRUCT_H__
#define __STRUCT_H__

#define WIDTH 10
#define HEIGHT 10


typedef enum {
    EMPTY = ' ',
    WALL = '#',
    PLAYER = 'o',
    BOX = 'X',
    GOAL = '.'
} Element;


typedef struct {
    int x;
    int y;
} playerPosition;




#endif

