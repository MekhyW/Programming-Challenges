#include <math.h>
#include <stdio.h>

#include "geometry.h"

double det(point p, point a, point b){
    /* 
    matriz disposta como 
    |1  1   1|
    |xa xb xp|
    |ya yb yp|
    */
    return b.x*p.y - p.x*b.y - a.x*p.y + p.x*a.y + a.x*b.y - b.x*a.y;
}

int relativo_reta(point p, point a, point b){
    /*  
    dado os vetores AB e AP, o sinal do det(AB,AP)
    determinará o lado relativo do ponto a reta
    */
    double estado = det(p,a,b);
    if (fabs(estado) < 1e-6){
        return 0;
    }
    else if (estado>0){
        return 1;
    } 
    else {
        return -1;
    }
}

point maior_ponto(point a, point b){
    if (a.y > b.y){
        return a;
    }
    else if (b.y > a.y){
        return b;
    }
    else {
        if (a.x > b.x){
            return a;
        }
        else {
            return b;
        }
    }
}

point menor_ponto(point a, point b){
    if (a.y < b.y){
        return a;
    }
    else if (b.y < a.y){
        return b;
    }
    else {
        if (a.x < b.x){
            return a;
        }
        else {
            return b;
        }
    }
}

int verify(point p, point a, point b) {
    point maior, menor;
    maior = maior_ponto(a,b);
    menor = menor_ponto(a,b);
    int posicao_relativa = relativo_reta(p, menor, maior);
    if (a.y == b.y) {
        /* reta horizontal ou pontos coincidentes */
        if (a.x == b.x) {
            /* pontos a e b são iguais */
            if (p.x == a.x && p.y == a.y) {
                return 2;
            } 
            else {
                return 0;
            }
        }
        if (posicao_relativa == 0){
            /* são colineares */
            if ((menor.x <= p.x) && (p.x <= maior.x)){
                return 2;
            } else {
                return 0;
            }
        }
    }
    if (menor.y <= p.y && p.y <= maior.y){
        /* caso onde p está sobre a aresta ou cruzou */
        /* se colineares, estão sobre a mesma reta */
        if (posicao_relativa == 0) {
            return 2;
        } else if (posicao_relativa == -1) {
            /* ponto a direita da reta, logo cruza */
            if (menor.y == p.y) {
                return 0;
            }
            return 1;
        } else if (posicao_relativa == 1){
            return 0;
        }
    } 
    else {
        return 0;
    }
    return 0;
}

int inside(point p, point poly[], int n) {
    int interceptacoes = 0;
    int resultado_verify;
    for (int i=0; i<n; i++){
        if (i == n-1){
            resultado_verify = verify(p, poly[i], poly[0]);
        }
        else {
            resultado_verify = verify(p, poly[i], poly[i+1]);
        }
        if (resultado_verify == 2){
            return 1;
        }
        if (resultado_verify == 1){
            interceptacoes++;
        }
    }
    return interceptacoes%2;
}
