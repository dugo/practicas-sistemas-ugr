
/* ***************************************** */

#ifndef __GRAFICOS__H__
#define __GRAFICOS__H__

/* ***************************************** */

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

/* ***************************************** */

/**
  * @brief Inicializar la biblioteca SDL y crear una ventana
  * @param ancho Número de columnas (en píxeles) de la ventana a crear.
  * @param alto Número de filas (en píxeles) de la ventana a crear.
  * @param titulo Cadena con el título de la ventana a crear.
  * @pre  @a ancho y @a alto deben ser positivos.
  */
void CrearVentana(int ancho, int alto, const char *titulo);


/**
  * @brief Consulta del alto de la ventana
  * @return  Las filas (alto) de la ventana en píxeles
  * @pre Se ha creado una ventana previamente con CrearVentana
  */
int FilasVentana();


/**
  * @brief Consulta del ancho de la ventana
  * @return  Las columnas (ancho) de la ventana en píxeles
  * @pre Se ha creado una ventana previamente con CrearVentana
  */
int ColumnasVentana();


/**
  * @brief Borrar la Ventana
  * @pre Se ha creado una ventana previamente con CrearVentana
  */
void LimpiarVentana();


/**
  * @brief Dibuja un punto de color (@a r, @a g, @a b)
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre 0<= @a x < ColumnasVentana() && 0<= @a y < FilasVentana()
  */
