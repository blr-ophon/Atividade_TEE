#ifndef MAIN_H
#define MAIN_H

#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "interrupts.h"
#include "Framebuffer.h"
#include "config.h"
#include "transforms.h"

typedef struct{
    uint8_t buttons[6];
} GameInputs;

typedef enum{
    INPUT_X_POS = 0,
    INPUT_X_NEG = 1,
    INPUT_Y_POS = 2,
    INPUT_Y_NEG = 3,
    INPUT_Z_POS = 4,
    INPUT_Z_NEG = 5
} E_INPUTS;


void RenderAllPoints(Framebuffer fb, Vec_2D *points, uint8_t n);
void RenderCube(Framebuffer *fb, Vec_2D *points2d);
void print_3d_vec(Vec_3D *vec);
void print_2d_vec(Vec_2D *vec);

#endif
