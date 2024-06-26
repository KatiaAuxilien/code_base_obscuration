/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : Paillier_num_main_V5_calc_r.cpp
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
#include "../../../include/controller/PaillierControllerStatR.hpp"

#include <iostream>
#include <set>
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>

using namespace std;

int main(int argc, char **argv)
{
	PaillierControllerStatR* controller = new PaillierControllerStatR();
	/*********************** Traitement d'arguments ***********************/

	if (argc < 2)
	{
		printf("Usage : p q\n-k public_key.bin\n");
		exit(EXIT_FAILURE);
	}

	bool parameters[4];
	controller->checkParameters(argv, argc, parameters);
	bool useKeys = parameters[0];
	bool distributeOnTwo = parameters[1];
	bool optimisationLSB = parameters[2];
	bool needHelp = parameters[3];

	if(needHelp)
	{
		controller->printHelp();
		exit(EXIT_SUCCESS);
	}

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
	/*********************** Chiffrement et enregistrement de résultats ***********************/
	if (controller->getModel()->getPublicKey().getN() <= 256)
	{
		controller->calc_encrypt();
	}
	else
	{
		controller->getView()->error_failure("n value not supported.");
		exit(EXIT_FAILURE);
	}
}