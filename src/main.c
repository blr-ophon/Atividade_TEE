#include "main.h"

volatile float SIN_A;
volatile float COS_A;
volatile GameInputs INPUTS = {{0}};


static const uint8_t cube_edges[12][2] = {
    {0,1}, {1,3}, {3,2}, {2,0},
    {4,5}, {5,7}, {7,6}, {6,4},
    {0,4}, {1,5}, {2,6}, {3,7}
};


ISR(PCINT2_vect){
    INPUTS.buttons[INPUT_Z_POS] = bit_is_clear(PIND, PD2)? 1 : 0;
    INPUTS.buttons[INPUT_Z_NEG] = bit_is_clear(PIND, PD3)? 1 : 0;
    INPUTS.buttons[INPUT_X_NEG] = bit_is_clear(PIND, PD4)? 1 : 0;
    INPUTS.buttons[INPUT_X_POS] = bit_is_clear(PIND, PD5)? 1 : 0;
    INPUTS.buttons[INPUT_Y_NEG] = bit_is_clear(PIND, PD6)? 1 : 0;
    INPUTS.buttons[INPUT_Y_POS] = bit_is_clear(PIND, PD7)? 1 : 0;
}


int main(void){
    //GPIO
    PORTD |= (1 << PD2);
    PORTD |= (1 << PD3);
    PORTD |= (1 << PD4);
    PORTD |= (1 << PD5);
    PORTD |= (1 << PD6);
    PORTD |= (1 << PD7);

    // Interrupts
    for(int i = 18; i <= 23; i++){
        initPCInt(i);
    }
    
    Framebuffer fb;

    SIN_A = sin(ROTATING_ANGLE * PI / 180.0);
    COS_A = cos(ROTATING_ANGLE * PI / 180.0);

    Vec_3D points3d[] = {
        { -CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH},
        { -CUBE_LENGTH, -CUBE_LENGTH,  CUBE_LENGTH},
        { -CUBE_LENGTH,  CUBE_LENGTH, -CUBE_LENGTH},
        { -CUBE_LENGTH,  CUBE_LENGTH,  CUBE_LENGTH},
        {  CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH},
        {  CUBE_LENGTH, -CUBE_LENGTH,  CUBE_LENGTH},
        {  CUBE_LENGTH,  CUBE_LENGTH, -CUBE_LENGTH},
        {  CUBE_LENGTH,  CUBE_LENGTH,  CUBE_LENGTH},
    };

    Vec_2D points2d[8];

    MapAllPoints(points3d, points2d, 8);

    uint8_t running = 1;
    while(running){
        // Proccess Inputs and update
        if(INPUTS.buttons[INPUT_X_POS]){
            RotateAllPoints(points3d, 8, X_AXIS, 0);
        }else if(INPUTS.buttons[INPUT_X_NEG]){
            RotateAllPoints(points3d, 8, X_AXIS, 1);
        }
        if(INPUTS.buttons[INPUT_Y_POS]){
            RotateAllPoints(points3d, 8, Y_AXIS, 0);
        }else if(INPUTS.buttons[INPUT_Y_NEG]){
            RotateAllPoints(points3d, 8, Y_AXIS, 1);
        }

        if(INPUTS.buttons[INPUT_Z_POS]){
            RotateAllPoints(points3d, 8, Z_AXIS, 0);
        }else if(INPUTS.buttons[INPUT_Z_NEG]){
            RotateAllPoints(points3d, 8, Z_AXIS, 1);
        }
        MapAllPoints(points3d, points2d, 8);

        // Render
        fb.clear();
        RenderCube(&fb, points2d);
        fb.show();
        _delay_ms(5);
    }

    return 0;
}


void RenderAllPoints(Framebuffer *fb, Vec_2D *points, uint8_t n){
    for(uint8_t i = 0; i < n; i++){
        fb->drawPixel(points[i].x, points[i].y);
    }
}


void RenderCube(Framebuffer *fb, Vec_2D *points2d){
    for (uint8_t i = 0; i < 12; i++) {
        uint8_t a = cube_edges[i][0];
        uint8_t b = cube_edges[i][1];

        fb->drawLine(
            points2d[a].x, points2d[a].y,
            points2d[b].x, points2d[b].y
        );
    }
}
