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
#include "../include/image.h"
#include "../include/image_ppm.h"
#include "../include/image_pgm.h"

#ifndef PAILLIER_CRYPTOSYSTEM
#define PAILLIER_CRYPTOSYSTEM

bool isPrime(int n, int i);

// UINT64_T

uint64_t fastMod_64t(uint64_t x, uint64_t e, uint64_t n);

uint64_t gcd_64t(uint64_t a, uint64_t b);

std::vector<long uint64_t> calc_set_same_remainder_divide_euclide_64t(uint64_t n);

uint64_t choose_g_in_vec_64t(std::vector<long uint64_t> &set, const uint64_t &n, const uint64_t &lambda);

uint64_t L_64t(uint64_t x, uint64_t n);

uint64_t lcm_64t(uint64_t a, uint64_t b);

uint64_t modInverse_64t(uint64_t a, uint64_t n);

uint64_t pow_uint64_t(uint64_t x, uint64_t n);

uint64_t paillierEncryption_64t(uint64_t n, uint64_t g, uint64_t m);
uint64_t paillierEncryption_64t(uint64_t n, uint64_t g, uint64_t m, uint64_t r);

void generateMu_64t(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n);

void generatePrivateKey_64t(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g);

uint64_t paillierDecryption_64t(uint64_t n, uint64_t lambda, uint64_t mu, uint64_t c);

///////////////////////// Opti
/* Paramètres
p : uint16_t
q : uint16_t
n : uint16_t -- finalement sur 16bit.
g : int
lambda : uint16_t
mu : int
r : uint16_t
m (pixel origin) : uint8_t
pix_enc : uint16_t
*/

int fastMod_int(int x, int e, int n);

int gcd_int(int a, int b);

long int choose_g_in_vec_int(std::vector<long int> &set, const int &n, const int &lambda);

std::vector<long int> calc_set_same_remainder_divide_euclide_int(int n);

int L_int(int x, int n);

int lcm_int(int a, int b);

int modInverse_int(int a, int n);

uint16_t paillierEncryption_8t(int n, long int g, uint8_t m);

uint16_t paillierEncryption_8t_r(int n, long int g, uint8_t m, int r);

void generateMu_int(int &mu, const int &g, const int &lambda, const int &n);

void generatePrivateKey_int(int &lambda, int &mu, const int &p, const int &q, const int &n, const long int &g);

uint8_t paillierDecryption_16t(int n, int lambda, int mu, uint16_t c);

uint8_t paillierDecryption_8t(int n, int lambda, int mu, uint8_t c);

#endif // PAILLIER_CRYPTOSYSTEM