/******************************************************************************
* ICAR_Interns_Library
*
* Fichier : Paillier_main.cpp
*
* Description : Classe contenant des fonctions qui permettent de récupérer des
*    images au format .pgm. 
*   Fichier source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
*
* Auteur : Katia Auxilien
*
* Mail : katia.auxilien@mail.fr
*
* Date : Avril 2024 - Mai 2024
*
*******************************************************************************/
#include "../../include/Paillier.h"
#include "../../include/filesystemCommon.h"
#include "../../include/filesystemPGM.h"
#include <cctype>
#include <fstream>
#include <string>
#include <string_view> 
using namespace std;

uint64_t checkNumbersArgument(string pos, char * arg){
	for(size_t i = 0; i < strlen(arg) ; i++){
		if(!isdigit(arg[i])){
			fprintf(stderr, "The %s argument must be an int.\n", pos.c_str());
			return 1;
		}
	}
	int p = atoi(arg);
	if(!isPrime(p,2)){
		fprintf(stderr, "The %s argument must be a prime number.\n",pos.c_str());
		return 1;
	}

	return p;
}

bool endsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int main(int argc, char **argv)
{

    if (argc != 5)
    {
        printf("Usage : [e or d] p q file.pgm\n");
        return 1;
    }

	bool isEncryption;
	if(tolower(argv[1][0]) == 'e'){
		isEncryption = true;
	}else if (tolower(argv[1][0]) == 'd'){
		isEncryption = false;
	}else{
        fprintf(stderr, "The first argument must be e or d. (the case don't matter)\n");
        return 1;
	}

// 	//23x11 ne marche pas car 22x10=11*20
// 	uint64_t p = 13;//23;//19;  
// 	uint64_t q = 19;//11;//17; 
	uint64_t p = checkNumbersArgument("second",argv[2]);
	if(p == 1){
		return 1;
	}
	uint64_t q = checkNumbersArgument("third",argv[3]);
	if(q == 1){
		return 1;
	}

	uint64_t n = p * q;
	vector<int> e =  calc_set_same_remainder_divide_euclide(n); 
	int i_position_e = rand() % e.size();
	uint64_t g = e.at(i_position_e);
	// uint64_t g = rand() % (uint64_t)pow(n, 2);
	uint64_t lambda, mu;
	generatePrivateKey(lambda, mu, p, q, n, g);

	// Private key (lambda;mu)
	// Public key (n;g)

	char* c_file = argv[4];
	string s_file = c_file;
	ifstream file(c_file);
    if (!file || !endsWith(s_file, ".pgm")) {
        cerr << "The fourth argument must be an existing .pgm file." << endl;
        return 1;
    }


	/*******Encryption*******/
	if (isEncryption) {
		char cNomImgLue[250];
		strcpy(cNomImgLue,s_file.c_str());

		string toErase = ".pgm";
		size_t pos = s_file.find(".pgm");
		s_file.erase(pos,toErase.length());
		string s_fileNew = s_file + "_E.pgm";
		char cNomImgEcriteEnc[250];
		strcpy(cNomImgEcriteEnc,s_fileNew.c_str());

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

		// ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n * n);
		ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW * 2, 255);

		free(ImgIn); free(ImgOutEnc); 
	}
	
// 	/*******Decryption*******/
// 	else {
// 		char cNomImgLue[250] = "24E.pgm";
// 		char cNomImgEcriteDec[250] = "24ED.pgm";
// 		int nH, nW, nTaille;

// 		uint64_t* ImgIn;
// 		OCTET* ImgOutDec;

// 		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
// 		nTaille = nH * nW;

// 		allocation_tableau(ImgIn, uint64_t, nTaille);
// 		lire_image_pgm_variable_size(cNomImgLue, ImgIn, nH * nW);
// 		allocation_tableau(ImgOutDec, OCTET, nTaille);

// 		for (int i = 0; i < nTaille; i++) {
// 			uint64_t e = ImgIn[i];
// 			uint64_t c = paillierDecryption(n, lambda, mu, ImgIn[i]);
// 			ImgOutDec[i] = static_cast<OCTET>(c);
// 		}

// 		ecrire_image_pgm(cNomImgEcriteDec, ImgOutDec, nH, nW);
// 		free(ImgIn); free(ImgOutDec);
// 	}

}