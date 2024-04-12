// chieff_AES.cpp : Chiffre une image par AES

#include <stdio.h>
#include "image_ppm.h"
#include "AES.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int K;
    int nH, nW, nTaille;
    
    if (argc != 4) {
        printf("Usage: ImageIn.pgm ImageOut.pgm Chiffrement(0)/Dechiffrement(1)\n"); 
        exit(1);
    }
    
    sscanf (argv[1], "%s", cNomImgLue) ;
    sscanf (argv[2], "%s", cNomImgEcrite);
    sscanf (argv[3], "%d", &K);

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    
    AES aes(AESKeyLength::AES_128);

    unsigned char key[] = { 0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b };

    if (K == 0)
        ImgOut = aes.EncryptECB(ImgIn, nTaille, key);
    else {
        if (K == 1)
            ImgOut = aes.DecryptECB(ImgIn, nTaille, key);
        else
            printf("K incorrect !");
    }


    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    return 1;
}
