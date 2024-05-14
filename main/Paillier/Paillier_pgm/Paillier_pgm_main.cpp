/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_pgm_main.cpp
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
#include "../../../include/Paillier.hpp"
#include "../../../include/filesystemCommon.h"
#include "../../../include/filesystemPGM.h"
#include "../../../include/Paillier_private_key.hpp"
#include "../../../include/Paillier_public_key.hpp"
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
using namespace std;

/* Vérification d'arguments */

/**
 *  @brief
 *  @details Vérification de l'argument en paramètre, afin de voir si c'est bel et bien un nombre et qu'il est premier.
 *  @param string pos
 * 	@param char *arg
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 */
uint8_t checkNumbersArgument(string pos, char *arg)
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
 *  @details Vérification de l'argument en paramètre, afin de voir si c'est bel et bien un nom de fichier terminant par .pgm.
 *  @param const std::string &str
 * 	@param const std::string &suffix
 *  @authors Katia Auxilien
 *  @date 30/04/2024
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
		uint64_t lambda, n, mu;
		n = p * q;
		uint64_t pgc_pq = gcd_64t(p * q, (p - 1) * (q - 1));

		if (pgc_pq != 1)
		{
			printf("pgcd(p * q, (p - 1) * (q - 1))= %" PRIu64 "\n", pgc_pq);
			fprintf(stderr, "p & q arguments must have a gcd = 1. Please retry with others p and q.\n");
			return 1;
		}
		vector<uint64_t> set = calc_set_same_remainder_divide_euclide_64t(n * n);
		uint64_t g = choose_g_in_vec_64t(set, n, lambda);

		if (g == 0)
		{
			fprintf(stderr, "ERROR with g.\n");
			return 1;
		}

		generatePrivateKey_64t(lambda, mu, p, q, n, g);
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

		int nH, nW, nTaille;
		uint64_t n = pubk.getN();
		uint64_t g = pubk.getG();
		printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
		printf("Pub Key N = %" PRIu64 "\n", pubk.getN());

		OCTET *ImgIn;
		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);

		if (distributeOnTwo)
		{
			uint8_t *ImgOutEnc;
			nTaille = nH * nW;

			allocation_tableau(ImgIn, OCTET, nTaille);
			lire_image_pgm(cNomImgLue, ImgIn, nTaille);
			allocation_tableau(ImgOutEnc, OCTET, nH * (2*nW));
			uint64_t x = 0, y = 1;
			for (int i = 0; i < nTaille; i++)
			{
				uint8_t pixel;
				if (recropPixels)
				{
					pixel = (ImgIn[i] * n) / 256;
				}
				else
				{
					pixel = ImgIn[i];
				}

				uint16_t pixel_enc = paillierEncryption_8t(n, g, pixel);
				uint8_t pixel_enc_dec_x = pixel_enc / n;
				uint8_t pixel_enc_dec_y = pixel_enc % n;
				ImgOutEnc[x] = pixel_enc_dec_x;
				ImgOutEnc[y] = pixel_enc_dec_y;
				x = x + 2;
				y = y + 2;
			}

			ecrire_image_pgm_variable_size_8t(cNomImgEcriteEnc, ImgOutEnc, nH, nW*2, n);

			free(ImgIn);
			free(ImgOutEnc);
		}
		else
		{
			uint16_t *ImgOutEnc;
			nTaille = nH * nW;

			allocation_tableau(ImgIn, OCTET, nTaille);
			lire_image_pgm(cNomImgLue, ImgIn, nTaille);
			allocation_tableau(ImgOutEnc, uint16_t, nTaille);

			for (int i = 0; i < nTaille; i++)
			{
				uint8_t pixel;
				if (recropPixels)
				{

					pixel = (ImgIn[i] * n) / 256;
				}
				else
				{
					pixel = ImgIn[i];
				}

				uint16_t pixel_enc = paillierEncryption_8t(n, g, pixel);

				ImgOutEnc[i] = pixel_enc;
			}

			ecrire_image_pgm_variable_size_16t(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n);

			free(ImgIn);
			free(ImgOutEnc);
			nTaille = nH *nW;
		}

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

		int nH, nW, nTaille;
		uint64_t n, lambda, mu;
		lambda = pk.getLambda();
		mu = pk.getMu();

		OCTET *ImgOutDec;
		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;

		if (distributeOnTwo)
		{
			uint8_t *ImgIn;

			allocation_tableau(ImgIn, uint8_t, nTaille);
			n = lire_image_pgm_and_get_maxgrey_8t(cNomImgLue, ImgIn, nTaille);
			allocation_tableau(ImgOutDec, OCTET, nH*(nW/2));

			int x = 0, y = 1;
			for (int i = 0; i < nH*(nW/2); i++)
			{
				uint16_t pixel;
				uint8_t pixel_enc_dec_x = ImgIn[x];
				uint8_t pixel_enc_dec_y = ImgIn[y];
				pixel = (pixel_enc_dec_x * n) + pixel_enc_dec_y;
				x = x + 2;
				y = y + 2;
				uint8_t c = paillierDecryption_16t(n, lambda, mu, pixel);
				ImgOutDec[i] = static_cast<OCTET>(c);
			}
			ecrire_image_pgm(cNomImgEcriteDec, ImgOutDec, nH, nW/2);
			free(ImgIn);
			free(ImgOutDec);
		}
		else
		{
			uint16_t *ImgIn;
			allocation_tableau(ImgIn, uint16_t, nTaille);
			n = lire_image_pgm_and_get_maxgrey_16t(cNomImgLue, ImgIn, nTaille);
			allocation_tableau(ImgOutDec, OCTET, nTaille);

			for (int i = 0; i < nTaille; i++)
			{	
				uint16_t pixel = ImgIn[i];
				uint8_t c = paillierDecryption_16t(n, lambda, mu, pixel);
				ImgOutDec[i] = static_cast<OCTET>(c);
				
			}
			ecrire_image_pgm(cNomImgEcriteDec, ImgOutDec, nH, nW);
			free(ImgIn);
			free(ImgOutDec);
		}


	}
}