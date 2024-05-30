/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_model.hpp
 *
 * Description : Implémentation de singleton de
 *  https://www.geeksforgeeks.org/implementation-of-singleton-class-in-cpp/
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

class PaillierModel
{

private:
    uint64_t lambda, n, mu, g, p, q;
    PaillierPrivateKey privateKey;
    PaillierPublicKey publicKey;
    Paillier<uint64_t,uint64_t> paillier_generation_key;

    static PaillierModel *instancePtr;

    PaillierModel();

public:
    PaillierModel(const PaillierModel &obj) = delete;

    static PaillierModel *getInstance(){
    if (instancePtr == NULL)
    {
        instancePtr = new PaillierModel();
        return instancePtr;
    }
    else
    {
        return instancePtr;
    }
    };


    // Getters
    uint64_t getLambda() const;
    uint64_t getN() const;
    uint64_t getMu() const;
    uint64_t getG() const;
    uint64_t getP() const;
    uint64_t getQ() const;

    Paillier<uint64_t,uint64_t> getPaillierGenerationKey() const;
    PaillierPrivateKey getPrivateKey() const;
    PaillierPublicKey getPublicKey() const;

    // Setters
    void setLambda(uint64_t value);
    void setN(uint64_t value);
    void setMu(uint64_t value);
    void setG(uint64_t value);
    void setP(uint64_t value);
    void setQ(uint64_t value);

    void setPaillierGenerationKey(Paillier<uint64_t,uint64_t> value);
    void setPrivateKey(PaillierPrivateKey value);
    void setPublicKey(PaillierPublicKey value);

    ~PaillierModel();
};

#endif // PAILLIER_MODEL