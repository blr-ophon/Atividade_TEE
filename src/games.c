#include "games.h"

extern GameInputs INPUTS;
volatile float SIN_A;
volatile float COS_A;

static const uint8_t cube_edges[12][2] = {
    {0,1}, {1,3}, {3,2}, {2,0},
    {4,5}, {5,7}, {7,6}, {6,4},
    {0,4}, {1,5}, {2,6}, {3,7}
};

static const uint8_t tetra_edges[6][2] = {
    {0, 1},
    {0, 2},
    {0, 3},
    {1, 2},
    {1, 3},
    {2, 3}
};

static void RenderAllPoints(Framebuffer fb, Vec_2D *points, uint8_t n);
static void RenderCube(Framebuffer *fb, Vec_2D *points2d);
static void RenderTetra(Framebuffer *fb, Vec_2D *points2d);

void CubeGame(Framebuffer *fb){

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

    while(INPUTS.game_select == CUBE_GAME){
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
        fb->clear();
        RenderCube(fb, points2d);
        fb->show();
        _delay_ms(5);
    }
}


void TetraGame(Framebuffer *fb){

    SIN_A = sin(ROTATING_ANGLE * PI / 180.0);
    COS_A = cos(ROTATING_ANGLE * PI / 180.0);

    Vec_3D points3d[] = {
        {  CUBE_LENGTH,  CUBE_LENGTH,  CUBE_LENGTH},   // Vertex 0
        { -CUBE_LENGTH, -CUBE_LENGTH,  CUBE_LENGTH},   // Vertex 1
        { -CUBE_LENGTH,  CUBE_LENGTH, -CUBE_LENGTH},   // Vertex 2
        {  CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH}    // Vertex 3
    };

    Vec_2D points2d[4];

    MapAllPoints(points3d, points2d, 4);

    while(INPUTS.game_select == TETRA_GAME){
        // Proccess Inputs and update
        if(INPUTS.buttons[INPUT_X_POS]){
            RotateAllPoints(points3d, 4, X_AXIS, 0);
        }else if(INPUTS.buttons[INPUT_X_NEG]){
            RotateAllPoints(points3d, 4, X_AXIS, 1);
        }
        if(INPUTS.buttons[INPUT_Y_POS]){
            RotateAllPoints(points3d, 4, Y_AXIS, 0);
        }else if(INPUTS.buttons[INPUT_Y_NEG]){
            RotateAllPoints(points3d, 4, Y_AXIS, 1);
        }

        if(INPUTS.buttons[INPUT_Z_POS]){
            RotateAllPoints(points3d, 4, Z_AXIS, 0);
        }else if(INPUTS.buttons[INPUT_Z_NEG]){
            RotateAllPoints(points3d, 4, Z_AXIS, 1);
        }
        MapAllPoints(points3d, points2d, 4);

        // Render
        fb->clear();
        RenderTetra(fb, points2d);
        fb->show();
        _delay_ms(5);
    }
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


void RenderTetra(Framebuffer *fb, Vec_2D *points2d){
    for (uint8_t i = 0; i < 6; i++) {
        uint8_t a = tetra_edges[i][0];
        uint8_t b = tetra_edges[i][1];

        fb->drawLine(
            points2d[a].x, points2d[a].y,
            points2d[b].x, points2d[b].y
        );
    }
}


// void DrawMarkito(void){
//     char markito[] = "        ####            \r\n"
//                         "      ##########        \r\n"
//                         "  ###################   \r\n"
//                         "  ####################  \r\n"
//                         " #####################  \r\n"
//                         "##########  ##########  \r\n"
//                         "#######       ########  \r\n"
//                         "####             #####  \r\n"
//                         " ##              #####  \r\n"
//                         "  #               ####  \r\n"
//                         "           ###########  \r\n"
//                         "  #################    #\r\n"
//                         "  #####  ##########  # #\r\n"
//                         "  #####  #########    # \r\n"
//                         "   ## #               # \r\n"
//                         "     #                  \r\n"
//                         "  #                     \r\n"
//                         "  #                     \r\n"
//                         "                #       \r\n"
//                         "    # #####  ##      #  \r\n"
//                         "      ##    ##          \r\n"
//                         "      ######       #    \r\n"
//                         "        ###             \r\n" 
//                         "       #                \r\n"
//                         "         #####          \r\n";
// 
//     UART_print(markito);
// }
