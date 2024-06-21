/**
 * @file Paillier_model.hpp
 * @brief Header of singleton of
 * https://www.geeksforgeeks.org/implementation-of-singleton-class-in-cpp/
 * using the Paillier cryptosystem.
 * @author Katia Auxilien
 * @date 28 may 2024, 13:48:00
 * @details 
 */

#ifndef PAILLIER_MODEL
#define PAILLIER_MODEL

#include <stdio.h>
#include "../../include/model/encryption/Paillier/Paillier.hpp"
#include "../../include/model/encryption/Paillier/keys/Paillier_private_key.hpp"
#include "../../include/model/encryption/Paillier/keys/Paillier_public_key.hpp"

/**
 * @brief This class represents a singleton model for the Paillier cryptosystem.
 * @details It contains the private and public keys, as well as the Paillier generation key.
 * It also contains the parameters of the Paillier cryptosystem: lambda, n, mu, g, p, and q.
 * The Paillier cryptosystem is an asymmetric encryption algorithm that allows
 * for homomorphic addition and multiplication of encrypted data. This class
 * provides a singleton instance of the Paillier cryptosystem, allowing for easy
 * access and management of the public and private keys, as well as the
 * encryption and decryption functions.
 * @author Katia Auxilien
 * @date 28 may 2024, 13:48:00
 */
class PaillierModel
{
private:
    uint64_t lambda;                                      //<! lambda used in the Paillier cryptosystem in privateKey
    uint64_t n;                                           //<! n used in the Paillier cryptosystem in public key
    uint64_t mu;                                          //<! mu used in the Paillier cryptosystem in privateKey
    uint64_t g;                                           //<! g used in the Paillier cryptosystem in public key
    uint64_t p;                                           //<! prime number to obtain n
    uint64_t q;                                           //<! prime number to obtain n
    PaillierPrivateKey privateKey;                        //<! The private key for decryption PaillierPublicKey publicKey
    PaillierPublicKey publicKey;                          //<!  The public key for encryption
    Paillier<uint64_t, uint64_t> paillier_generation_key; //<! The Paillier instance for key generation

    static PaillierModel *instancePtr; //<! The singleton instance of the PaillierModel class

    /**
     * @brief Construct a new Paillier Model object
     * @details Private constructor for the singleton instance of the PaillierModel class.
     * This constructor initializes the Paillier cryptosystem and generates the
     * public and private keys.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    PaillierModel();

public:
    /**
     * @brief Deleted copy constructor to prevent copying of the singleton instance.
     * @param obj Instance of PaillierModel.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    PaillierModel(const PaillierModel &obj) = delete;

    /**
     * @brief Static function to get the singleton instance of the PaillierModel class.
     * @details This function checks if the singleton instance has already been created, and
     * if not, creates a new instance. The instance is then returned.
     * @return PaillierModel*  The singleton instance of the PaillierModel class.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    static PaillierModel *getInstance()
    {
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
    /**
     * @brief Getter function for the lambda variable.
     * @return uint64_t The value of lambda
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    uint64_t getLambda() const;

    /**
     * @brief Getter function for the n variable.
     * @return uint64_t The value of n.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    uint64_t getN() const;

    /**
     * @brief Getter function for the mu variable.
     * @return uint64_t The value of mu.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    uint64_t getMu() const;

    /**
     * @brief Getter function for the g variable.
     * @return uint64_t The value of g
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    uint64_t getG() const;
    /**
     * @brief Getter function for the p variable.
     * @return uint64_t  The value of p.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    uint64_t getP() const;

    /**
     * @brief Getter function for the q variable.
     * @return uint64_t The value of q.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    uint64_t getQ() const;

    /**
     * @brief Getter function for the Paillier instance used for key generation.
     * @return Paillier<uint64_t,uint64_t> The Paillier instance used for key generation.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    Paillier<uint64_t, uint64_t> getPaillierGenerationKey() const;

    /**
     * @brief Getter function for the private key.
     * @return PaillierPrivateKey  The private key.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    PaillierPrivateKey getPrivateKey() const;

    /**
     * @brief Getter function for the public key.
     * @return PaillierPublicKey  The public key
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    PaillierPublicKey getPublicKey() const;

    // Setters
    /**
     * @brief Setter function for the lambda variable.
     * @param[in] value The new value for lambda.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setLambda(uint64_t value);
    /**
     * @brief Setter function for the n variable.
     * @param[in] value The new value for n.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setN(uint64_t value);
    /**
     * @brief Setter function for the mu variable.
     * @param[in] value The new value for mu.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setMu(uint64_t value);
    /**
     * @brief Setter function for the g variable.
     * @param[in] value The new value for g.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setG(uint64_t value);
    /**
     * @brief Setter function for the p variable.
     * @param[in] value The new value for p.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setP(uint64_t value);
    /**
     * @brief Setter function for the q variable.
     * @param[in] value The new value for q.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setQ(uint64_t value);
    /**
     * @brief Setter function for the Paillier instance used for key generation.
     * @param[in] value The new Paillier instance used for key generation.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setPaillierGenerationKey(Paillier<uint64_t, uint64_t> value);
    /**
     * @brief Setter function for the private key.
     * @param[in] value The new private key.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setPrivateKey(PaillierPrivateKey value);
    /**
     * @brief Setter function for the public key.
     * @param[in] value The new public key.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    void setPublicKey(PaillierPublicKey value);

    /**
     * @brief Destructor for the PaillierModel class.
     * @author Katia Auxilien
     * @date 28 may 2024, 13:48:00
     */
    ~PaillierModel();
};

#endif // PAILLIER_MODEL