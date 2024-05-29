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

#include "../../../include/model/image/image_pgm.hpp" 
#include "../../../include/controller/PaillierControllerPGM.hpp"


#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <ctype.h>
#include <errno.h> /* errno */ //TODO : Gestion des erreurs + propre.

using namespace std;

int main(int argc, char **argv)
{
	PaillierControllerPGM controller = new PaillierControllerPGM();
	controller.init();

	/*********************** Traitement d'arguments ***********************/

	if (argc < 3)
	{
		printf("Usage : [e or ek or dk] [params] image_file.pgm\n e p q file.pgm\n ek public_key.bin image_file.pgm\n dk private_key.bin image_file_encrypted.pgm\n");
		return 1;
	}

	bool parameters[5];
	controller.checkParameters(argv, argc, parameters);

	bool isEncryption = parameters[0];
	bool useKeys = parameters[1];
	bool distributeOnTwo = parameters[2];
	bool recropPixels = parameters[3];
	bool optimisationLSB = parameters[4];

	// string s_file = c_file;
	// string s_key_file;
	// if (isEncryption && useKeys)
	// {
	// 	s_key_file = c_key_file;
	// }

	/*********************** Traitement de clé ***********************/

	if (!useKeys && isEncryption)
	{
		controller.generateAndSaveKeyPair();
	}
	else
	{
		controller.readKeyFile(isEncryption);
	}

	/*********************** Instanciations de Paillier en fonction de n ***********************/


	uint64_t n = controller.model.getN();
	/*********************** Chiffrement ***********************/
	if (isEncryption)
	{
		
		if (n <= 256)
		{
			printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
			printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
			Paillier<uint8_t, uint16_t> paillier;
			encrypt(s_file, pubk, distributeOnTwo, recropPixels, paillier);
		}
		else if (n > 256 && n <= 65535)
		{

			Paillier<uint16_t, uint32_t> paillier;
			encrypt2(s_file, pubk, distributeOnTwo, recropPixels, paillier);
		}
		else
		{
			controller.view.error_failure("n value not supported.");
			exit(EXIT_FAILURE);
		}
	}
	/*********************** Déchiffrement ***********************/
	else
	{
		if (n <= 256)
		{
			printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
			printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
			Paillier<uint8_t, uint16_t> paillier;
			decrypt(s_file, pk, distributeOnTwo,paillier);
		}
		else if (n > 256 && n <= 65535)
		{
			Paillier<uint16_t, uint32_t> paillier;
			decrypt2(s_file, pk, distributeOnTwo,paillier);
		}
		else
		{
			controller.view.error_failure("n value not supported.");
			exit(EXIT_FAILURE);
		}
	}
}