#include <math.h>
#include <stdio.h>

#include "drawing.h"

void draw(point p, point poly[], int n, int result, char path[], int width, int height) {
    FILE *file = fopen(path, "w");

    fprintf(file, "<?xml version=\"1.0\"?>\n");
    fprintf(file, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n", width, height);
    fprintf(file, "    <rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" stroke=\"%s\" fill=\"%s\"/>\n", width, height, BG_COLOR, BG_COLOR);

    fprintf(file, "    <polygon points=\" ");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d,%d ", poly[i].x, height - poly[i].y - 1);
    }
    fprintf(file, "\" stroke-width=\"%d\" stroke=\"%s\" fill=\"none\"/>\n", EDGE_WIDTH, FG_COLOR);

    char *color;
    switch (result) {
    case 0:
        color = NEG_COLOR;
        break;
    case 1:
        color = POS_COLOR;
        break;
    default:
        color = DEF_COLOR;
    }

    fprintf(file, "    <circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"%s\" fill=\"%s\"/>\n", p.x, height - p.y - 1, POINT_RADIUS, color, color);
    fprintf(file, "    <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"%d\" stroke=\"%s\" fill=\"none\"/>\n", p.x, height - p.y - 1, 0, height - p.y - 1, RAY_WIDTH, RAY_COLOR);
    fprintf(file, "</svg>\n");

    fclose(file);
}

point convert(point p) {
    point cp;

    double shift = SIZE / 6.0;

    cp.x = (int)((p.x + 1) * shift + 0.5);
    cp.y = (int)((p.y + 1) * shift + 0.5);

    return cp;
}

void draw_unit(point p, point a, point b, int result, char path[]) {
    p = convert(p);

    point poly[] = {convert(a), convert(b)};

    draw(p, poly, 2, result, path, SIZE, SIZE);
}

void draw_integration(point p, point poly[], int n, int result, char path[]) {
    draw(p, poly, n, result, path, WIDTH, HEIGHT);
}
