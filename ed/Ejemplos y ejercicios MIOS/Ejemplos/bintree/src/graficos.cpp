/**
  * @file graficos.cpp
  * @brief Fichero con definiciones para la gestión de gráficos
  *
  * Implementa la interfaz de graficos.h
  *
  */


/* ***************************************** */

#include <iostream>
#include <cstdlib>
#include "graficos.h"

/* ***************************************** */

using namespace std;

namespace {
  // Variable que representa la pantalla (ventana) donde vamos a dibujar
  SDL_Surface *ventana;
}

/* ***************************************** */

void CrearVentana(int ancho, int alto, const char *titulo)
{
  // Iniciamos el módulo de gráficos de la SDL
  if (SDL_Init(SDL_INIT_VIDEO)<0) {
    cerr << "No se puede iniciar SDL ("<<SDL_GetError()<<")"<<endl;
    exit(-1);
  }

  // Ponemos el modo de video:
  // Dimensiones de la ventana: ancho x alto
  // Profundidad de color: número de bits para representar el color de un pixel
  ventana=SDL_SetVideoMode(ancho,alto,32,SDL_SWSURFACE|SDL_ANYFORMAT);
  if (ventana==0) {
    cerr << "No se puede iniciar modo grafico ("<<SDL_GetError()<<")"<<endl;
    SDL_Quit();
    exit(-1);
  }

  // Ponemos el título de la ventana
  SDL_WM_SetCaption(titulo,0);

  // Antes de finalizar el programa llamaremos a la función SDL_Quit
  atexit(SDL_Quit);
}

/* ***************************************** */

void LimpiarVentana()
{
  int i;
  /* Set the screen to black */
  if ( SDL_LockSurface(ventana) == 0 ) {
    Uint32 black;
    Uint8 *pixels;
    black = SDL_MapRGB(ventana->format, 0, 0, 0);
    pixels = (Uint8 *)ventana->pixels;
    for ( i=0; i<ventana->h; ++i ) {
      memset(pixels, black,
              ventana->w*ventana->format->BytesPerPixel);
      pixels += ventana->pitch;
    }
    SDL_UnlockSurface(ventana);
  }
}

/* ***************************************** */

int FilasVentana()
{
  return ventana->h;
}

/* ***************************************** */

int ColumnasVentana()
{
  return ventana->w;
}

/* ***************************************** */

void Punto(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
  pixelRGBA(ventana, x, y, r, g, b, 255);
  SDL_UpdateRect(ventana, x, y, 1, 1);
}

/* ***************************************** */

void Linea(int x1, int y1, int x2, int y2,
           unsigned char r, unsigned char g, unsigned char b)
{
  lineRGBA(ventana, x1, y1, x2, y2, r, g, b, 255);
  SDL_UpdateRect(ventana, min(x1,x2), min(y1,y2), abs(x1-x2)+1, abs(y1-y2)+1);
}

/* ***************************************** */

void Circulo(int x, int y, int rad,
             unsigned char r, unsigned char g, unsigned char b)
{
  circleRGBA(ventana, x, y, rad, r, g, b,255);
  SDL_UpdateRect(ventana, x-rad, y-rad, rad*2+1, rad*2+1);
}

/* ***************************************** */

void CirculoR(int x, int y, int rad,
              unsigned char r, unsigned char g, unsigned char b)
{
  filledCircleRGBA(ventana, x, y, rad, r, g, b,255);
  SDL_UpdateRect(ventana, x-rad, y-rad, rad*2+1, rad*2+1);
}

/* ***************************************** */

void Rectangulo(int x1, int y1, int x2, int y2,
              unsigned char r, unsigned char g, unsigned char b)
{
  rectangleRGBA(ventana, x1, y1, x2, y2, r, g, b, 255);
  SDL_UpdateRect(ventana, min(x1,x2), min(y1,y2), abs(x1-x2)+1, abs(y1-y2)+1);
}

/* ***************************************** */

void RectanguloR(int x1, int y1, int x2, int y2,
              unsigned char r, unsigned char g, unsigned char b)
{
  boxRGBA(ventana, x1, y1, x2, y2, r, g, b, 255);
  SDL_UpdateRect(ventana, min(x1,x2), min(y1,y2), abs(x1-x2)+1, abs(y1-y2)+1);
}

/* ***************************************** */

void Elipse(int x, int y, int radx, int rady,
             unsigned char r, unsigned char g, unsigned char b)
{
  ellipseRGBA(ventana, x, y, radx, rady, r, g, b,255);
  SDL_UpdateRect(ventana, x-radx, y-rady, radx*2+1, rady*2+1);
}

