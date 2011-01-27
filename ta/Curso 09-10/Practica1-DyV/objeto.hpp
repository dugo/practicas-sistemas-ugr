typedef struct {
   int grosor;
} tornillo;
typedef struct {
   int anchura;
} tuerca;
int compara (tornillo tor, tuerca tuer)
{
   if (tor.grosor == tuer.anchura)
      return 0;
   else
      if (tor.grosor > tuer.anchura)
          return 1;
      else
          return -1;
}
