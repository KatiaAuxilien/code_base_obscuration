/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_8bit.hpp
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
#include <iostream>
#include <bitset>
#include <vector>
#include "../Paillier.hpp"

#ifndef PAILLIER_8_BIT
#define PAILLIER_8_BIT

class Paillier_8bit {
    public:

        Paillier_8bit();
        Paillier_8bit(Paillier p);
        //================ Overload ================//
        /**
         *  @overload
         *  @brief Chiffrement par paillier.
         *  @details Chiffrement par paillier d'un message m sur 8 bit.
         *  @param uint64_t n valeur p*q.
         * 	@param uint64_t g élément choisit dans l'ensemble (Z/n2Z)*.
         *  @param uint8_t m message en clair sur 8bit.
         *  @return static_cast<uint16_t>(c) : Le message m chiffré, dont le chiffré est sur 16 bit.
         *  @retval uint16_t 
         *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
         *  @date 13/05/2024
         */
        uint16_t paillierEncryption(uint64_t n, uint64_t g, uint8_t m);
        
        /**
         *  @overload
         *  @brief Chiffrement par paillier.
         *  @details Chiffrement par paillier d'un message m sur 8 bit.
         *  @param uint64_t n valeur p*q, fait partie de la clé publique.
         * 	@param uint64_t g élément choisit dans l'ensemble (Z/n2Z)*, fait partie de la clé publique.
         *  @param uint64_t r élément aléatoire appartenant à l'ensemble r ∈ (Z/nZ)*.
         *  @param uint8_t m message en clair sur 8bit.
         *  @return static_cast<uint16_t>(c) : Le message m chiffré, dont le chiffré est sur 16 bit.
         *  @retval uint16_t 
         *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
         *  @date 13/05/2024
         */
        uint16_t paillierEncryption(uint64_t n,uint64_t g, uint8_t m, uint64_t r);
        
        /**
         *  @overload
         *  @brief Déchiffrement par paillier.
         *  @details Déchiffrement par paillier d'un chiffré sur 16 bit.
         *  @param uint64_t n valeur p*q.
         * 	@param uint64_t lambda correspond au lcm(p-1,q-1), fait partie de la clé privée.
         *  @param uint64_t mu généré par la fonction generateMu_64t(...), fait partie de la clé privée.
         *  @param uint8_t c message chiffré sur 16bits.
         *  @return static_cast<uint8_t>(result) : Le message clair, déchiffré de c, sur 8 bit.
         *  @retval uint8_t 
         *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
         *  @date 13/05/2024
         */
        uint8_t paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, uint16_t c);

        ~Paillier_8bit();
    private:
        Paillier paillier;
};

#endif //PAILLIER_8_BIT