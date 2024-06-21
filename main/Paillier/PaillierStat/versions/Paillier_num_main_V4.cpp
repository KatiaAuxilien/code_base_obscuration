/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : Paillier_num_main_V4.cpp
 *
 * Description : Essais sur la taille d'un chiffré dont n > 255
 *   File source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
 *
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024 - Mai 2024
 *
 *******************************************************************************/
#include "../../../include/encryption/Paillier/Paillier.hpp"
#include "../../../include/encryption/Paillier/keys/Paillier_private_key.hpp"
#include "../../../include/encryption/Paillier/keys/Paillier_public_key.hpp"
#include "../../../include/filesystem/filesystemCommon.h" //Navigation dans le système de fichier
#include "../../../include/filesystem/filesystemPGM.h"
#include "../../../include/interface/cmd/interface_cmd.hpp"	  // Gestion de l'affichage dans le terminal (couleurs, ...)
#include "../../../include/controller/Paillier_arguments.hpp" //Traitement des arguments.

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

	if (argc < 3)
	{
		printf("Usage : [e or ek or dk] [params] image_file.pgm\n e p q file.pgm\n ek public_key.bin image_file.pgm\n dk private_key.bin image_file_encrypted.pgm\n");
		return 1;
	}

	bool parameters[5];
	char *c_file;
	char *c_key_file;
	uint64_t lambda, n, mu, g, p, q;

	convertToLower(argv, argc);
	checkParameters(argv, argc, parameters, c_key_file, c_file, p, q, n, lambda);

	bool isEncryption = parameters[0];
	bool useKeys = parameters[1];
	// bool distributeOnTwo = parameters[2];
	// bool recropPixels = parameters[3];
	// bool optimisationLSB = parameters[4];

	string s_file = c_file;
	string s_key_file;
	if (isEncryption && useKeys)
	{
		s_key_file = c_key_file;
	}

	/********************************************************************/

	/*********************** Traitement de clé ***********************/

	PaillierPrivateKey pk;
	PaillierPublicKey pubk;

	if (!useKeys && isEncryption)
	{
		Paillier<uint64_t, uint64_t> paillier;

		vector<uint64_t> vector_g = paillier.calc_set_same_remainder_divide_euclide_64t_v2(n * n, lambda);
		mu = 0;
		if(vector_g.size() == 0){
			cmd_colorError();
			fprintf(stderr, "ERROR with g, no value found for g where mu exist.\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
		g = paillier.choose_g_in_vec_64t_v2(vector_g);
		paillier.generatePrivateKey_64t(lambda, mu, p, q, n, g);
		// if (mu == 0)
		// {
		// 	cmd_colorError();
		// 	fprintf(stderr, "ERROR with g, no value found for g where mu exist.\n");
		// 	cmd_colorStandard();
		// 	exit(EXIT_FAILURE);
		// }

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
		if (!isEncryption)
		{
			size_t size;
			FILE *f_private_key = NULL;

			f_private_key = fopen(c_key_file, "rb");

			if (f_private_key == NULL)
			{
				cmd_colorError();
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				cmd_colorStandard();
				exit(EXIT_FAILURE);
			}

			size = sizeof(PaillierPrivateKey);
			size_t items_read = fread(&pk, size, 1, f_private_key);
			if(items_read != 1)
			{
				cmd_colorError();
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				cmd_colorStandard();
				exit(EXIT_FAILURE);
			}

			fclose(f_private_key);
		}
		if (isEncryption)
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
	}

	/*********************** Instanciations de Paillier en fonction de n ***********************/

	/*********************** Chiffrement ***********************/
	if (isEncryption)
	{
		printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
		printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
		printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
		printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
		if (n <= 256)
		{
			Paillier<uint8_t, uint16_t> paillier;
			uint64_t n = pubk.getN();
			uint64_t g = pubk.getG();

			unsigned char msg = 18;
			fprintf(stdout, "Msg : %" PRIu8 "\n", msg);
			uint16_t msg_enc = paillier.paillierEncryption(n, g, msg);
			fprintf(stdout, "Enc : %" PRIu16 "\n", msg_enc);
		}
		else if (n > 256 && n <= 65535)
		{
			Paillier<uint8_t, uint32_t> paillier;
			uint64_t n = pubk.getN();
			uint64_t g = pubk.getG();

			unsigned char msg = 18;
			fprintf(stdout, "Msg : %" PRIu8 "\n", msg);
			uint32_t msg_enc = paillier.paillierEncryption(n, g, msg);
			fprintf(stdout, "Enc : %" PRIu32 "\n", msg_enc);
		}
		else
		{
			cmd_colorError();
			fprintf(stderr, "n value not supported.");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
	}
	/*********************** Déchiffrement ***********************/
	else
	{
		uint64_t n, lambda, mu;
		n = pk.getN();	
		lambda = pk.getLambda();
		mu = pk.getMu();
			printf("Pub Key N = %" PRIu64 "\n", pk.getN());
			printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
			printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());

		if (n <= 256)
		{
			Paillier<uint8_t, uint16_t> paillier;

			uint16_t msg_enc = 50189;
			fprintf(stdout, "Enc : %" PRIu16 "\n", msg_enc);			
			uint8_t c = paillier.paillierDecryption(n, lambda, mu, msg_enc);
			fprintf(stdout, "Dec : %" PRIu8 "\n", c);
		}
		else if (n > 256 && n <= 65535)
		{
			Paillier<uint8_t, uint32_t> paillier;

			uint32_t msg_enc = 51643;
			fprintf(stdout, "Enc : %" PRIu32 "\n", msg_enc);			
			uint8_t c = paillier.paillierDecryption(n, lambda, mu, msg_enc);
			fprintf(stdout, "Dec : %" PRIu16 "\n", c);
		}
		else
		{
			cmd_colorError();
			fprintf(stderr, "n value not supported.");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
	}
}