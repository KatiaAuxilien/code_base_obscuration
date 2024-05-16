/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_16bit.cpp
 *
 * Description :
 *   
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 16/05/2024 16:00:00
 *
 *******************************************************************************/
#include <iostream>
#include <bitset>
#include <vector>
#include "../../../../include/encryption/Paillier/Paillier_nbit/Paillier_16bit.hpp"

Paillier_16bit::Paillier_16bit(){};

Paillier_16bit::Paillier_16bit(Paillier p){
    paillier = p;
};

uint32_t Paillier_16bit::paillierEncryption(uint64_t n, uint64_t g, uint16_t m){
    uint64_t c = paillier.paillierEncryption(n,g,m);
    if (c >= std::numeric_limits<uint32_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 32 bits.");
    }
    return static_cast<uint32_t>(c);
}

uint32_t Paillier_16bit::paillierEncryption(uint64_t n,uint64_t g, uint16_t m, uint64_t r)
{
    uint64_t c = paillier.paillierEncryption(n,g,m,r);
    if (c >= std::numeric_limits<uint32_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 32 bits.");
    }
    return static_cast<uint32_t>(c);
}


uint16_t Paillier_16bit::paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, uint32_t c)
{
    uint64_t result = paillier.paillierDecryption(n,lambda,mu,c);
    if (result >= std::numeric_limits<uint16_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 16 bits.");
    }
    return static_cast<uint16_t>(result);
}

Paillier_16bit::~Paillier_16bit(){};
