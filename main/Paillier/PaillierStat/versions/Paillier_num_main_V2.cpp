/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : Paillier_main.cpp
 *
 * Description :
 *   File source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
 *
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024 - Mai 2024
 *
 *******************************************************************************/
#include "../../include/Paillier.hpp"
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
 *  @date 30 April 2024
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
 *  @date 30 April 2024
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
		printf("Usage : [e or ek or dk]\n");
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
		fprintf(stderr, "The first argument must be e, ek or dk. (the case don't matter)\n");
		return 1;
	}

	/*======================== Generate keys ========================*/

	PaillierPrivateKey pk;
	PaillierPublicKey pubk;

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

	vector<long uint64_t> vector_g = calc_set_same_remainder_divide_euclide(n * n);

	uint64_t g = 0;

	std::vector<long uint64_t> vector_r_values = calc_set_same_remainder_divide_euclide(n);
	size_t size_vec_r = vector_r_values.size();

	int count_y[size_vec_r], count_x[size_vec_r];
	int count_enc_pix[size_vec_r];

	for(size_t u = 0; u< size_vec_r;u++){
		count_x[u] = 0;
		count_y[u] = 0;
		count_enc_pix[u]=0;
	}

	vector<long uint64_t> vector_g_good;

	uint64_t vector_size_g;
	if(vector_g.size() >= 1000)
	{
		vector_size_g = vector_g.size();
	}else{
		vector_size_g = 1000;
	}

	for (size_t i_position = 0; i_position < vector_size_g;i_position ++)
	{

		uint64_t x;
		uint64_t r = 1, r2 = 1;
		while (r != 0 && r2 != 0)
		{			
			g = vector_g.at(i_position);
			x = fastMod(g, lambda, n * n);
			r = (x - 1) % n;
			r2 = (x - 1) / n;
			i_position++;
		}
		vector_g_good.push_back(g);

		if (g == 0)
		{
			fprintf(stderr, "ERROR with g.\n");
			return 1;
		}

		generatePrivateKey(lambda, mu, p, q, n, g);
		pk = PaillierPrivateKey(lambda, mu);
		pubk = PaillierPublicKey(n, g);

		/*======================== Encryption ========================*/
		// printf("Pub Key G = %" PRIu64 "\n", pubk.getG());


		for (size_t l = 0; l < size_vec_r; l++)
		{

			for (int i = 0; i < 256; i++)
			{
				unsigned char msg = i;
				uint64_t pixel_enc = paillierEncryption(n, g, msg, vector_r_values.at(l));
				uint64_t pixel_enc_dec_x = pixel_enc / n;
				uint64_t pixel_enc_dec_y = pixel_enc % n;

				if (pixel_enc % 2 == 0)
				{
					count_enc_pix[l]++;
				}
				if (pixel_enc_dec_x % 2 == 0)
				{
					count_x[l]++;
				}
				if (pixel_enc_dec_y % 2 == 0)
				{
					count_y[l]++;
				}
			}
		}
	}

		// float x_sum = 0;
		// float x_sum_sqr = 0;

		// float y_sum = 0;
		// float y_sum_sqr = 0;

		// float pix_sum = 0;
		// float pix_sum_sqr = 0;

	int nbElements = 256*vector_size_g;
	double t_x_avg[size_vec_r];
	double t_y_avg[size_vec_r];
	double t_pix_enc_avg[size_vec_r];


	// float ecart_type_x[size_vec_r];
	// float ecart_type_y[size_vec_r];
	// float ecart_type_pix[size_vec_r];

	for (size_t l = 0; l < size_vec_r; l++)
	{
		t_x_avg[l] = count_x[l] / (double) nbElements;
		t_y_avg[l] = count_y[l] / (double) nbElements;
		t_pix_enc_avg[l] = count_enc_pix[l] / (double) nbElements;

		// double variance_x = (x_sum_sqr/(double)size_vec_r)-((x_sum*x_sum)/(double)size_vec_r);
		// double variance_y = (y_sum_sqr/(double)size_vec_r)-((y_sum*y_sum)/(double)size_vec_r);
		// double variance_pix = (pix_sum_sqr/(double)size_vec_r) - ((pix_sum*pix_sum)/(double)size_vec_r);

		// ecart_type_x[l] = sqrt(variance_x);
		// ecart_type_y[l] = sqrt(variance_y);
		// ecart_type_pix[l] = sqrt(variance_pix);
	}
	
	
	/////////////////////////////// Enregistrement des résultats : Pix_enc.

	FILE *file_enc_pix = NULL;
	file_enc_pix = fopen("results_pix_g.txt", "w+");

	if (file_enc_pix == NULL)
	{
		printf("Error!");
		exit(1);
	}

	for (size_t l = 0; l < size_vec_r; l++)
	{
		fprintf(file_enc_pix, "%" PRIu64 "", vector_r_values.at(l));
		fprintf(file_enc_pix, "\n");
		fprintf(file_enc_pix, "%lf", t_pix_enc_avg[l]);
		fprintf(file_enc_pix, "\n");
	}

	fclose(file_enc_pix);


	/////////////////////////////// Enregistrement des résultats : x

	FILE *file_x = NULL;
	file_x = fopen("results_x_g.txt", "w+");

	if (file_x == NULL)
	{
		printf("Error!");
		exit(1);
	}

	for (size_t l = 0; l < size_vec_r; l++)
	{
		fprintf(file_x, "%" PRIu64 "", vector_r_values.at(l));
		fprintf(file_x, "\n");
		fprintf(file_x, "%lf", t_x_avg[l]);
		fprintf(file_x, "\n");
	}

	fclose(file_x);

	/////////////////////////////// Enregistrement des résultats : y

	FILE *file_y = NULL;
	file_y = fopen("results_y_g.txt", "w+");

	if (file_y == NULL)
	{
		printf("Error!");
		exit(1);
	}

	for (size_t l = 0; l < size_vec_r; l++)
	{
		fprintf(file_y, "%" PRIu64 "", vector_r_values.at(l));
		fprintf(file_y, "\n");
		fprintf(file_y, "%lf", t_y_avg[l]);
		fprintf(file_y, "\n");
	}

	fclose(file_y);

}