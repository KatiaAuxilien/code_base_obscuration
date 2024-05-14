/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier.h
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
#include "../../../include/image/image_pgm.h"

#ifndef PAILLIER_CRYPTOSYSTEM
#define PAILLIER_CRYPTOSYSTEM

class Paillier
{
    public:
        Paillier();
        uint64_t fastMod_64t(uint64_t x, uint64_t e, uint64_t n);
        uint64_t gcd_64t(uint64_t a, uint64_t b);
        std::vector<uint64_t> calc_set_same_remainder_divide_euclide_64t(uint64_t n);
        uint64_t choose_g_in_vec_64t(std::vector<uint64_t> &set, const uint64_t &n, const uint64_t &lambda);
        uint64_t L_64t(uint64_t x, uint64_t n);
        uint64_t lcm_64t(uint64_t a, uint64_t b);
        uint64_t modInverse_64t(uint64_t a, uint64_t n);
        uint64_t pow_uint64_t(uint64_t x, uint64_t n);
        void generateMu_64t(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n);
        void generatePrivateKey_64t(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g);
        uint16_t paillierEncryption_8t(uint64_t n, uint64_t g, uint8_t m);
        uint16_t paillierEncryption_8t_r(uint64_t n,uint64_t g, uint8_t m, uint64_t r);
        uint8_t paillierDecryption_16t(uint64_t n, uint64_t lambda, uint64_t mu, uint16_t c);
        uint8_t paillierDecryption_8t(uint64_t n, uint64_t lambda, uint64_t mu, uint8_t c);
        ~Paillier();
};

#endif // PAILLIER_CRYPTOSYSTEM