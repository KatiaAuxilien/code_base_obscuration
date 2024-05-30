/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerStat.hpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 29 mai 2024, 13:55:00
 *
 *******************************************************************************/

#ifndef PAILLIERCONTROLLER_Stat
#define PAILLIERCONTROLLER_Stat

#include <stdio.h>
#include "include/controller/PaillierController.hpp"

class PaillierControllerStat : public PaillierController
{
public:
    /**
     *  @brief
     *  @details Vérification pour le programme effectuant des calculs statistiques sur r.
     *  @param char* arg_in[]
     *  @param bool param[]
     *				0	bool useKeys = false;
     *				1	bool distributeOnTwo = false;
     *				2	bool optimisationLSB = false;
     *  @authors Katia Auxilien
     *  @date 27/05/2024 11:52:00
     */
    void checkParameters(char *arg_in[], int size_arg, bool param[], char *&c_key_file, uint64_t &p, uint64_t &q, uint64_t &n, uint64_t &lambda);

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
    void checkParameters(char *arg_in[], int size_arg, bool param[], uint64_t &p, uint64_t &q, uint64_t &n, uint64_t &lambda);
}
#endif // PAILLIERCONTROLLER_Stat