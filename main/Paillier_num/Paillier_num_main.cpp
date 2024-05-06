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
	if (argc < 3)
	{
		printf("Usage : [e or ek or dk] [params] \n e p q \n ek public_key.bin \n dk private_key.bin \n");
		return 1;
	}

	bool isEncryption;
	bool useKeys = false;

	if (tolower(argv[1][0]) == 'e')
	{
		isEncryption = true;
		if (tolower(argv[1][1]) == 'k')
		{
			useKeys = true;
		}
	}
	else if (tolower(argv[1][0]) == 'd' && tolower(argv[1][1]) == 'k')
	{
		isEncryption = false;
		useKeys = true;
	}
	else
	{
		fprintf(stderr, "The first argument must be e, ek or dk. (the case don't matter)\n");
		return 1;
	}

	string englishArgNumb = "fourth";
	char *c_key_file;
	if (useKeys)
	{
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
			printf("pgcd(p * q, (p - 1) * (q - 1))= %" PRIu64 "\n", pgc_pq);
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
	uint64_t n, g;
	n = pubk.getN();
	g = pubk.getG();

	std::vector<long uint64_t> vector_r_values = calc_set_same_remainder_divide_euclide(n);

	uint64_t t_x[vector_r_values.size()][256];
	uint64_t t_y[vector_r_values.size()][256];
	uint64_t t_pix_enc[vector_r_values.size()][256];

	for (long unsigned int l = 0; l < vector_r_values.size(); l++)
	{
		printf("r = %" PRIu64 "\n", vector_r_values.at(l));
		for (int i = 0; i < 256; i++)
		{
			unsigned char msg = i;
			uint64_t pixel_enc = paillierEncryption(n, g, msg, vector_r_values.at(l));

			t_pix_enc[l][i] = pixel_enc;
			// printf("pix = %" PRIu64 "\n",pixel_enc);

			uint64_t pixel_enc_dec_x = pixel_enc / n;
			uint64_t pixel_enc_dec_y = pixel_enc % n;
			t_x[l][i] = pixel_enc_dec_x;
			t_y[l][i] = pixel_enc_dec_y;
		}
	}

	FILE *file_pix_enc = NULL;
	file_pix_enc = fopen("results_pix_enc.txt", "w+");

	if (file_pix_enc == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fprintf(file_pix_enc, "%lu \n", vector_r_values.size());
	fprintf(file_pix_enc, "%" PRIu64 "", g);

	for (long unsigned int l = 0; l < vector_r_values.size(); l++)
	{
		for (int i = 0; i < 256; i++)
		{
			fprintf(file_pix_enc, "\n");

			fprintf(file_pix_enc, "%" PRIu64 "", t_pix_enc[l][i]);
		}
	}

	fclose(file_pix_enc);

	FILE *file_t_x = NULL;
	file_t_x = fopen("results_t_x.txt", "w+");

	if (file_t_x == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fprintf(file_t_x, "%lu \n", vector_r_values.size());
	fprintf(file_t_x, "%" PRIu64 "", g);


	for (long unsigned int l = 0; l < vector_r_values.size(); l++)
	{
		for (int i = 0; i < 256; i++)
		{
			fprintf(file_t_x, "\n");

			fprintf(file_t_x, "%" PRIu64 "", t_x[l][i]);
		}
	}

	fclose(file_t_x);

	FILE *file_t_y = NULL;
	file_t_y = fopen("results_t_y.txt", "w+");
	
	if (file_t_y == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fprintf(file_t_y, "%lu \n", vector_r_values.size());
	fprintf(file_t_y, "%" PRIu64 "", g);


	for (long unsigned int l = 0; l < vector_r_values.size(); l++)
	{
		for (int i = 0; i < 256; i++)
		{
			fprintf(file_t_y, "\n");

			fprintf(file_t_y, "%" PRIu64 "", t_y[l][i]);
		}
	}

	fclose(file_t_y);
}