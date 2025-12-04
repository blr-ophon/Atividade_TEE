/**
 * @file transforms.c
 * @brief 3d points transformations.
 */

#include "transforms.h"

static Vec_2D map_3d_to_2d(Vec_3D *vec);
static void rotate_point_x(Vec_3D *vec, uint8_t reverse);
static void rotate_point_y(Vec_3D *vec, uint8_t reverse);
static void rotate_point_z(Vec_3D *vec, uint8_t reverse);


extern float SIN_A;
extern float COS_A;


/**
 * @brief Rotates a set of points in 3d space.
 * @param points3d Array of points in 3d space.
 * @param n size of array
 * @param reverse Set for reverse direction.
 */
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


/**
 * @brief Generates projections from a set of points in 3d space to their 2d screen coordinates.
 * @param points3d Array of points in 3d space.
 * @param points2d Array of point coordinates in 2d screen.
 * @param n size of both arrays
 */
void MapAllPoints(Vec_3D *points3d, Vec_2D *points2d, uint8_t n){
    for(uint8_t i = 0; i < n; i++){
        points2d[i] = map_3d_to_2d(&points3d[i]);
    }
}


/**
 * @brief Generates transformation of point in 3d space to their 2d screen coordinates.
 * @param vec The point in 3d space.
 * @return 2d point mapped to screen plane.
 */
Vec_2D map_3d_to_2d(Vec_3D *vec){
    float factor = DEPTH/(vec->z + CENTER_Z);
    Vec_2D vec2d;  
    vec2d.x = factor * vec->x + CENTER_X;
    vec2d.y = factor * vec->y + CENTER_Y;
    return vec2d;
}


/**
 * @brief Rotate point in 3d space along x axis.
 * @param vec The point in 3d space.
 * @param reverse Set for reverse direction.
 */
void rotate_point_x(Vec_3D *vec, uint8_t reverse){
    float direction = reverse? -1 : 1;
    Vec_3D tmp = *vec;
    vec->y = tmp.y * COS_A - tmp.z * (SIN_A*direction);
    vec->z = tmp.y * (SIN_A*direction) + tmp.z * COS_A;
}


/**
 * @brief Rotate point in 3d space along y axis.
 * @param vec The point in 3d space.
 * @param reverse Set for reverse direction.
 */
void rotate_point_y(Vec_3D *vec, uint8_t reverse){
    float direction = reverse? -1 : 1;
    Vec_3D tmp = *vec;
    vec->x = tmp.x * COS_A + tmp.z * (SIN_A*direction);
    vec->z = -tmp.x * (SIN_A*direction) + tmp.z * COS_A;
}


/**
 * @brief Rotate point in 3d space along z axis.
 * @param vec The point in 3d space.
 * @param reverse Set for reverse direction.
 */
void rotate_point_z(Vec_3D *vec, uint8_t reverse){
    float direction = reverse? -1 : 1;
    Vec_3D tmp = *vec;
    vec->x = tmp.x * COS_A - tmp.y * (SIN_A*direction);
    vec->y = tmp.x * (SIN_A*direction) + tmp.y * COS_A;
}
