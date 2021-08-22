#include <allegro.h>
#include <cstdlib>



#define MARCOFILAS 20 // filas de la matriz para la pantalla
#define MARCOCOLUMNAS 31 // columnas de la matriz para la pantalla

using namespace std;
BITMAP *buffer; // m�scara de la pantalla
BITMAP *roca; //variable para almacenar el dibujo de la roca
BITMAP *pacbmp; // variable para almacenar el dibujo completo de pacman
BITMAP *pacman; // variable para tomar una de las posiciones de pacman
BITMAP *comida; // comida de pacman
BITMAP *ganador, *inicio;
BITMAP *muertebmp;
SAMPLE *musica1;
SAMPLE *bolita;
SAMPLE *muerte;
SAMPLE *camina;

int dir=4; // variable para observar la direcci�n del pacman
int px=30*14, py =30*17; // posici�n de pacman en X y en Y


int anteriorpx, anteriorpy;


char mapa [MARCOFILAS][MARCOCOLUMNAS]={
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "Xoooo|ooooo XXXXX oooooo|ooooX",
        "XoXXXoXXXXXoXXXXX XXXXXXoXXX X",
        "X XXXoXXXXXoXXXXX XXXXXXoXXX X",
        "X|ooo|ooooooooooo|oooooo|ooo|X",
        "XoXXXoXX XXXXXXXXXXXX XXoXXX X",
        "X|   |XX ooooXXX      XXoooo|X",
        "XoXXXoXXXXXX XXX XXXXXXXoXXX X",
        "XoXXXoXX    o   |oooo XXoXXX X",
        " |   |XX XXXXXXXXXXXX XX|ooo| ",
        "X XXX XX XXXXXXXXXXXX XX XXX X",
        "X XXXoXX ooo|ooooooo  XX XXX X",
        "X XXXoXXXXXX XXX XXXXXXX XXX X",
        "X|   |XX     XXX      XX|ooo|X",
        "X XXX XX XXXXXXXXXXXX XX XXXoX",
        "X XXX|    |ooooooo   |  |XXXoX",
        "X XXX XXXX XXXXXXXXX XXX XXXoX",
        "X XXX XXXX   oooooo |XXX XXXoX",
        "Xoooo|oooooXXXXXXXXXoooo|ooooX",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

void dibujar_mapa (){

    int row, col;

    for(row=0;row<MARCOFILAS; row++){
        for(col=0; col<MARCOCOLUMNAS; col++){

            if(mapa[row][col]=='X'){

                draw_sprite(buffer, roca, col*30, row*30);
            }
            else if (mapa[row][col]=='o'){

                draw_sprite(buffer, comida, col*30, row*30);// aparezca la comida
                if(py/30 == row && px/30 == col) // pacman est� en esa misma posici�n
                {
                    play_sample(bolita,200, 127, 1000, 0);
                    mapa[row][col]= ' '; // desaparece la comida
                }

            }
        }
    }
}

void pantalla (){

    blit(buffer, screen,0,0,0,0,900,600);


    }
void dibujar_peronaje(){


    blit(pacbmp,pacman,dir*33,0,0,0,33,33);
    draw_sprite(buffer,pacman,px,py);//para establecer la transparencia de la imagen de pacman sobre el bufer del escenario
    //textprintf(buffer, font, "VIDAS" + char(vidas), 160, 25, 0xFFFFFF, 0x33FF5B);
}


bool game_over()
{
     int row, col;
    for(row=0;row<MARCOFILAS; row++){
        for(col=0; col<MARCOCOLUMNAS; col++){

            if(mapa[row][col]=='o')
                return true;
        }
    }
     while (!key[KEY_ESC])
{

    BITMAP *buffer = create_bitmap(242,242);

    draw_sprite(buffer, ganador, 0, 0 );
    blit(buffer, screen,0,0,0,0,242,242);
    rest(20);
}
return false;
}

void iniciar()
{


BITMAP *portada = create_bitmap (223,226);
draw_sprite(portada, inicio,0,0);
blit (portada, screen, 0,0,0,0, 223,242);

    readkey();

    destroy_bitmap(portada);


}


class fantasma
{
BITMAP *enemigobmp, *enemigo;
    int fdir; // variable para observar la direcci�n del fantasma
    int _x, _y;

    public:
        fantasma(int x, int y); //constructor
        void dibujar_fantasma () const;
        void mover_fantasma();
        void choque_pacman();
};
fantasma::fantasma(int x, int y)
{
    _x=x;
    _y=y;
    fdir =rand()%4;
    enemigo =create_bitmap (30,30);
    enemigobmp=load_bitmap("coronavirus.bmp", NULL);
}
void fantasma::dibujar_fantasma() const
{

    blit(enemigobmp,enemigo,0,0,0,0,30,30);
    draw_sprite(buffer,enemigo,_x, _y);//para establecer la transparencia de la imagen de pacman sobre el bufer del escenario
}


void fantasma::choque_pacman()
{
    if((py==_y && px ==_x )|| (_y==anteriorpy && _x == anteriorpx))
    {
        play_sample(muerte,200, 127, 1000, 0);
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



int main ()
{

    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 900, 600, 0, 0);
//inicializar audio
if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
       allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
       return 1;
    }
    set_volume(70, 70);
    musica1 = load_wav("pacman_music.wav");
    bolita = load_wav("pacman_comida.wav");
    muerte = load_wav("pacman_muerte.wav");
    camina = load_wav("waka waka.wav");


    buffer = create_bitmap(900, 600);
   roca=load_bitmap("block.bmp",NULL); //cargar imagen de la roca
   pacbmp=load_bitmap("Pacman.bmp",NULL); //carga el archivo con la imagen de pacman
   pacman = create_bitmap(33,33); //tama�o de una posici�n de pacman
   comida=load_bitmap("Comida.bmp",NULL); //cargar la imagen de la comida
   ganador=load_bitmap("ganar.bmp",NULL);

   muertebmp=load_bitmap("muerte.bmp", NULL);
    inicio=load_bitmap("inicio.bmp", NULL);
    iniciar();
    fantasma A(30*2,30*3);
    fantasma B(30*15,30*15);
    fantasma C(30*2,30*3);
    fantasma D(30*7,30*15);
    fantasma E(30*8,30*8);
    fantasma F(30*6,30*6);
    fantasma G(30*5,30*5);

    play_sample(musica1,125, 127, 1000, 1);
        while (!key[KEY_ESC]&& game_over())
            {
    if(dir!=4){
        play_sample(camina,170, 127, 1000, 0);
    }
        anteriorpx = px;
        anteriorpy = py;
        if(key[KEY_RIGHT]) dir=1; // apretarlo a derecha
        else if (key[KEY_LEFT]) dir=0; // apretarlo izuierda
        else if (key[KEY_UP]) dir=2; // apretarlo arriba
        else if (key[KEY_DOWN]) dir=3; // apretarlo abajo

        if (dir ==0) //moverlo a la izquierda
        {
            if(mapa[py/30][(px-30)/30]!='X') //revisar que no haya muro
              px -=30;
              else dir=4;
        }

        if (dir == 1) // moverlo a la derecha
        {
            if(mapa[py/30][(px+30)/30]!='X') //revisar que no haya muro
            px +=30;
             else dir=4;
        }
        if (dir == 2)  // moverlo arriba
        {
            if(mapa[(py-30)/30][(px/30)]!='X') //revisar que no haya muro

            py -= 30;
            else dir=4;
        }
        if (dir == 3)  // moverlo abajo
        {
            if(mapa[(py+30)/30][(px/30)]!='X') //revisar que no haya muro
            py +=30;
             else dir=4;
        }

        if (px<=-30) px=870; // salir por atajo izquierda
        else if (px>=870) px =-30;
        clear (buffer); //limpiar el bufer para que no quede rastro del movimiento
        dibujar_mapa();
        dibujar_peronaje();
        A.mover_fantasma();
        B.mover_fantasma();
        C.mover_fantasma();
        D.mover_fantasma();
        E.mover_fantasma();
        F.mover_fantasma();
        G.mover_fantasma();

        pantalla();
        rest(70); //peque�a pausa al sistema para ver el movimiento e pacman 70ms

        clear (pacman); //limpiar buffer para hacer que vaya mordiendo

            blit(pacbmp,pacman,4*33,0,0,0,33,33);
            draw_sprite(buffer,pacman,px,py);
         pantalla();
         rest(90);

        }


    return 0;
}
END_OF_MAIN ()
