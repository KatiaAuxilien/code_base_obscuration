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
	uint64_t c = 1;
	bitset<BITSETSIZE> bits = bitset<BITSETSIZE>(e);

	for (int i = BITSETSIZE - 1; i >= 0; i--) {
		c = c * c % n;
		if (bits[i] & 1) c = c * x % n;
	}

	return c;
}

// Greatest common divisor
// uint64_t gcd(uint64_t a, uint64_t b) {
// 	uint64_t q, r;		// quotient, remainder

// 	while (b > 0) {
// 		q = a / b;		// the integer
// 		r = a - q * b;	// the modulo
// 		a = b;
// 		b = r;
// 	}

// 	return a;
// }


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
  for (int i = 0; i < n; i++) {
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
	int i = 0;
	uint64_t g, r,r2;
	while(r != 0 && r2 !=0 ){ //Est-ce que ça pose problème d'avoir en soi toujours le même g avec les mêmes p et q ? Est-ce qu'il faut ajouter de l'aléatoire ?
		g = set.at(i); // int i_position_e = rand() % e.size();
		x = fastMod(g, lambda, n * n);
		r = (x - 1) % n;
		r2 = (x - 1) / n;
		i++;
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
	a = a % n;
	for (uint64_t x = 1; x < n; x++) {
		if ((a * x) % n == 1)
			return x;
	}

	return 0;
}

uint64_t paillierEncryption(uint64_t n, uint64_t g, uint64_t m) {
	uint64_t c;

	uint64_t r = rand() % n;

	while (gcd(r, n) != 1 || r == 0) {
		r = rand() % n;
	}

	uint64_t fm1 = fastMod(g, m, n * n);
	uint64_t fm2 = fastMod(r, n, n * n);

	c = (fm1 * fm2) % (n * n);		// (a+b)%n = (a%n + b%n) % n

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
	return ((fastMod(c, lambda, n * n) - 1) / n) * mu % n;
}
