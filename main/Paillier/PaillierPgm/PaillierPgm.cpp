/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : Paillier_pgm_main.cpp
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


#include "../../../include/controller/PaillierControllerPGM.hpp"

#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <ctype.h>
#include <errno.h> /* errno */ //TODO : Gestion des erreurs + propre.

using namespace std;

//TODO : Documentation

int main(int argc, char **argv)
{
	PaillierControllerPGM *controller = new PaillierControllerPGM();

	/*********************** Traitement d'arguments ***********************/

	if (argc == 1|| (argc < 3 && argv[1][1] != 'h'))
	{
		controller->printHelp();
		return 1;
	}

	bool parameters[6];
	controller->checkParameters(argv, argc, parameters);

	bool isEncryption = parameters[0];
	bool useKeys = parameters[1];
	bool distributeOnTwo = parameters[2];
	bool recropPixels = parameters[3];
	bool optimisationLSB = parameters[4];
	bool needHelp = parameters[5];

	if(needHelp)
	{
		controller->printHelp();
		exit(EXIT_SUCCESS);
	}

	/*********************** Traitement de clé ***********************/

	if (!useKeys && isEncryption)
	{
		controller->generateAndSaveKeyPair();
	}
	else
	{
		controller->readKeyFile(isEncryption);
	}

	/*********************** Instanciations de Paillier en fonction de n ***********************/

	uint64_t n = controller->getModel()->getN();
	/*********************** Chiffrement ***********************/

	if (isEncryption)
	{
		if (n <= 256)
		{
			if (!optimisationLSB)
			{
				Paillier<uint8_t, uint16_t> paillier;
				controller->encrypt(distributeOnTwo, recropPixels, paillier);
			}
			if (optimisationLSB)
			{
				Paillier<uint8_t, uint16_t> paillier;
				controller->encryptCompression(recropPixels, paillier);
			}
		}
		// else if (n > 256 && n <= 65535)
		// {
		// 	Paillier<uint16_t, uint32_t> paillier;
		// 	controller->encrypt2(distributeOnTwo, recropPixels,paillier);
		// }
		else
		{
			controller->getView()->error_failure("n value not supported.");
			exit(EXIT_FAILURE);
		}
	}
	/*********************** Déchiffrement ***********************/
	else
	{
		if (n <= 256)
		{
			if (!optimisationLSB)
			{
				Paillier<uint8_t, uint16_t> paillier;
				controller->decrypt(distributeOnTwo, paillier);
			}
			if (optimisationLSB)
			{
				Paillier<uint8_t, uint16_t> paillier;
				controller->decryptCompression(paillier);
			}
		}
		// else if (n > 256 && n <= 65535)
		// {
		// 	Paillier<uint16_t, uint32_t> paillier;
		// 	controller->decrypt2(distributeOnTwo,paillier);
		// }
		else
		{
			controller->getView()->error_failure("n value not supported.");
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}