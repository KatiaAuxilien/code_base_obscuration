/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerStatR.hpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien\mail.fr
 *
 * Date : 30 mai 2024, 15:50:00
 *
 *******************************************************************************/

#ifndef PAILLIERCONTROLLER_Stat_R
#define PAILLIERCONTROLLER_Stat_R

#include <stdio.h>
#include "../../include/controller/PaillierController.hpp"

class PaillierControllerStatR : public PaillierController
{
public:

    /**
    * \brief 
    * \details
    * \author 
    * \date 
    */
    PaillierControllerStatR();
    
    /**
    * \brief 
    * \details
    * \author 
    * \date 
    */
    ~PaillierControllerStatR();
    void init();

    /**
     *  \brief
     *  \details Vérification pour le programme effectuant des calculs statistiques sur r.
     *  \param char* arg_in[]
     *  \param int size_arg
     *  \param bool param[]
     *				0	bool useKeys = false;
     *				1	bool distributeOnTwo = false;
     *				2	bool optimisationLSB = false;
     *  \authors Katia Auxilien
     *  \date 27/05/2024 11:52:00
     */
    void checkParameters(char *arg_in[], int size_arg, bool param[]);

	/**
	 * \brief Afficher le manuel du programme.
	 * \author Katia Auxilien
	 * \date 07/06/2024 16:41:00
	 */
	void printHelp();

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
#endif // PAILLIERCONTROLLER_Stat_R
