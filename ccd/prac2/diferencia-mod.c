/*
Uso: diferencia fich_entrada fich_salida

diferencia lee el fichero de entrada fich_entrada y a cada uno de los datos 
le resta el dato anterior guardando el resultado en el fichero fich_salida.

Se supone que el fichero de entrada está almacenado con un byte por dato.

IMPORTANTE: El fichero de salida tiene dos bytes por dato dado que las 
diferencias pueden estar en el intervalo [-255, 255] y, por tanto, necesitamos 
al menos 9 bits para representarlas. 
Para evitar problemas con la representación se suma 256 a las diferencias 
obteniendo así un valor positivo en el intervalo [1, 511], que será el valor 
de salida del modelo. Dicho valor se almacena en el fichero usando dos bytes,
siendo el byte más significativo el primero.

El primer dato del fichero de salida es igual al primer dato del fichero de
entrada (aunque almacenado en dos bytes).

Si el fichero de entrada es una imagen PGM, el fichero de salida será tambien 
una imagen PGM.

Autor: Javier Mateos
*/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

   FILE *fin, *fout;
   int actual, anterior;
   unsigned short diferencia;
   int ancho, alto, maxval;
   char linea[72];

   if(argc!=3){
      fprintf(stderr,"Use: %s fich_entrada fich_salida\n", argv[0]);
      exit(1);
   }

   if((fin = fopen(argv[1], "rb")) == NULL){
	  fprintf(stderr,"Error abriendo el fichero de entrada\n");
	  exit(1);
   }

   if((fout = fopen(argv[2], "wb")) == NULL){
	  fprintf(stderr,"Error abriendo el fichero de salida\n");
	  exit(1);
   }

   // Comprobar si el fichero de entrada es PGM (el magic number debe ser P5)
   actual=getc(fin); 
   if (actual == 'P'){
      actual=getc(fin); 
      if (actual != '5'){ //no es PGM
         ungetc(actual,fin); //devolver el 5 y poner actual al primer byte ('P')
         actual = 'P';
      } else { //Tenemos un PGM, leer los datos
         fgets(linea, 71, fin);  //leemos hasta el final de línea
         do{
            fgets(linea, 71, fin);  //leemos la siguiente línea 
         }while (linea[0]=='#'); // eliminando los comentarios
         sscanf(linea,"%d %d", &ancho, &alto); 
         fgets(linea, 71, fin);  //leemos la siguiente línea 
         sscanf(linea, "%d", &maxval);
         actual=getc(fin); // leemos el primer valor de los datos

         // Escribir la cabecera del fichero de salida
         fprintf(fout, "P5\n");
         fprintf(fout, "%d %d\n", ancho, alto);
         fprintf(fout, "%d\n", 255);
      }
   }
   
   /*
   Al llegar aqui actual contiene el primer valor de los datos. 
   Si es un PGM será el primer pixel, si no, será el primer dato del fichero
   */ 
   
   anterior = 0; // El primer valor lo tomamos como cero
   while(actual != EOF){
	  diferencia= (actual-anterior+256)%256;
	  fputc(diferencia, fout);
	  anterior=actual; 
	  actual=getc(fin);
   }

   fclose(fin);
   fclose(fout);
}
