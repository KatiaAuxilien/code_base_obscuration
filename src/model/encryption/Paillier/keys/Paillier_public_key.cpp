/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_public_key.cpp
 *
 * Description : 
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 28 Mai 2024, 13:55:00
 *
 *******************************************************************************/
#include "../../../../include/encryption/Paillier/keys/Paillier_public_key.hpp"

PaillierPublicKey::PaillierPublicKey()
{
    n = g = 0;
}

PaillierPublicKey::PaillierPublicKey(uint64_t N, uint64_t G)
{
    n = N;
    g = G;
}

uint64_t PaillierPublicKey::getN()
{
    return n;
}

uint64_t PaillierPublicKey::getG()
{
    return g;
}

PaillierPublicKey::~PaillierPublicKey() {}
