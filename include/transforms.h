#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <avr/io.h>
#include "config.h"

#define CUBE_LENGTH             20
#define ROTATING_ANGLE          10
#define CENTER_X                SCREEN_W/2
#define CENTER_Y                SCREEN_H/2
#define CENTER_Z                CUBE_LENGTH*3
#define PI                      3.14159265358979323846
#define DEPTH                   CENTER_Z/2

typedef struct{
    float x;
    float y;
    float z;
}Vec_3D;

typedef struct{
    float x;
    float y;
}Vec_2D;

typedef enum{
    X_AXIS = 0,
    Y_AXIS = 1,
    Z_AXIS = 2,
} E_AXIS;

void RotateAllPoints(Vec_3D *points3d, uint8_t n, E_AXIS axis, uint8_t reverse);
void MapAllPoints(Vec_3D *points3d, Vec_2D *points2d, uint8_t n);


#endif
