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

#include "../../../include/controller/PaillierControllerStatG.hpp"

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
	PaillierControllerStatG* controller = new PaillierControllerStatG();
	/*********************** Traitement d'arguments ***********************/
	if (argc < 2)
	{
		printf("Usage : p q\n");
		exit(EXIT_FAILURE);
	}
	bool parameters[3];
	controller->checkParameters(argv, argc, parameters);
	bool distributeOnTwo = parameters[0];
	bool optimisationLSB = parameters[1];
	bool needHelp = parameters[2];

	if(needHelp)
	{
		controller->printHelp();
		exit(EXIT_SUCCESS);
	}
//TODO : Implémente la prise en charge des paramtères

	/********************************************************************/
	/*********************** Calculs ***********************/
	controller->calc_encrypt_10_g();
	return 0;
}