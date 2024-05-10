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

//UINT64_T

uint64_t fastMod(uint64_t x, uint64_t e, uint64_t n);

uint64_t gcd(uint64_t a, uint64_t b);

std::vector<long uint64_t> calc_set_same_remainder_divide_euclide(uint64_t n);

uint64_t choose_g_in_vec(std::vector<long uint64_t> &set, const uint64_t &n, const uint64_t &lambda);

uint64_t L(uint64_t x, uint64_t n);

uint64_t lcm(uint64_t a, uint64_t b);

uint64_t modInverse(uint64_t a, uint64_t n);

uint64_t pow_uint64_t(uint64_t x, uint64_t n);

uint64_t paillierEncryption(uint64_t n, uint64_t g, uint64_t m);
uint64_t paillierEncryption(uint64_t n, uint64_t g, uint64_t m, uint64_t r);

void generateMu(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n);

void generatePrivateKey(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g);

uint64_t paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, uint64_t c);

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

int fastMod(int x, uint16_t e, uint16_t n);
int fastMod(int x, uint16_t e, uint32_t n);
int fastMod(uint16_t x, uint16_t e, uint32_t n)

uint8_t gcd(uint16_t a, uint16_t b);

std::vector<int> calc_set_same_remainder_divide_euclide_g(int n);
std::vector<uint16_t> calc_set_same_remainder_divide_euclide_r(int n);

int choose_g_in_vec(std::vector<int> &set, const uint16_t &n, const int &lambda);

int L(int x, uint16_t n);

uint8_t lcm(uint16_t a, uint16_t b);

int modInverse(uint16_t a, uint16_t n);

uint16_t paillierEncryption(uint16_t n, int g, uint8_t m);
uint16_t paillierEncryption(uint16_t n, int g, uint8_t m, uint16_t r);

void generateMu(int &mu, const int &g, const uint16_t &lambda, const uint16_t &n);

void generatePrivateKey(uint16_t &lambda, int &mu, const uint16_t &p, const uint16_t &q, const uint16_t &n, const int &g);

uint8_t paillierDecryption(uint16_t n, uint16_t lambda, int mu, uint16_t c);

#endif // PAILLIER_CRYPTOSYSTEM