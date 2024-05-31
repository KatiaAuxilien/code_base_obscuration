/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerStatG.hpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 30 mai 2024, 15:50
 *
 *******************************************************************************/

#ifndef PAILLIERCONTROLLER_Stat_G
#define PAILLIERCONTROLLER_Stat_G

#include <stdio.h>
#include "../../include/controller/PaillierController.hpp"

class PaillierControllerStatG : public PaillierController
{
public:
	PaillierControllerStatG();
	~PaillierControllerStatG();
	void init();

	/**
	 *  @brief
	 *  @details Vérification pour le programme effectuant des calculs statistiques sur g.
	 *  @param char* arg_in[]
	 *  @param bool param[]
	 *				0	bool distributeOnTwo = false;
	 *				1	bool optimisationLSB = false;
	 *  @authors Katia Auxilien
	 *  @date 27/05/2024 11:52:00
	 */
	void checkParameters(char *arg_in[], int size_arg, bool param[]);

	/*********************** Chiffrement/Déchiffrement ***********************/

	/************** 8bits **************/
	/**
	 *  \brief
	 *  \details
	 *  \param
	 *  \authors Katia Auxilien
	 *  \date 30/05/2024
	 */
	void calc_encrypt();
};
#endif // PAILLIERCONTROLLER_Stat_G
