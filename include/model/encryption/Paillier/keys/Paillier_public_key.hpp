/**
 * @file Paillier_public_key.hpp
 * @brief Header of the Public key in the Paillier cryptosystem.
 * @author Katia Auxilien
 * @date 28 may 2024, 13:55:00
 * @details  This class represents the public key used in the Paillier cryptosystem.
 * It contains the n value, which is the modulus used in the encryption process,
 * and the g value, which is a generator used in the encryption process.
 */
#ifndef PAILLIER_PUBLIC_KEY
#define PAILLIER_PUBLIC_KEY

#include <cstdint>

/**
 * \class PaillierPublicKey
 * \brief Class representing the public key in the Paillier cryptosystem.
 * \details This class contains the n and g values necessary for encryption
 * in the Paillier cryptosystem. It provides getter methods for these values.
 * \author Katia Auxilien
 * \date 28 Mai 2024, 13:55:00
 */
class PaillierPublicKey
{
public:
    /**
     * \brief Default constructor for the PaillierPublicKey class.
     * \details Initializes n and g to 0.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    PaillierPublicKey();
    /**
     * \brief Constructor for the PaillierPublicKey class.
     * \details Initializes n and g with the given values.
     * \param N The n value.
     * \param G The g value.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    PaillierPublicKey(uint64_t n, uint64_t g);

    /**
     * \brief Getter method for the n value.
     * \details Returns the n value.
     * \return The n value.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    uint64_t getN() const;
    /**
     * \brief Getter method for the g value.
     * \details Returns the g value.
     * \return The g value.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    uint64_t getG() const;
    /**
     * \brief Destructor for the PaillierPublicKey class.
     * \details Frees any resources used by the class.
     * \author Katia Auxilien
     * \date 28 Mai 2024, 13:55:00
     */
    ~PaillierPublicKey();

private:
    uint64_t n; /*!< n value of the public key */
    uint64_t g; /*!< g value of the public key g ∈ Z/n2Z* */
};
#endif // PAILLIER_PUBLIC_KEY
