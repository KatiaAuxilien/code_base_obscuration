// AES_OFB.cpp : Chiffre une image par OFB

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
    unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

    // unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    // unsigned char iv[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    if (K == 0)
        ImgOut = aes.EncryptCTR(ImgIn, nTaille, key, iv);
    else {
        if (K == 1)
            ImgOut = aes.DecryptCTR(ImgIn, nTaille, key, iv);
        else
            printf("K incorrect !");
    }


    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    return 1;
}
