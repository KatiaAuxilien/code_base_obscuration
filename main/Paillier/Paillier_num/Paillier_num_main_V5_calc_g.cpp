/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_num_main_V5_calc_r.cpp
 *
 * Description : Essais sur la taille d'un chiffré dont n > 255
 *   Fichier source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024 - Mai 2024
 *
 *******************************************************************************/

#include "../../../include/model/filesystem/filesystemCommon.h" //Navigation dans le système de fichier
#include "../../../include/model/filesystem/filesystemPGM.h"

#include <iostream>
#include <set>
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <ctype.h>
#include <errno.h> /* errno */ //TODO : Gestion des erreurs + propre.
#include <signal.h>

using namespace std;

int main(int argc, char **argv)
{
	/*********************** Traitement d'arguments ***********************/

	if (argc < 2)
	{
		printf("Usage : p q\n-k public_key.bin\n");
		return 1;
	}

	bool parameters[2];
	uint64_t lambda, n, mu, g, p, q;

	convertToLower(argv, argc);
	checkParameters(argv, argc, parameters, p, q, n, lambda);

	bool distributeOnTwo = parameters[0];
	bool optimisationLSB = parameters[1];

	/********************************************************************/

	/*********************** Traitement de clé ***********************/

	PaillierPrivateKey pk;
	PaillierPublicKey pubk;

	Paillier<uint64_t, uint64_t> paillier;
	mu = 0;
	std::vector<uint64_t> set_ZN2ZStar = paillier.get_set_ZN2ZStar(n, lambda);

	for (size_t g = 0; g < set_ZN2ZStar.size(); g++)
	{

		paillier.generatePrivateKey_64t(lambda, mu, p, q, n, g);

		if (mu == 0)
		{
			cmd_colorError();
			fprintf(stderr, "ERROR with g, no value found for g where mu exist.\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}

		pk = PaillierPrivateKey(lambda, mu, n);
		pubk = PaillierPublicKey(n, g);
		if (lambda == 0 || mu == 0 || p == 0 || q == 0 || n == 0 || g == 0)
		{
			cmd_colorError();
			fprintf(stderr, "Error in generation of private key.\n");
			printf("p = %" PRIu64 "\n", p);
			printf("q = %" PRIu64 "\n", q);
			printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
			printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
			printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
			printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}

		/*********************** Instanciations de Paillier en fonction de n ***********************/

		/*********************** Chiffrement ***********************/
		if (n <= 256)
		{
			Paillier<uint8_t, uint16_t> paillier;
			uint64_t n = pubk.getN();
			uint64_t g = pubk.getG();
			std::vector<uint64_t> set_ZNZStar = paillier.get_set_ZNZStar(n);

			size_t size_vec_r = set_ZNZStar.size();

			uint16_t t_pix_enc[size_vec_r][n];

			for (size_t l = 0; l < size_vec_r; l++)
			{
				for (uint64_t i = 0; i < n; i++)
				{

					unsigned char msg = i;
					uint16_t pixel_enc = paillier.paillierEncryption(n, g, msg, set_ZNZStar.at(l));
					t_pix_enc[l][i] = pixel_enc;
					if (i == 0)
					{
						fprintf(stdout, "Enc (0) : %" PRIu16 "\n", pixel_enc);
					}
				}
			}
		}

		/*======================== Enregistrement fichier ========================*/
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
			fprintf(file_enc_pix, "%" PRIu64 "", set_ZNZStar.at(l));
			for (uint64_t i = 0; i < n; i++)
			{
				fprintf(file_enc_pix, "\n");
				fprintf(file_enc_pix, "%" PRIu16 "", t_pix_enc[l][i]);
			}
		}

		fclose(file_enc_pix);
	}
	else
	{
		cmd_colorError();
		fprintf(stderr, "n value not supported.");
		cmd_colorStandard();
		exit(EXIT_FAILURE);
	}
}