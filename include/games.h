#ifndef GAMES_H
#define GAMES_H

#include <util/delay.h>
#include <math.h>
#include "Framebuffer.h"
#include "config.h"
#include "transforms.h"
#include "inputs.h"


typedef enum{
    MENU = 0,
    CUBE_GAME = 1,
    TETRA_GAME = 2,
} E_GAMES;

void CubeGame(Framebuffer *fb);
void TetraGame(Framebuffer *fb);

#endif
