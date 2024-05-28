/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_private_key.cpp
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
#include "../../../../include/model/encryption/Paillier/keys/Paillier_private_key.hpp"

PaillierPrivateKey::PaillierPrivateKey()
{
    this->lambda = this->mu = 0;
}

PaillierPrivateKey::PaillierPrivateKey(uint64_t l, uint64_t m)
{
    this->lambda = l;
    this->mu = m;
}

PaillierPrivateKey::PaillierPrivateKey(uint64_t l, uint64_t m, uint64_t nn)
{
    this->lambda = l;
    this->mu = m;
    this->n = nn;
}

uint64_t PaillierPrivateKey::getLambda() const
{
    return this->lambda;
}

uint64_t PaillierPrivateKey::getMu() const
{
    return this->mu;
}

uint64_t PaillierPrivateKey::getN() const
{
    return this->n;
}

PaillierPrivateKey::~PaillierPrivateKey() {}
