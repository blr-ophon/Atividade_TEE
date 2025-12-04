#include "transforms.h"

static Vec_2D map_3d_to_2d(Vec_3D *vec);
static void rotate_point_x(Vec_3D *vec, uint8_t reverse);
static void rotate_point_y(Vec_3D *vec, uint8_t reverse);
static void rotate_point_z(Vec_3D *vec, uint8_t reverse);


extern float SIN_A;
extern float COS_A;


void RotateAllPoints(Vec_3D *points3d, uint8_t n, E_AXIS axis, uint8_t reverse){
    void (*rotate_point[3])(Vec_3D*, uint8_t) = {
        rotate_point_x,
        rotate_point_y,
        rotate_point_z 
    };

    for(uint8_t i = 0; i < n; i++){
        rotate_point[axis](&points3d[i], reverse);
    }
}


void MapAllPoints(Vec_3D *points3d, Vec_2D *points2d, uint8_t n){
    for(uint8_t i = 0; i < n; i++){
        points2d[i] = map_3d_to_2d(&points3d[i]);
    }
}


Vec_2D map_3d_to_2d(Vec_3D *vec){
    float factor = DEPTH/(vec->z + CENTER_Z);
    Vec_2D vec2d;  
    vec2d.x = factor * vec->x + CENTER_X;
    vec2d.y = factor * vec->y + CENTER_Y;
    return vec2d;
}


void rotate_point_x(Vec_3D *vec, uint8_t reverse){
    float direction = reverse? -1 : 1;
    Vec_3D tmp = *vec;
    vec->y = tmp.y * COS_A - tmp.z * (SIN_A*direction);
    vec->z = tmp.y * (SIN_A*direction) + tmp.z * COS_A;
}


void rotate_point_y(Vec_3D *vec, uint8_t reverse){
    float direction = reverse? -1 : 1;
    Vec_3D tmp = *vec;
    vec->x = tmp.x * COS_A + tmp.z * (SIN_A*direction);
    vec->z = -tmp.x * (SIN_A*direction) + tmp.z * COS_A;
}


void rotate_point_z(Vec_3D *vec, uint8_t reverse){
    float direction = reverse? -1 : 1;
    Vec_3D tmp = *vec;
    vec->x = tmp.x * COS_A - tmp.y * (SIN_A*direction);
    vec->y = tmp.x * (SIN_A*direction) + tmp.y * COS_A;
}
