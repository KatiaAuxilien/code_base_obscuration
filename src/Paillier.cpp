/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier.cpp
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
#include "../include/Paillier.h"

#define BITSETSIZE 64

using namespace std;

bool isPrime(int n, int i = 2)
{
	if (n <= 2) return (n == 2) ? true : false;
	if (n % i == 0) return false;
	if (i * i > n)
	return true;

	return isPrime(n, i + 1);
}


uint64_t fastMod(uint64_t x, uint64_t e, uint64_t n) {
    uint64_t result = 1;
    x %= n;
    while (e > 0) {
        if (e & 1) result = (result * x) % n;
        x = (x * x) % n;
        e >>= 1;
    }
    return result;
}

/**
 *  @brief 
 *  @param 
 *  @authors Katia Auxilien
 *  @date 30/04/2024 15:51:00
 * 
 *  Calcul du PGCD en récursif.
 *
 *  @details 
 */
uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

/**
 *  @brief 
 *  @param 
 *  @authors Katia Auxilien
 *  @date 30/04/2024 15:51:00
 * 
 *  Calcul de l'ensemble des éléments de  g ∈ (Z/n2Z)*
 *
 *  @details 
 */
std::vector<long uint64_t> calc_set_same_remainder_divide_euclide(uint64_t n) {
  std::vector<long uint64_t> result;
  for (uint64_t i = 0; i < n; i++) {
    if (gcd(i, n) == 1) {
      result.push_back(i);
    }
  }
  return result;
}

/**
 *  @brief 
 *  @param 
 *  @authors Katia Auxilien
 *  @date 02/05/2024
 * 
 *  Choix de g tant que (x - 1)/n ne donne pas un L(x) entier. 
 *
 *  @details 
 */
uint64_t choose_g_in_vec(std::vector<long uint64_t>& set, const uint64_t& n, const uint64_t& lambda){
	uint64_t x;
	int i_position = 0;
	uint64_t g = 0, r = 1, r2=1;
	while(r != 0 && r2 != 0){
		i_position = rand() % set.size();
		g = set.at(i_position);
		x = fastMod(g, lambda, n * n);
		r = (x - 1) % n;
		r2 = (x - 1) / n;
	}
	return g;
}

uint64_t L(uint64_t x, uint64_t n) {
	return (x - 1) / n;
}

// least common multiple
uint64_t lcm(uint64_t a, uint64_t b) {
	return a * b / gcd(a, b);
}

uint64_t modInverse(uint64_t a, uint64_t n) {
    uint64_t b = n, u = 1, v = 0;
    while (a > 0) {
        uint64_t q = b / a;
        uint64_t t = a; a = b % a; b = t;
        t = u; u = v - q * u; v = t;
    }
    return (v + n) % n;
}

uint64_t generate_rand_r(uint64_t n){
	std::vector<long uint64_t> set = calc_set_same_remainder_divide_euclide(n);
	
	uint64_t r = set.at(rand() % set.size());
	
	return r;
}

uint64_t pow_uint64_t(uint64_t x, uint64_t n){
	if(n == 0){
		return 1;
	}
	return x * pow_uint64_t(x,n-1);
}

uint64_t paillierEncryption(uint64_t n, uint64_t g, uint64_t m) {
	uint64_t c;
	uint64_t r = generate_rand_r(n);
	c = ((pow_uint64_t(g,m))*(pow_uint64_t(r,n)) ) % (n * n);	

	return c;
}

void generateMu(uint64_t& mu, const uint64_t& g, const uint64_t& lambda, const uint64_t& n) {
	uint64_t u = fastMod(g, lambda, n * n);
	uint64_t l = (u - 1) / n;
	mu = modInverse(l, n);
}

void generatePrivateKey(uint64_t& lambda, uint64_t& mu, const uint64_t& p, const uint64_t& q, const uint64_t& n, const uint64_t& g) {
	lambda = lcm(p - 1, q - 1);

	generateMu(mu, g, lambda, n);
}

uint64_t paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, uint64_t c) {
	return (((fastMod(c, lambda, n * n) - 1) / n) * mu) % n;
}