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
#include "../../include/Paillier_private_key.hpp"
#include "../../include/Paillier_public_key.hpp"
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
using namespace std;

uint64_t checkNumbersArgument(string pos, char *arg)
{
	for (size_t i = 0; i < strlen(arg); i++)
	{
		if (!isdigit(arg[i]))
		{
			fprintf(stderr, "The %s argument must be an int.\n", pos.c_str());
			return 1;
		}
	}
	int p = atoi(arg);
	if (!isPrime(p, 2))
	{
		fprintf(stderr, "The %s argument must be a prime number.\n", pos.c_str());
		return 1;
	}

	return p;
}

bool endsWith(const std::string &str, const std::string &suffix)
{
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
	if (tolower(argv[1][0]) == 'e')
	{
		isEncryption = true;
	}
	else if (tolower(argv[1][0]) == 'd')
	{
		isEncryption = false;
	}
	else
	{
		fprintf(stderr, "The first argument must be e or d. (the case don't matter)\n");
		return 1;
	}

	uint64_t p = checkNumbersArgument("second", argv[2]);
	if (p == 1)
	{
		return 1;
	}
	uint64_t q = checkNumbersArgument("third", argv[3]);
	if (q == 1)
	{
		return 1;
	}

	uint64_t n = p * q;
	uint64_t pgc_pq = gcd(p * q, (p - 1) * (q - 1));

	if (pgc_pq != 1)
	{
		fprintf(stderr, "p & q arguments must have a gcd = 1. Please retry with others p and q.\n");
		return 1;
	}

	char *c_file = argv[4];
	string s_file = c_file;
	ifstream file(c_file);
	if (!file || !endsWith(s_file, ".pgm"))
	{
		cerr << "The fourth argument must be an existing .pgm file." << endl;
		return 1;
	}

	vector<long uint64_t> set = calc_set_same_remainder_divide_euclide(n);
	
	uint64_t lambda, mu;

	uint64_t g = choose_g_in_vec(set, n,lambda);

	generatePrivateKey(lambda, mu, p, q, n, g);
	PaillierPrivateKey pk = new PaillierPrivateKey(lambda,mu);
	PaillierPublicKey pubk = new PaillierPublicKey(n,g);

	/*******Encryption*******/
	if (isEncryption)
	{
		char cNomImgLue[250];
		strcpy(cNomImgLue, s_file.c_str());

		string toErase = ".pgm";
		size_t pos = s_file.find(".pgm");
		s_file.erase(pos, toErase.length());
		string s_fileNew = s_file + "_E.pgm";
		char cNomImgEcriteEnc[250];
		strcpy(cNomImgEcriteEnc, s_fileNew.c_str());

		int nH, nW, nTaille;

		OCTET *ImgIn;
		uint64_t *ImgOutEnc;

		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		lire_image_pgm(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, uint64_t, nH * (nW * 2));

		int x=0,y=1;
		for (int i = 0; i < nTaille; i++)
		{
			uint64_t pixel_recrop = (ImgIn[i]/255) % n;

			uint64_t pixel_enc = paillierEncryption(n, g, pixel_recrop);

			uint64_t pixel_enc_dec_x = pixel_enc/n;
			uint64_t pixel_enc_dec_y = pixel_enc%n;
			ImgOutEnc[x] = pixel_enc_dec_x;
			ImgOutEnc[y] = pixel_enc_dec_y;
			x=x+2;
			y=y+2;
		}

		ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW * 2, 255);

		free(ImgIn);
		free(ImgOutEnc);
	}
	/*******Decryption*******/
	else {
		char cNomImgLue[250];
		strcpy(cNomImgLue, s_file.c_str());

		string toErase = ".pgm";
		size_t pos = s_file.find(".pgm");
		s_file.erase(pos, toErase.length());
		string s_fileNew = s_file + "_D.pgm";
		char cNomImgEcriteDec[250];
		strcpy(cNomImgEcriteDec, s_fileNew.c_str());

		int nH, nW, nTaille;

		OCTET *ImgIn;
		uint64_t *ImgOutDec;

		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		lire_image_pgm(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutDec, uint64_t, nH * (nW / 2));

		int x=0,y=1;
		for (int i = 0; i < nTaille; i++)
		{
			uint64_t pixel_enc_dec_x = ImgOutDec[x];
			uint64_t pixel_enc_dec_y = ImgOutDec[y];
			uint64_t cipher = pixel_enc_dec_x * n + pixel_enc_dec_y;
			
			ImgIn[i] = paillierDecryption(n,lambda,mu,cipher);
			
			x=x+2;
			y=y+2;
		}

		ecrire_image_pgm_variable_size(cNomImgEcriteDec, ImgOutDec, nH, nW / 2, 255);

		free(ImgIn);
		free(ImgOutDec);
		
	}
}