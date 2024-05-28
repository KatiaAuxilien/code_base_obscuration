/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_model.hpp
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
#ifndef PAILLIER_MODEL
#define PAILLIER_MODEL

#include <stdio.h>
#include "../../include/model/encryption/Paillier/Paillier.hpp"
#include "../../include/model/encryption/Paillier/keys/Paillier_private_key.hpp"
#include "../../include/model/encryption/Paillier/keys/Paillier_public_key.hpp"

class PaillierModel{

    public :
        PaillierModel();
        PaillierModel(Paillier cryptosysteme = null,PaillierPublicKey pubKey = null,PaillierPrivateKey prvKey = null);
        uint64_t lambda, n, mu, g, p, q;
        Paillier paillier;
        PaillierPrivateKey privateKey;
        PaillierPublicKey publicKey;
        ~PaillierModel();
    private:
}

#endif // PAILLIER_MODEL