void Punto(int x, int y, unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Dibuja una línea desde (@a x1,@a y1) a (@a x2,@a y2) de color (@a r, @a g, @a b)
  * @param x1 columna del primer punto
  * @param y1 fila del primer punto
  * @param x2 columna del segundo punto
  * @param y2 fila del segundo punto
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre Los puntos (@a x1,@a y1) (@a x2,@a y2) están dentro de la ventana
  * @pre Los componentes de color están en en rango [0,255]
  */
void Linea(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Dibuja una circunferencia centrada en (@a x,@a y) con radio @a rad de color (@a r, @a g, @a b)
  * @param x columna del punto centro de la circunferencia
  * @param y fila del punto centro de la circunferencia
  * @param rad radio de la circunferencia
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre Los puntos que dibujan la circunferencia están dentro de la ventana
  * @pre Los componentes de color están en en rango [0,255]
  * @see CirculoR
  */
void Circulo(int x, int y, int rad, unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Dibuja un rectángulo definido por las esquinas (@a x1,@a y1) a (@a x2,@a y2) de color (@a r, @a g, @a b)
  * @param x1 columna del primer punto
  * @param y1 fila del primer punto
  * @param x2 columna del segundo punto
  * @param y2 fila del segundo punto
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre Los puntos (@a x1,@a y1) (@a x2,@a y2) están dentro de la ventana
  * @pre Los componentes de color están en en rango [0,255]
  * @see RectanguloR
  */
void Rectangulo(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Dibuja una elipse centrada en (@a x,@a y) con radios @a radx y @rady de color (@a r, @a g, @a b)
  * @param x columna del punto centro de la elipse
  * @param y fila del punto centro de la elipse
  * @param radx radio horizontal de la elipse
  * @param rady radio vertical de la elipse
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre Los puntos que dibujan la elipse están dentro de la ventana
  * @pre Los componentes de color están en en rango [0,255]
  * @see ElipseR
  */
void Elipse(int x, int y, int radx, int rady, unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Dibuja un rectángulo relleno
  * @param x1 columna del primer punto
  * @param y1 fila del primer punto
  * @param x2 columna del segundo punto
  * @param y2 fila del segundo punto
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre Los puntos (@a x1,@a y1) (@a x2,@a y2) están dentro de la ventana
  * @pre Los componentes de color están en en rango [0,255]
  * @see Rectangulo
  */
void RectanguloR(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Dibuja un círculo relleno
  * @param x columna del punto centro de la circunferencia
  * @param y fila del punto centro de la circunferencia
  * @param rad radio de la circunferencia
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre Los puntos que dibujan la circunferencia están dentro de la ventana
  * @pre Los componentes de color están en en rango [0,255]
  * @see Circulo
  */
void CirculoR(int x, int y, int rad, unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Dibuja una elipse rellena
  * @param x columna del punto centro de la elipse
  * @param y fila del punto centro de la elipse
  * @param radx radio horizontal de la elipse
  * @param rady radio vertical de la elipse
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre Los puntos que dibujan la elipse están dentro de la ventana
  * @pre Los componentes de color están en en rango [0,255]
  * @see ElipseR
  */
void ElipseR(int x, int y, int radx, int rady, unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Escribe un texto en la ventana
  * @param x columna donde se sita la esquina superior izquierda del bloque donde se dibuja el texto
  * @param y fila donde se sita la esquina superior izquierda del bloque donde se dibuja el texto
  * @param c texto a escribir
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre Los puntos que dibujan el texto están dentro de la ventana
  * @pre Los componentes de color están en en rango [0,255]
  * @post El texto se dibuja en el rectángulo de alto 8 y ancho longitud(c)*8 y con esquina superior
  izquierda situada en (@a x,@a y)
  */
void Texto(int x, int y, const char *c,  unsigned char r, unsigned char g, unsigned char b);


/**
  * @brief Obtiene el color de un pixel (@a r, @a g, @a b)
  * @param r componente rojo del color
  * @param g componente verde del color
  * @param b componente azul del color
  * @pre Se ha creado una ventana previamente con CrearVentana
  * @pre 0<= @a x < ColumnasVentana() && 0<= @a y < FilasVentana()
  * @post El color del punto  (@a x,@a y) se obtiene en  (@a r, @a g, @a b)
  */
void ObtenerPunto(int x, int y, unsigned char &r, unsigned char &g, unsigned char &b);


/**
  * @brief Cargar desde un fichero en disco una imagen BMP
  * @param fich nombre del archivo con la imagen
  * @return un puntero a la imagen cargada, 0 si no es posible cargarla
  * @post Si ocurre un error, se describe el problema en la salida estándar de error
  * @see LiberarImagenBMP, DimensionesBMP, DibujarImagenBMP
  */
SDL_Surface *LeerImagenBMP(const char *fich);


/**
  * @brief Liberar la memoria ocupada por una imagen BMP
  * @param img puntero a la imagen previamente cargada
  * @pre La imagen ha sido previamente cargada con LeerImagenBMP
  * @see LeerImagenBMP, DimensionesBMP, DibujarImagenBMP
  */
void LiberarImagenBMP(SDL_Surface *img);


/**
  * @brief Obtener las dimensiones (filas y columnas) de una imagen que está almacenada en un fichero
  * @param imagen cadena que contiene el nombre del fichero
  * @param x tamaño en columnas de la imagen
  * @param y tamaño en filas de la imagen
  * @see LeerImagenBMP, DimensionesBMP, DibujarImagenBMP
  */
void DimensionesBMP(const char *imagen, int& x, int& y);


/**
  * @brief Dibuja en la ventana gráfica, a partir de las coordenadas (@a x, @a y), la imagen almacenada en @a img
  * @param img puntero a la imagen
  * @param x coordenada horizontal (columna) a partir de la cual pintar la imagen
  * @param y coordenada vertical (fila) a partir de la cual pintar la imagen
  * @pre La imagen ha sido previamente cargada con LeerImagenBMP
  * @pre La imagen debe caber completa en el área delimitada por la ventana
  * @see LeerImagenBMP, DimensionesBMP, DibujarImagenBMP
  */
void DibujarImagenBMP(SDL_Surface *img, int x, int y);


/**
  * @brief Espera hasta que se pulsa uno de los botones del ratón
  * @param x coordenada horizontal (columna) del ratón en el momento de la pulsación
  * @param y coordenada vertical (fila) del ratón en el momento de la pulsación
  * @return un entero que codifica el botón pulsado (1=izquierdo, 2=central, 3=derecho)
  * @post Las coordenadas del ratón en el momento de la pulsación se obtienen en (@a x, @a y)
  */
int ObtenerClick(int &x, int &y);


/**
  * @brief Espera hasta que se pulsa una tecla
  * @return un entero que codifica la tecla que se ha pulsado
  */
int ObtenerTecla();


/**
  * @brief Espera durante un instante de tiempo
  * @param ms nmero de milisegundos a esperar
  */
void Esperar(int ms);

/* ***************************************** */

#endif

/* ***************************************** */
