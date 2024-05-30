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
#include "../../../include/controller/PaillierControllerStatR.hpp"

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
	PaillierControllerStatR controller = new PaillierControllerStatR();
	/*********************** Traitement d'arguments ***********************/

	if (argc < 2)
	{
		printf("Usage : p q\n-k public_key.bin\n");
		return 1;
	}

	bool parameters[3];

	controller.checkParameters(argv, argc, parameters);

	bool useKeys = parameters[0];
	bool distributeOnTwo = parameters[1];
	bool optimisationLSB = parameters[2];
 
	/********************************************************************/

	if (!useKeys)
	{
		controller->generateAndSaveKeyPair();
	}
	else
	{
		controller->readKeyFile(true);
	}

	/*********************** Instanciations de Paillier en fonction de n ***********************/

	// uint64_t n = controller->getModel()->getN();
	// /*********************** Chiffrement ***********************/

	// if (isEncryption)
	// {
	// 	printf("Pub Key G = %" PRIu64 "\n", controller->getModel()->getPublicKey().getG());
	// 	printf("Pub Key N = %" PRIu64 "\n", controller->getModel()->getPublicKey().getN());
	// 	if (n <= 256)
	// 	{
	// 		Paillier<uint8_t, uint16_t> paillier;
	// 		controller->encrypt(distributeOnTwo, recropPixels,paillier);
	// 	}
	// 	// else if (n > 256 && n <= 65535)
	// 	// {
	// 	// 	Paillier<uint16_t, uint32_t> paillier;
	// 	// 	controller->encrypt2(distributeOnTwo, recropPixels,paillier);
	// 	// }
	// 	else
	// 	{
	// 		controller->getView()->error_failure("n value not supported.");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	// /*********************** Déchiffrement ***********************/
	// else
	// {
	// 	printf("Priv Key lambda = %" PRIu64 "\n", controller->getModel()->getPrivateKey().getLambda());
	// 	printf("Priv Key mu = %" PRIu64 "\n", controller->getModel()->getPrivateKey().getMu());
	// 	if (n <= 256)
	// 	{
	// 		Paillier<uint8_t, uint16_t> paillier;
	// 		controller->decrypt(distributeOnTwo,paillier);
	// 	}
	// 	// else if (n > 256 && n <= 65535)
	// 	// {
	// 	// 	Paillier<uint16_t, uint32_t> paillier;
	// 	// 	controller->decrypt2(distributeOnTwo,paillier);
	// 	// }
	// 	else
	// 	{
	// 		controller->getView()->error_failure("n value not supported.");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }



	/*********************** Instanciations de Paillier en fonction de n ***********************/

	/*********************** Chiffrement ***********************/
		printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
		printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
		printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
		printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
		if (n <= 256)
		{

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