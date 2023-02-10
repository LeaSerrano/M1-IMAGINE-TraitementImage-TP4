#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille*3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille*3);

    OCTET *tabIdR, *tabIdG, *tabIdB, *tabIdR_flou, *tabIdG_flou, *tabIdB_flou;
    
    allocation_tableau(tabIdR, OCTET, nTaille);
    allocation_tableau(tabIdG, OCTET, nTaille);
    allocation_tableau(tabIdB, OCTET, nTaille);
    allocation_tableau(tabIdR_flou, OCTET, nTaille);
    allocation_tableau(tabIdG_flou, OCTET, nTaille);
    allocation_tableau(tabIdB_flou, OCTET, nTaille);

    planR(tabIdR, ImgIn, nTaille);
    planV(tabIdG, ImgIn, nTaille);
    planB(tabIdB, ImgIn, nTaille);

    for (int i = 0; i < nH; i++) {
      for (int j = 0; j < nW; j++) {
      
        tabIdR_flou[i*nW+j] = (tabIdR[(i-1)*nW+(j-1)] + tabIdR[(i-1)*nW+j] + tabIdR[(i-1)*nW+(j+1)] + tabIdR[i*nW+(j-1)] + tabIdR[i*nW+j] + tabIdR[i*nW+(j+1)] + tabIdR[(i+1)*nW+(j-1)] + tabIdR[(i+1)*nW+j] + tabIdR[(i+1)*nW+(j+1)])/9;
        tabIdG_flou[i*nW+j] = (tabIdG[(i-1)*nW+(j-1)] + tabIdG[(i-1)*nW+j] + tabIdG[(i-1)*nW+(j+1)] + tabIdG[i*nW+(j-1)] + tabIdG[i*nW+j] + tabIdG[i*nW+(j+1)] + tabIdG[(i+1)*nW+(j-1)] + tabIdG[(i+1)*nW+j] + tabIdG[(i+1)*nW+(j+1)])/9;
        tabIdB_flou[i*nW+j] = (tabIdB[(i-1)*nW+(j-1)] + tabIdB[(i-1)*nW+j] + tabIdB[(i-1)*nW+(j+1)] + tabIdB[i*nW+(j-1)] + tabIdB[i*nW+j] + tabIdB[i*nW+(j+1)] + tabIdB[(i+1)*nW+(j-1)] + tabIdB[(i+1)*nW+j] + tabIdB[(i+1)*nW+(j+1)])/9;
      } 
    } 

   for (int elt=0; elt < nTaille*3; elt+=3)
    {
      ImgOut[elt] = tabIdR_flou[elt/3];
      ImgOut[elt+1] = tabIdG_flou[elt/3];
      ImgOut[elt+2] = tabIdB_flou[elt/3];
    }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
