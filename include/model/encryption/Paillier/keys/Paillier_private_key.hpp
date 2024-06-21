/**
 * @file Paillier_private_key.hpp
 * @brief Header of the Private key class in the Paillier cryptosystem.
 * @author Katia Auxilien
 * @date 28 may 2024, 13:55:00
 * @details The Paillier cryptosystem is a public key cryptosystem that allows for homomorphic
 * encryption of messages. The private key is used to decrypt messages that have
 * been encrypted with the corresponding public key.
 * This class represents the private key used in the Paillier cryptosystem.
 * It contains the lambda and mu values, which are necessary for decryption,
 * and the n value, which is the modulus used in the encryption process.
 */

#ifndef PAILLIER_PRIVATE_KEY
#define PAILLIER_PRIVATE_KEY

#include <cstdint>

/**
 * \brief Class representing the private key in the Paillier cryptosystem.
 * \details This class contains the lambda, mu, and n values necessary for decryption
 * in the Paillier cryptosystem. It provides getter methods for these values.
 * \author Katia Auxilien
 * \date 28 Mai 2024, 13:55:00
 */
class PaillierPrivateKey
{
public:
    /**
     * \brief Default constructor for the PaillierPrivateKey class.
     * \details Initializes lambda and mu to 0.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    PaillierPrivateKey();

    /**
     * \brief Constructor for the PaillierPrivateKey class.
     * \details Initializes lambda and mu with the given values.
     * \param l The lambda value.
     * \param m The mu value.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    PaillierPrivateKey(uint64_t l, uint64_t m);

    /**
     * \brief Constructor for the PaillierPrivateKey class.
     * \details Initializes lambda, mu, and n with the given values.
     * \param l The lambda value.
     * \param m The mu value.
     * \param nn The n value.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    PaillierPrivateKey(uint64_t l, uint64_t m, uint64_t n);

    /**
     * \brief Getter method for the lambda value.
     * \details Returns the lambda value.
     * \return The lambda value.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    uint64_t getLambda() const;

    /**
     * \brief Getter method for the mu value.
     * \details Returns the mu value.
     * \return The mu value.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    uint64_t getMu() const;
    /**
     * \brief Getter method for the n value.
     * \details Returns the n value.
     * \return The n value.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    uint64_t getN() const;

    /**
     * \brief Destructor for the PaillierPrivateKey class.
     * \details Frees any resources used by the class.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    ~PaillierPrivateKey();

private:
    uint64_t lambda; /*!< Lambda value of the private key */
    uint64_t mu;     /*!< Mu value of the private key */
    uint64_t n;      /*!< n value of the public key */
};

#endif // PAILLIER_PRIVATE_KEY