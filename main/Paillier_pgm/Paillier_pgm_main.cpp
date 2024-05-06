/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_main.cpp
 *
 * Description :
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

/**
 *  @brief
 *  @param string pos
 * 	@param char *arg
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 *
 *  Vérification de l'argument en paramètre, afin de voir si
 * 	c'est bel et bien un nombre et qu'il est premier.
 *
 *  @details
 */
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

/**
 *  @brief
 *  @param const std::string &str
 * 	@param const std::string &suffix
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 *
 *  Vérification de l'argument en paramètre, afin de voir si c'est bel et bien
 * 	un nom de fichier terminant par .pgm.
 *
 *  @details
 */
bool endsWith(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		   str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int main(int argc, char **argv)
{
	/*======================== Check arguments ========================*/
	if (argc < 4)
	{
		printf("Usage : [e or ek or dk] [params] image_file.pgm\n e p q file.pgm\n ek public_key.bin image_file.pgm\n dk private_key.bin image_file_encrypted.pgm\n");
		return 1;
	}

	bool isEncryption;
	bool useKeys = false;
	bool distributeOnTwo = false;
	bool recropPixels = false;

	if (tolower(argv[1][0]) == 'e')
	{
		isEncryption = true;
		if (tolower(argv[1][1]) == 'k')
		{
			useKeys = true;
		}
		if (tolower(argv[1][1]) == 'r' || argv[1][2] == 'r' || argv[1][3] == 'r')
			{
				recropPixels = true;
			}
	}
	else if (tolower(argv[1][0]) == 'd' && tolower(argv[1][1]) == 'k')
	{
		isEncryption = false;
		useKeys = true;
	}
	else
	{
		fprintf(stderr, "The first argument must be e, ek or dk, e2, ek2 or dk2. (the case don't matter)\n");
		return 1;
	}

	if (tolower(argv[1][1]) == '2' || argv[1][2] == '2')
		{
			distributeOnTwo = true;
		}

	int argImg = 4;
	string englishArgNumb = "fourth";
	char *c_key_file;
	if (useKeys)
	{
		argImg = 3;
		englishArgNumb = "third";

		c_key_file = argv[2];
		string s_key_file = c_key_file;
		ifstream file(c_key_file);
		if (!file || !endsWith(s_key_file, ".bin"))
		{
			cerr << "The second argument must be an existing .bin file." << endl;
			return 1;
		}
	}
	char *c_file = argv[argImg];
	string s_file = c_file;
	ifstream file(c_file);
	if (!file || !endsWith(s_file, ".pgm"))
	{
		cerr << "The " + englishArgNumb + " argument must be an existing .pgm file." << endl;
		return 1;
	}

	/*======================== Generate keys ========================*/

	PaillierPrivateKey pk;
	PaillierPublicKey pubk;

	if (!useKeys && isEncryption)
	{
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
		uint64_t n, lambda, mu;

		n = p * q;
		uint64_t pgc_pq = gcd(p * q, (p - 1) * (q - 1));

		if (pgc_pq != 1)
		{
			fprintf(stderr, "p & q arguments must have a gcd = 1. Please retry with others p and q.\n");
			return 1;
		}

		vector<long uint64_t> set = calc_set_same_remainder_divide_euclide(n * n);
		uint64_t g = choose_g_in_vec(set, n, lambda);
		// uint64_t g = n+1;
		if (g == 0)
		{
			fprintf(stderr, "ERROR with g.\n");
			return 1;
		}

		generatePrivateKey(lambda, mu, p, q, n, g);
		pk = PaillierPrivateKey(lambda, mu);
		pubk = PaillierPublicKey(n, g);

		FILE *f_private_key = NULL;

		f_private_key = fopen("Paillier_private_key.bin", "w+b");

		if (f_private_key == NULL)
		{
			fprintf(stderr, "Error ! Opening Paillier_private_key.bin\n");
			return 1;
		}

		fwrite(&pk, sizeof(PaillierPrivateKey), 1, f_private_key);

		fclose(f_private_key);

		FILE *f_public_key = NULL;
		f_public_key = fopen("Paillier_public_key.bin", "w+b");

		if (f_public_key == NULL)
		{
			fprintf(stderr, "Error ! Opening Paillier_public_key.bin\n");
			return 1;
		}
		fwrite(&pubk, sizeof(PaillierPublicKey), 1, f_public_key);

		fclose(f_public_key);

		printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
		printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
		printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
		printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
	}
	else
	{
		if (!isEncryption)
		{
			size_t size;
			FILE *f_private_key = NULL;

			f_private_key = fopen(c_key_file, "rb");

			if (f_private_key == NULL)
			{
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				return 1;
			}

			size = sizeof(PaillierPrivateKey);
			fread(&pk, size, 1, f_private_key);
			// if (result != size) {fputs ("Reading error",stderr); return 1;}

			fclose(f_private_key);
		}
		if (isEncryption)
		{
			size_t size;
			FILE *f_public_key = NULL;
			f_public_key = fopen(c_key_file, "rb");

			if (f_public_key == NULL)
			{
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				return 1;
			}
			size = sizeof(PaillierPublicKey);
			fread(&pubk, size, 1, f_public_key);
			// if (result != size) {fputs ("Reading error",stderr); return 1;}

			fclose(f_public_key);
		}
	}

	/*======================== Encryption ========================*/
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

		int nH, nW, nTaille, nTailleOut, nWOut;

		OCTET *ImgIn;
		uint64_t *ImgOutEnc;

		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;
		if (distributeOnTwo)
		{
			nWOut = nW * 2;
		}
		else
		{
			nWOut = nW;
		}

		nTailleOut = nH * nWOut;

		uint64_t n, g;
		n = pubk.getN();
		g = pubk.getG();

		allocation_tableau(ImgIn, OCTET, nTaille);
		lire_image_pgm(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, uint64_t, nTailleOut);
		int x = 0, y = 1;
		for (int i = 0; i < nTaille; i++)
		{
			uint64_t pixel;
			if(recropPixels){
				pixel = (ImgIn[i] * n) / 255;
			}else{
				pixel = ImgIn[i];
			}

			uint64_t pixel_enc = paillierEncryption(n, g,pixel);

			if(distributeOnTwo){
				uint64_t pixel_enc_dec_x = pixel_enc / n;
				uint64_t pixel_enc_dec_y = pixel_enc % n;
				ImgOutEnc[x] = pixel_enc_dec_x;
				ImgOutEnc[y] = pixel_enc_dec_y;
				x = x + 2;
				y = y + 2;
			}else{
				ImgOutEnc[i] = pixel_enc;
			}

		}

		ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nWOut, n);

		free(ImgIn);
		free(ImgOutEnc);
	}
	/*======================== Decryption ========================*/
	else
	{
		char cNomImgLue[250];
		strcpy(cNomImgLue, s_file.c_str());

		string toErase = ".pgm";
		size_t pos = s_file.find(".pgm");
		s_file.erase(pos, toErase.length());
		string s_fileNew = s_file + "_D.pgm";
		char cNomImgEcriteDec[250];
		strcpy(cNomImgEcriteDec, s_fileNew.c_str());

		int nH, nW, nTaille, nTailleOut, nWOut;
		uint64_t n, lambda, mu;
		uint64_t *ImgIn;
		OCTET *ImgOutDec;

		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;

		if (distributeOnTwo)
		{
			nWOut = nW /2;
		}
		else
		{
			nWOut = nW;
		}

		nTailleOut = nH * nWOut;

		allocation_tableau(ImgIn, uint64_t, nTaille);
		n = lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutDec, OCTET, nTailleOut);

		lambda = pk.getLambda();
		mu = pk.getMu();
		printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
		printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());

		int x = 0, y = 1;
		for (int i = 0; i < nTailleOut; i++)
		{
			uint64_t pixel;
			if(distributeOnTwo){
				uint64_t pixel_enc_dec_x = ImgIn[x];
				uint64_t pixel_enc_dec_y = ImgIn[y];
				pixel = (pixel_enc_dec_x * n) + pixel_enc_dec_y;
				x = x + 2;
				y = y + 2;
			}else{
				pixel = ImgIn[i];
			}
			uint64_t c = paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}

		ecrire_image_pgm(cNomImgEcriteDec, ImgOutDec, nH, nWOut);
		free(ImgIn);
		free(ImgOutDec);
	}
}