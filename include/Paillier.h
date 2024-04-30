#include <iostream>
#include <bitset>
#include <vector>
#include "../include/image.h"
#include "../include/image_ppm.h"
#include "../include/image_pgm.h"

#ifndef PAILLIER_CRYPTOSYSTEM
#define PAILLIER_CRYPTOSYSTEM

bool isPrime(int n, int i);

uint64_t fastMod(uint64_t x, uint64_t e, uint64_t n);

uint64_t gcd(uint64_t a, uint64_t b);

std::vector<int> calc_set_same_remainder_divide_euclide(int n);

uint64_t L(uint64_t x, uint64_t n);

uint64_t lcm(uint64_t a, uint64_t b);

uint64_t modInverse(uint64_t a, uint64_t n);

uint64_t paillierEncryption(uint64_t n, uint64_t g, uint64_t m);

void generateMu(uint64_t& mu, const uint64_t& g, const uint64_t& lambda, const uint64_t& n);

void generatePrivateKey(uint64_t& lambda, uint64_t& mu, const uint64_t& p, const uint64_t& q, const uint64_t& n, const uint64_t& g);

uint64_t paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, uint64_t c);

#endif //PAILLIER_CRYPTOSYSTEM