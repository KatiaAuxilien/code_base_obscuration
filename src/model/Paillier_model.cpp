/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_model.cpp
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

#include "../../include/model/Paillier_model.hpp"

PaillierModel::PaillierModel(){};

static PaillierModel PaillierModel::*getInstance()
{
    if (this->instancePtr == NULL)
    {
        this->instancePtr = new PaillierModel();
        return this->instancePtr;
    }
    else
    {
        return this->instancePtr;
    }
};

uint64_t PaillierModel::getLambda() const { return this->lambda; }
uint64_t PaillierModel::getN() const { return this->n; }
uint64_t PaillierModel::getMu() const { return this->mu; }
uint64_t PaillierModel::getG() const { return this->g; }
uint64_t PaillierModel::getP() const { return this->p; }
uint64_t PaillierModel::getQ() const { return this->q; }
Paillier PaillierModel::getPaillier() const { return this->paillier; }
PaillierPrivateKey PaillierModel::getPrivateKey() const { return this->privateKey; }
PaillierPublicKey PaillierModel::getPublicKey() const { return this->publicKey; }

// Setters
void PaillierModel::setLambda(uint64_t value) { this->lambda = value; }
void PaillierModel::setN(uint64_t value) { this->n = value; }
void PaillierModel::setMu(uint64_t value) { this->mu = value; }
void PaillierModel::setG(uint64_t value) { this->g = value; }
void PaillierModel::setP(uint64_t value) { this->p = value; }
void PaillierModel::setQ(uint64_t value) { this->q = value; }
void PaillierModel::setPaillier(Paillier value) { this->paillier = value; }
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
    this->setN(value.getN);
    this->setG(value.getG);    
}
