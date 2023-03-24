#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct {
    int x;
    int y;
} point;

int verify(point p, point a, point b);
int inside(point p, point poly[], int n);

#endif