/* ***************************************** */

void ElipseR(int x, int y, int radx, int rady,
             unsigned char r, unsigned char g, unsigned char b)
{
  filledEllipseRGBA(ventana, x, y, radx, rady, r, g, b,255);
  SDL_UpdateRect(ventana, x-radx, y-rady, radx*2+1, rady*2+1);
}

/* ***************************************** */

void Texto(int x, int y, const char *c,
             unsigned char r, unsigned char g, unsigned char b)
{
  stringRGBA(ventana, x, y, c, r, g, b, 255);
  SDL_UpdateRect(ventana, 0, 0, 0, 0);
}

/* ***************************************** */

// Obtenemos el color del punto que hay en las coordenadas (x,y)
// Devolvemos el valor en (r,g,b)
void ObtenerPunto(int x, int y,
                  unsigned char &r, unsigned char &g, unsigned char &b)
{
  int bpp = ventana->format->BytesPerPixel;
  Uint8 *p = (Uint8*)ventana->pixels + y*ventana->pitch + x*bpp;
  Uint32 color=0;

  // Bloqueamos la ventana si es necesario
  if (SDL_MUSTLOCK(ventana)) {
    if (SDL_LockSurface(ventana)<0) {
      cerr << "Error al bloquear la ventana ("<<SDL_GetError()<<")"<<endl;
      SDL_Quit();
      exit(-1);
    }
  }

  // Obtenemos punto
  switch (bpp) {
    case 1:
      color = *p;
      break;
    case 2:
      color = *(Uint16*)p;
      break;
    case 3:
      if (SDL_BYTEORDER==SDL_BIG_ENDIAN)
        color = p[0]<<16 | p[1]<<8 | p[2];
      else
        color = p[0] | p[1]<<8 | p[2]<<16;
      break;
    case 4:
      color = *(Uint32*)p;
      break;
  }

  // Desbloqueamos la ventana si es necesario
  if (SDL_MUSTLOCK(ventana)) {
    SDL_UnlockSurface(ventana);
  }

  // Decodificamos el color en sus 3 componentes R, G y B
  SDL_GetRGB(color,ventana->format,&r,&g,&b);
}

/* ***************************************** */

SDL_Surface *LeerImagenBMP(const char *fich)
{
  SDL_Surface *img;
  if (!(img=SDL_LoadBMP(fich))) {
    cerr << "No es posible cargar el fichero "<<fich<<endl;
    cerr << SDL_GetError() << endl;
    return 0;
  }
  return img;
}

/* ***************************************** */

void LiberarImagenBMP(SDL_Surface *img)
{
  if (img)
    SDL_FreeSurface(img);
}

/* ***************************************** */

void DimensionesBMP(const char *imagen, int& x, int& y)
{
  SDL_Surface *img= LeerImagenBMP(imagen);
  x=y=0;
  if (img!=0) {
    x= img->w;
    y= img->h;
    LiberarImagenBMP(img);
  }
}

/* ***************************************** */

void DibujarImagenBMP(SDL_Surface *img, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = img->w;
  dest.h = img->h;
  //SDL_SetAlpha(img, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
  //SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format, 255, 255, 255));
  SDL_BlitSurface(img, NULL, ventana, &dest);

  SDL_UpdateRect(ventana, x, y, img->w, img->h);
}

/* ***************************************** */

int ObtenerClick(int &x, int &y)
{
  SDL_Event evento;
  int boton;
  bool fin=false;
  while (!fin) {
    if (SDL_PollEvent(&evento)) {
      switch (evento.type) {
        case SDL_MOUSEBUTTONDOWN:    // Pulsamos botón del ratón
          boton = (int)(evento.button.button);
          x = evento.button.x;
          y = evento.button.y;
          fin = true;
	  break;
	case SDL_QUIT:
	  exit(1);                      // Pulsar X de ventana
      }
    }
  }
  return boton;
}

/* ***************************************** */

int ObtenerTecla()
{
  SDL_Event evento;
  int tecla;
  bool fin=false;
  while (!fin) {
    if (SDL_PollEvent(&evento)) {
      switch (evento.type) {
        case SDL_KEYDOWN:    // Pulsamos una tecla
          tecla = (int)(evento.key.keysym.scancode);
          fin = true;
        break;
        case SDL_QUIT:
	          exit(1);      // Pulsar X de ventana
      }
    }
  }
  return tecla;
}

/* ***************************************** */

void Esperar(int ms)
{
  SDL_Delay(ms);
}

/* ***************************************** */
