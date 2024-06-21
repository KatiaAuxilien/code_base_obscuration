/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_model.cpp
 *
 * Description : Implementation of singleton of
 *              https://www.geeksforgeeks.org/implementation-of-singleton-class-in-cpp/
 *              using the Paillier cryptosystem.
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 28 mai 2024, 13:48:00
 *
 *******************************************************************************/

#include "../../include/model/Paillier_model.hpp"

PaillierModel::PaillierModel(){};

PaillierModel *PaillierModel ::instancePtr = NULL;

uint64_t PaillierModel::getLambda() const { return this->lambda; }
uint64_t PaillierModel::getN() const { return this->n; }
uint64_t PaillierModel::getMu() const { return this->mu; }
uint64_t PaillierModel::getG() const { return this->g; }
uint64_t PaillierModel::getP() const { return this->p; }
uint64_t PaillierModel::getQ() const { return this->q; }
Paillier<uint64_t, uint64_t> PaillierModel::getPaillierGenerationKey() const { return this->paillier_generation_key; }
PaillierPrivateKey PaillierModel::getPrivateKey() const { return this->privateKey; }
PaillierPublicKey PaillierModel::getPublicKey() const { return this->publicKey; }

// Setters
void PaillierModel::setLambda(uint64_t value) { this->lambda = value; }
void PaillierModel::setN(uint64_t value) { this->n = value; }
void PaillierModel::setMu(uint64_t value) { this->mu = value; }
void PaillierModel::setG(uint64_t value) { this->g = value; }
void PaillierModel::setP(uint64_t value) { this->p = value; }
void PaillierModel::setQ(uint64_t value) { this->q = value; }

void PaillierModel::setPaillierGenerationKey(Paillier<uint64_t, uint64_t> value)
{
    this->paillier_generation_key = value;
}

void PaillierModel::setPrivateKey(PaillierPrivateKey value)
{
    this->privateKey = value;
    this->setLambda(value.getLambda());
    this->setN(value.getN());
    this->setMu(value.getMu());
}
void PaillierModel::setPublicKey(PaillierPublicKey value)
{
    this->publicKey = value;
    this->setN(value.getN());
    this->setG(value.getG());
}
