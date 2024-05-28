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
#include "../../../../include/encryption/Paillier/keys/Paillier_private_key.hpp"

PaillierPrivateKey::PaillierPrivateKey()
{
    lambda = mu = 0;
}

PaillierPrivateKey::PaillierPrivateKey(uint64_t l, uint64_t m)
{
    lambda = l;
    mu = m;
}

PaillierPrivateKey::PaillierPrivateKey(uint64_t l, uint64_t m, uint64_t nn)
{
    lambda = l;
    mu = m;
    n = nn;
}

uint64_t PaillierPrivateKey::getLambda()
{
    return lambda;
}

uint64_t PaillierPrivateKey::getMu()
{
    return mu;
}

uint64_t PaillierPrivateKey::getN()
{
    return n;
}

PaillierPrivateKey::~PaillierPrivateKey() {}
