/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_num_main_V3.cpp
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
#include "../../../include/encryption/Paillier/Paillier.hpp"
#include "../../../include/encryption/Paillier/keys/Paillier_private_key.hpp"
#include "../../../include/encryption/Paillier/keys/Paillier_public_key.hpp"
#include "../../../include/filesystem/filesystemCommon.h"
#include "../../../include/filesystem/filesystemPGM.h"
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
using namespace std;

/**
 *  @brief Vérifier si n est un nombre premier.
 *  @details
 *  @param int n 
 *  @param int i
 *  @authors Katia Auxilien
 *  @date 30/04/2024 
 */
bool isPrime(int n, int i = 2)
{
	if (n <= 2)
		return (n == 2) ? true : false;
	if (n % i == 0)
		return false;
	if (i * i > n)
		return true;

	return isPrime(n, i + 1);
}

/**
 *  @brief
 *  @details Vérification de l'argument en paramètre, afin de voir si c'est bel et bien un nombre et qu'il est premier.
 *  @param string pos
 * 	@param char *arg
 *  @authors Katia Auxilien
 *  @date 30/04/2024
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
	Paillier paillier;
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

		vector<uint64_t> set = paillier.calc_set_same_remainder_divide_euclide_64t(n * n);
		uint64_t g = paillier.choose_g_in_vec_64t(set, n, lambda);
		if (g == 0)
		{
			fprintf(stderr, "ERROR with g.\n");
			return 1;
		}

		paillier.generatePrivateKey_64t(lambda, mu, p, q, n, g);
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

	printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
	printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
	std::vector<uint64_t> vector_r_values = paillier.calc_set_same_remainder_divide_euclide_64t(n);

	size_t size_vec_r = vector_r_values.size();
	printf(" vect r : %ld", size_vec_r);
	uint16_t t_pix_enc[size_vec_r][n];

	for (size_t l = 0; l < size_vec_r ; l++)
	{
		for (uint64_t i = 0; i < n; i++)
		{
			unsigned char msg = i;
			uint16_t pixel_enc = paillier.paillierEncryption_8tr(n, g, msg, vector_r_values.at(l));
			t_pix_enc[l][i] = pixel_enc;
		}
	}

	FILE *file_enc_pix = NULL;
	file_enc_pix = fopen("results_pix.txt", "w+");

	if (file_enc_pix == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fprintf(file_enc_pix, "%" PRIu64 "", n);
	fprintf(file_enc_pix, "\n");
	fprintf(file_enc_pix, "%ld", size_vec_r);

	for (size_t l = 0; l < size_vec_r; l++)
	{
		fprintf(file_enc_pix, "\n");
		fprintf(file_enc_pix, "%" PRIu64 "", vector_r_values.at(l));
		for (uint64_t i = 0; i < n; i++)
		{
			fprintf(file_enc_pix, "\n");
			fprintf(file_enc_pix, "%" PRIu16 "", t_pix_enc[l][i]);
		}
	}

	fclose(file_enc_pix);

}