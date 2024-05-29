/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierController.hpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 28 mai 2024, 13:48:00
 *
 *******************************************************************************/
#ifndef PAILLIERCONTROLLER
#define PAILLIERCONTROLLER

#include <stdio.h>
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <ctype.h>

#include "../include/model/Paillier_model.hpp"
#include "../include/view/commandLineInterface.hpp" // Gestion de l'affichage dans le terminal (couleurs, ...)

class PaillierController
{
protected:
	char *c_key_file;

    const PaillierModel *model = PaillierModel::getInstance();
    const commandLineInterface *view = commandLineInterface::getInstance();

    /**
     *  @brief
     *  @details Vérification de l'argument en paramètre, afin de voir si c'est bel et bien un nom de fichier terminant par .pgm.
     *  @param const std::string &str
     * 	@param const std::string &suffix
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    bool endsWith(const std::string &str, const std::string &suffix);

    /**
     *  @brief
     *  @details
     *  @param char *arg_in[]
     *  @param int size_arg_in
     *  @authors Katia Auxilien
     *  @date 15/05/2024
     */
    void convertToLower(char *arg_in[], int size_arg_in);

    /**
     *  @brief Vérifier si n est un nombre premier.
     *  @details
     *  @param int n
     *  @param int i
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    bool isPrime(int n, int i = 2);

    /**
     *  @brief
     *  @details Vérification de l'argument en paramètre, afin de voir si c'est bel et bien un nombre et qu'il est premier.
     * 	@param char *arg
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    uint64_t check_p_q_arg(char *arg);

public:
    PaillierController();
    ~PaillierController();
    virtual void init();

    const char* getCKeyFile() const;
    void setCKeyFile(char* newCKeyFile);

    void generateAndSaveKeyPair();

    void readKeyFile(bool isEncryption);
}

#endif // PAILLIERCONTROLLER