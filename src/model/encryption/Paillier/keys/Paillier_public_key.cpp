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
#include "../../../../../include/model/encryption/Paillier/keys/Paillier_public_key.hpp"

PaillierPublicKey::PaillierPublicKey()
{
    this->n = this->g = 0;
}

PaillierPublicKey::PaillierPublicKey(uint64_t N, uint64_t G)
{
    this->n = N;
    this->g = G;
}

uint64_t PaillierPublicKey::getN () const
{
    return this->n;
}

uint64_t PaillierPublicKey::getG () const
{
    return this->g;
}

PaillierPublicKey::~PaillierPublicKey() {}
