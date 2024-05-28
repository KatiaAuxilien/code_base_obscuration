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
#include "../../../include/model/encryption/Paillier/Paillier.hpp"
#include "../../../include/model/encryption/Paillier/keys/Paillier_private_key.hpp"
#include "../../../include/model/encryption/Paillier/keys/Paillier_public_key.hpp"
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

	bool parameters[3];
	char *c_file;
	char *c_key_file;
	uint64_t lambda, n, mu, g, p, q;

	convertToLower(argv, argc);
	checkParameters(argv, argc, parameters, c_key_file, p, q, n, lambda);

	bool useKeys = parameters[0];
	bool distributeOnTwo = parameters[1];
	bool optimisationLSB = parameters[2];
 
	string s_file = c_file;
	string s_key_file;
	if (useKeys)
	{
		s_key_file = c_key_file;
	}

	/********************************************************************/

	/*********************** Traitement de clé ***********************/

	PaillierPrivateKey pk;
	PaillierPublicKey pubk;

	if (!useKeys)
	{
		Paillier<uint64_t, uint64_t> paillier;
		mu = 0;
		g = paillier.generate_g_64t(n,lambda);
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
		if(lambda == 0 || mu == 0 || p == 0 || q == 0 || n == 0 || g == 0){
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
		
		FILE *f_private_key = NULL;

		f_private_key = fopen("Paillier_private_key.bin", "w+b");

		if (f_private_key == NULL)
		{
			cmd_colorError();			
			fprintf(stderr, "Error ! Opening Paillier_private_key.bin\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}

		fwrite(&pk, sizeof(PaillierPrivateKey), 1, f_private_key);

		fclose(f_private_key);

		FILE *f_public_key = NULL;
		f_public_key = fopen("Paillier_public_key.bin", "w+b");

		if (f_public_key == NULL)
		{
			cmd_colorError();			
			fprintf(stderr, "Error ! Opening Paillier_public_key.bin\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
		fwrite(&pubk, sizeof(PaillierPublicKey), 1, f_public_key);

		fclose(f_public_key);

			printf("p = %" PRIu64 "\n", p);
			printf("q = %" PRIu64 "\n", q);
			printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
			printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
			printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
			printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
	}
	else
	{
			size_t size;
			FILE *f_public_key = NULL;
			f_public_key = fopen(c_key_file, "rb");

			if (f_public_key == NULL)
			{
				cmd_colorError();
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				cmd_colorStandard();
				exit(EXIT_FAILURE);
			}
			size = sizeof(PaillierPublicKey);
			size_t items_read = fread(&pubk, size, 1, f_public_key);
			if(items_read != 1)
			{
				cmd_colorError();
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				cmd_colorStandard();
				exit(EXIT_FAILURE);
			}

			fclose(f_public_key);
	}

	/*********************** Instanciations de Paillier en fonction de n ***********************/

	/*********************** Chiffrement ***********************/
		printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
		printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
		printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
		printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
		if (n <= 256)
		{
			Paillier<uint8_t, uint16_t> paillier;
			uint64_t n = pubk.getN();
			uint64_t g = pubk.getG();
			std::vector<uint64_t> set_ZNZStar = paillier.get_set_ZNZStar(n) ;
					
			size_t size_vec_r = set_ZNZStar.size();

			uint16_t t_pix_enc[size_vec_r][n];

			for (size_t l = 0; l < size_vec_r ; l++)
			{
				for (uint64_t i = 0; i < n; i++)
				{
					
					unsigned char msg = i;
					uint16_t pixel_enc = paillier.paillierEncryption(n, g, msg, set_ZNZStar.at(l));
					t_pix_enc[l][i] = pixel_enc;
					if(i == 0){
						fprintf(stdout, "Enc (0) : %" PRIu16 "\n", pixel_enc);
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