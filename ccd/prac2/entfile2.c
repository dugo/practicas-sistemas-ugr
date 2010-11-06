#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "idc.h"
/**********************************************************************
*                                                                      *
*  File: entfile2.c                                                    *
*  Function:  computes first order entropy assuming 65536 letter alphabet.*
*             Note that this is equivalent to computes the second order*
*			  entropy assuming 256 letter alphabet.                    *
*  Author  : K. Sayood & J. Mateos                                    *
*  Last mod:                                                           *
*  Usage:  see usage(), for details see entfile.doc or man page        *
***********************************************************************/

/*******************************************************************************
*NOTICE:                                                                       *
*This code is believed by the author to be bug free.  You are free to use and  *
*modify this code with the understanding that any use, either direct or        *
*derivative, must contain acknowledgement of its author and source.  The author*
*makes no warranty of any kind, expressed or implied, of merchantability or    *
*fitness for a particular purpose.  The author shall not be held liable for any*
*incidental or consequential damages in connection with or arising out of the  *
*furnishing, performance, or use of this software.  This software is not       *
*authorized for use in life support devices or systems.                        *
********************************************************************************/

void usage(void);

#define max 65536

main(int argc, char **argv)
{
  FILE *ifp;
  int i, c, size, hist[max];
  float prob[max], count, entropy;
  int prev;

  if((ifp = fopen(argv[1],"r")) == NULL)
   {
    fprintf(stderr,"Input open failed\n");
    usage();
    exit(1);
   }


/* Compute the histogram  */ 

  for(i=0; i<max; i++)
   hist[i] = 0;

  size = 0;

/*
Nota: Si el número de bytes del fichero es impar,
el ultimo byte no se considera
*/

  while(((prev=getc(ifp))!=EOF)&&((c=getc(ifp))!=EOF))
  {
   hist[prev*256+c]++;
   size++;
  }

  count = (float) (size);

/*  Compute the zero order probability model  */

  for(i=0; i< max; i++)
      prob[i]= (float) hist[i]/ count; 
/*  Compute the entropy  */ 

  entropy = ent(prob,max);
  fprintf(stderr,"Entropy of file is %5.2f\n",entropy);

 }
 
 void usage(void)
{
  fprintf(stderr,"usage:\n \t entfile filename [-l size] [-h]\n");
  fprintf(stderr,"\t\t filename: name of file for which zero order entropy is\n");
  fprintf(stderr,"\t\t\t   to be calculated\n");
  fprintf(stderr,"\t\t size    : Size of file in bytes\n");
}  
