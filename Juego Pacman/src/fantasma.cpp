#include "fantasma.h"

fantasma::fantasma(int x, int y)
{
    _x=x;
    _y=y;
    fdir =rand()%4;
    enemigo =create_bitmap (30,30);
    enemigobmp=load_bitmap("coronavirus.bmp", NULL);
}

fantasma::~fantasma()
{
    //dtor
}
