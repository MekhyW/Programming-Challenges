#ifndef DRAWING_H
#define DRAWING_H

#include "geometry.h"

#define SIZE 240

#define WIDTH 640
#define HEIGHT 480

#define POINT_RADIUS 5
#define EDGE_WIDTH 3
#define RAY_WIDTH 1

#define BG_COLOR "#ffffff"
#define FG_COLOR "#000000"

#define NEG_COLOR "#ff0000"
#define POS_COLOR "#0000ff"
#define DEF_COLOR "#000000"
#define RAY_COLOR "#00ff00"

void draw_unit(point p, point a, point b, int result, char path[]);
void draw_integration(point p, point poly[], int n, int result, char path[]);

#endif
