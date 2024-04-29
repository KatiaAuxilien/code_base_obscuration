// g++ -c image.cpp
// g++ -c Paillier_Image_v2.cpp
// g++ image.o Paillier_Image_v2.o -o Paillier

#include <iostream>
#include <bitset>
#include <vector>
#include "../../include/Paillier.h"
#include "../../include/image.h"
#include "../../include/image_pgm.h"

using namespace std;

int main()
{
	bool isEncryption = false;
	//bool isEncryption = true;
	
	//23x11 ne marche pas car 22x10=11*20
	uint64_t p = 13;//23;//19; 
	uint64_t q = 19;//11;//17; 
	uint64_t n = p * q;
	uint64_t g = n + 1;
	// uint64_t g = rand() % (uint64_t)pow(n, 2);

	uint64_t lambda, mu;

	generatePrivateKey(lambda, mu, p, q, n, g);

	/*******Encryption*******/
	if (isEncryption) {
//		char cNomImgLue[250] = "C:\\Users\\Bianca\\Documents\\Paillier_Image\\01_Lena.pgm";
		char cNomImgLue[250] = "24.pgm";
		char cNomImgEcriteEnc[250] = "24E.pgm";
		int nH, nW, nTaille;

		OCTET* ImgIn, * ImgOutDec;
		uint64_t* ImgOutEnc;

		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
		allocation_tableau(ImgOutEnc, uint64_t, nTaille);

		for (int i = 0; i < nTaille; i++) {
			uint64_t c = paillierEncryption(n, g, ImgIn[i]);
			ImgOutEnc[i] = c;
		}

		ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n * n);
		free(ImgIn); free(ImgOutEnc); 
	}
	
	/*******Decryption*******/
	else {
		char cNomImgLue[250] = "24E.pgm";
		char cNomImgEcriteDec[250] = "24ED.pgm";
		int nH, nW, nTaille;

		uint64_t* ImgIn;
		OCTET* ImgOutDec;

		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;

		allocation_tableau(ImgIn, uint64_t, nTaille);
		lire_image_pgm_variable_size(cNomImgLue, ImgIn, nH * nW);
		allocation_tableau(ImgOutDec, OCTET, nTaille);

		for (int i = 0; i < nTaille; i++) {
			uint64_t e = ImgIn[i];
			uint64_t c = paillierDecryption(n, lambda, mu, ImgIn[i]);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}

		ecrire_image_pgm(cNomImgEcriteDec, ImgOutDec, nH, nW);
		free(ImgIn); free(ImgOutDec);
	}
	
}