#include <allegro.h>
#ifndef FANTASMA_H
#define FANTASMA_H


class fantasma
{
BITMAP *enemigobmp, *enemigo, *buffer, *pacman;
    int fdir = 0; // variable para observar la dirección del fantasma
    int _x, _y;
    int px, py;
    int anteriorpx, anteriorpy;
    public:
        fantasma(int x, int y); //constructor
        void dibujar_fantasma () const;
        void mover_fantasma();
        void choque_pacman();

        virtual ~fantasma();

    protected:

    private:
};
void fantasma::dibujar_fantasma() const
{

    blit(enemigobmp,enemigo,0,0,0,0,30,30);
    draw_sprite(buffer,enemigo,_x, _y);//para establecer la transparencia de la imagen de pacman sobre el bufer del escenario
}

void fantasma::choque_pacman()
{
    if((py==_y && px ==_x )|| (_y==anteriorpy && _x == anteriorpx))
    {
        for (int j=0; j<5; j++)
            {
            clear(pacman);
            clear(buffer);
            dibujar_mapa();



            blit(muertebmp,pacman,j*33,0,0,0,33,33);
            draw_sprite(buffer,pacman,px,py);
            pantalla();
            rest (80);
                }
    px=30*14;
    py=30*17;
    dir =4;
    }
}
void fantasma::mover_fantasma()
{
      dibujar_fantasma();
    choque_pacman();
    //movimiento del fantasma

    if (mapa[_y/30][_x/30]=='|')
            {
        fdir=rand()%4;
            }
    if (fdir==0)
        {
        if(mapa[_y/30][(_x-30)/30]!='X')_x-=30;
        else fdir = rand()%4;
        }
        if (fdir==1)
        {
        if(mapa[_y/30][(_x+30)/30]!='X')_x+=30;
        else fdir = rand()%4;
        }
        if (fdir==2)
        {
        if(mapa[(_y-30)/30][_x/30]!='X')_y-=30;
        else fdir = rand()%4;
        } if (fdir==3)
        {
        if(mapa[(_y+30)/30][_x/30]!='X')_y+=30;
        else fdir = rand()%4;
    }
    // atajo
    if (_x<=-30) _x=870; // salir por atajo izquierda
        else if (_x>=870) _x =-30;


}

#endif // FANTASMA_H
