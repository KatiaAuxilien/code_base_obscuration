/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier.hpp
 *
 * Description :
 *   Fichier source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024 - Mai 2024
 *
 *******************************************************************************/
#include <iostream>
#include <bitset>
#include <vector>
#include "../../../include/image/image_pgm.hpp"

#ifndef PAILLIER_CRYPTOSYSTEM
#define PAILLIER_CRYPTOSYSTEM

class Paillier
{
public:
    Paillier();

    /**
     *  @brief Calcul de l'exponentiation modulaire rapide.
     *  @details Calcul de l'exponentiation modulaire rapide.
     *  @param uint64_t x
     *  @param uint64_t i
     * 	@param uint64_t n
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    uint64_t fastMod_64t(uint64_t x, uint64_t e, uint64_t n);

    /**
     *  @brief Calcul du PGCD en récursif.
     *  @details Calcul du PGCD en récursif, de a et b sur 64 bit.
     *  @param uint64_t a
     * 	@param uint64_t b
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    uint64_t gcd_64t(uint64_t a, uint64_t b);

    /**
     *  @brief
     *  @details Calcul de l'ensemble des éléments de  g ∈ (Z/n2Z)*
     *  @param
     *  @authors Katia Auxilien
     *  @date 30/04/2024 15:51:00
     */
    std::vector<uint64_t> calc_set_same_remainder_divide_euclide_64t(uint64_t n);

    /**
     *  @brief
     *  @details Choix de g tant que (x - 1)/n ne donne pas un L(x) entier.
     *  @param
     *  @authors Katia Auxilien
     *  @date 02/05/2024
     */
    uint64_t choose_g_in_vec_64t(std::vector<uint64_t> &set, const uint64_t &n, const uint64_t &lambda);

    /**
     *  @brief Calcul de L(x).
     *  @details Calcul de L(x) nécessaire dans la génération de Mu et le déchiffrement par Paillier.
     *  @param uint64_t x
     * 	@param uint64_t n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    uint64_t L_64t(uint64_t x, uint64_t n);

    /**
     *  @brief Calcul du plus petit diviseur commun.
     *  @details Calcul du plus petit diviseur commun de a et b.
     *  @param uint64_t a
     * 	@param uint64_t b
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    uint64_t lcm_64t(uint64_t a, uint64_t b);

    /**
     *  @brief Calcul de l'inverse modulaire de a modulo n.
     *  @details Calcul de l'inverse modulaire de a modulo n sur 64 bit.
     *  @param uint64_t a
     * 	@param uint64_t n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    uint64_t modInverse_64t(uint64_t a, uint64_t n);

    /**
     *  @brief Calcul de la puissance de n de x
     *  @details Calcul de la puissance de n de x en récursif.
     *  @param uint64_t x
     * 	@param uint64_t n
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    uint64_t pow_uint64_t(uint64_t x, uint64_t n);

    /**
     *  @brief Génération du Mu.
     *  @details Génération du paramètre Mu nécessaire à la clé privée du chiffrement par Paillier.
     *  @param uint64_t &mu
     * 	@param const uint64_t &g
     *  @param const uint64_t &lambda
     *  @param const uint64_t &n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    void generateMu_64t(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n);

    /**
     *  @brief Génération de la clé privée du chiffrement par Paillier.
     *  @details Génération de la clé privée du chiffrement par Paillier avec des paramètres sur 64 bit.
     *  @param uint64_t &lambda
     * 	@param uint64_t &mu
     *  @param const uint64_t &p
     *  @param const uint64_t &q
     *  @param const uint64_t &n
     *  @param const uint64_t &g
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    void generatePrivateKey_64t(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g);

    //================ Overload and Generic programming ================//
    /**
     *  @overload
     *  @brief Chiffrement par paillier.
     *  @details Chiffrement par paillier d'un message m sur n bit.
     *  @param uint64_t n valeur p*q.
     * 	@param uint64_t g élément choisit dans l'ensemble (Z/n2Z)*.
     *  @param uintN_t m message en clair sur n bit.
     *  @return static_cast<uintN_t>(c) : Le message m chiffré, dont le chiffré est sur 2*n bit.
     *  @retval uintN_t
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
     */
    template <typename uintN_t>
    uint64_t paillierEncryption(uint64_t n, uint64_t g, uintN_t m);

    /**
     *  @overload
     *  @brief Chiffrement par paillier.
     *  @details Chiffrement par paillier d'un message m sur n bit.
     *  @param uint64_t n valeur p*q, fait partie de la clé publique.
     * 	@param uint64_t g élément choisit dans l'ensemble (Z/n2Z)*, fait partie de la clé publique.
     *  @param uint64_t r élément aléatoire appartenant à l'ensemble r ∈ (Z/nZ)*.
     *  @param uintN_t m message en clair sur nbit.
     *  @return static_cast<uintN_t>(c) : Le message m chiffré, dont le chiffré est sur 2*n bit.
     *  @retval uintN_t
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
     */
    template <typename uintN_t>
    uint64_t paillierEncryption(uint64_t n, uint64_t g, uintN_t m, uint64_t r);

    /**
     *  @overload
     *  @brief Déchiffrement par paillier.
     *  @details Déchiffrement par paillier d'un chiffré sur 2*n bit.
     *  @param uint64_t n valeur p*q.
     * 	@param uint64_t lambda correspond au lcm(p-1,q-1), fait partie de la clé privée.
     *  @param uint64_t mu généré par la fonction generateMu_64t(...), fait partie de la clé privée.
     *  @param uintN_t c message chiffré sur 2*nbits.
     *  @return static_cast<uintN_t>(result) : Le message clair, déchiffré de c, sur n bit.
     *  @retval uintN_t
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
     */
    template <typename uintN_t>
    uint64_t paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, uintN_t c);

    ~Paillier();
};

#endif // PAILLIER_CRYPTOSYSTEM