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

#include "../../../include/controller/PaillierControllerStatG.hpp"

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
	PaillierControllerStatG controller = new PaillierControllerStatG();
	/*********************** Traitement d'arguments ***********************/
	if (argc < 2)
	{
		printf("Usage : p q\n-k public_key.bin\n");
		return 1;
	}
	bool parameters[2];
	controller.checkParameters(argv, argc, parameters, p, q, n, lambda);
	bool distributeOnTwo = parameters[0];
	bool optimisationLSB = parameters[1];

	/********************************************************************/
	/*********************** Calculs ***********************/
	controller.calc_encrypt();
	/*======================== Enregistrement fichier ========================*/
	controller.saveResults();
}