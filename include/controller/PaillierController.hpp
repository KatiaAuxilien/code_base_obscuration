/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_controller.hpp
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
#ifndef PAILLIER_CONTROLLER
#define PAILLIER_CONTROLLER

#include <stdio.h>

#include "../../include/model/Paillier_model.hpp"
#include "../../include/view/commandLineInterface/Paillier_arguments.hpp" //Traitement des arguments.
#include "../../include/interface/view/commandLineInterface/interface_cmd.hpp"	  // Gestion de l'affichage dans le terminal (couleurs, ...)

class Paillier_controller{

    public :
        Paillier_controller();
        Paillier_controller(Paillier cryptosysteme = null,PaillierPublicKey pubKey = null,PaillierPrivateKey prvKey = null);
        uint64_t lambda, n, mu, g, p, q;
        PaillerModel model;
    
        ~Paillier_controller();
    private:
}

#endif // PAILLIER_CONTROLLER