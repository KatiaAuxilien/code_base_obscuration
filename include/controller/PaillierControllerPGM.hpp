/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerPGM.hpp
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
#ifndef PAILLIERCONTROLLER_PGM
#define PAILLIERCONTROLLER_PGM

#include <stdio.h>
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <ctype.h>

#include "../../include/controller/PaillierController.hpp"
#include "../../include/model/image/image_pgm.hpp"

class PaillierControllerPGM : public PaillierController
{

private:
    image_pgm img_pgm;
    char *c_file;

public:
    void init();

    const image_pgm getImagePgm() const;
    void setImagePgm(image_pgm image);

    const char *getCFile() const;
    void setCFile(char *newCFile);

    /**
     *  \brief
     *  \details Vérification
     *  \param char* arg_in[]
     *  \param bool param[]
     *				0	bool isEncryption = false ;
     *				1	bool useKeys = false;
     *				2	bool distributeOnTwo = false;
     *				3	bool recropPixels = false;
     *				4	bool optimisationLSB = false;
     *  \authors Katia Auxilien
     *  \date 15/05/2024 9:00:00
     */
    void checkParameters(char *arg_in[], int size_arg, bool param[]);

    /*********************** Chiffrement/Déchiffrement ***********************/

    /************** 8bits **************/
    /**
     *  \brief
     *  \details
     *  \param bool distributeOnTwo
     *  \param bool recropPixels
     *  \authors Katia Auxilien
     *  \date 15/05/2024
     */
    template <typename T_in, typename T_out>
    void encrypt(bool distributeOnTwo, bool recropPixels, Paillier<T_in,T_out> paillier);

    /**
     *  \brief
     *  \details
     *  \param bool distributeOnTwo
     *  \authors Katia Auxilien
     *  \date 15/05/2024
     */
    template <typename T_in, typename T_out>
    void decrypt(bool distributeOnTwo,Paillier<T_in,T_out> paillier);

    /************** n > 8bits**************/
    
    /**
     *  \brief
     *  \details
     *  \param bool distributeOnTwo
     *  \param bool recropPixels
     *  \param Paillier<T_in, T_out> paillier
     *  \authors Katia Auxilien
     *  \date 15/05/2024
     */
    template <typename T_in, typename T_out>
    void encrypt2(bool distributeOnTwo, bool recropPixels, Paillier<T_in,T_out> paillier);

    /**
     *  \brief
     *  \details
     *  \param bool distributeOnTwo
     *  \param bool recropPixels
     *  \param Paillier<T_in, T_out> paillier
     *  \authors Katia Auxilien
     *  \date 15/05/2024
     */
    template <typename T_in, typename T_out>
    void decrypt2(bool distributeOnTwo, Paillier<T_in,T_out> paillier);
};
#endif // PAILLIERCONTROLLER_PGM