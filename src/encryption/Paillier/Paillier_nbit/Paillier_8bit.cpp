/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_8bit.cpp
 *
 * Description :
 *   
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 16/05/2024 15:52:00
 *
 *******************************************************************************/
#include "../../../../include/encryption/Paillier/Paillier_nbit/Paillier_8bit.hpp"


Paillier_8bit::Paillier_8bit(){};

Paillier_8bit::Paillier_8bit(Paillier p){
    paillier = p;
};

uint16_t Paillier_8bit::paillierEncryption(uint64_t n, uint64_t g, uint8_t m){
    uint64_t c = paillier.paillierEncryption(n,g,m);
    if (c >= std::numeric_limits<uint16_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 16 bits.");
    }
    return static_cast<uint16_t>(c);
}

uint16_t Paillier_8bit::paillierEncryption(uint64_t n,uint64_t g, uint8_t m, uint64_t r)
{
    uint64_t c = paillier.paillierEncryption(n,g,m,r);
    if (c >= std::numeric_limits<uint16_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 16 bits.");
    }
    return static_cast<uint16_t>(c);
}


uint8_t Paillier_8bit::paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, uint16_t c)
{
    uint64_t result = paillier.paillierDecryption(n,lambda,mu,c);
    if (result >= std::numeric_limits<uint8_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 8 bits.");
    }
    return static_cast<uint8_t>(result);
}

Paillier_8bit::~Paillier_8bit(){};