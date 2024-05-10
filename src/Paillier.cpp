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
#include "../include/Paillier.hpp"
#include <numeric>
#define BITSETSIZE 64

using namespace std;

bool isPrime(int n, int i = 2)
{
	if (n <= 2)
		return (n == 2) ? true : false;
	if (n % i == 0)
		return false;
	if (i * i > n)
		return true;

	return isPrime(n, i + 1);
}

/////////////////// UINT64_T

uint64_t fastMod(uint64_t x, uint64_t e, uint64_t n)
{
	uint64_t c = 1;
	bitset<BITSETSIZE> bits = bitset<BITSETSIZE>(e);

	for (int i = BITSETSIZE - 1; i >= 0; i--)
	{
		c = c * c % n;
		if (bits[i] & 1)
			c = c * x % n;
	}

	return c;
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
uint64_t gcd(uint64_t a, uint64_t b)
{
	if (b == 0)
	{
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
std::vector<long uint64_t> calc_set_same_remainder_divide_euclide(uint64_t n)
{
	std::vector<long uint64_t> result;
	for (uint64_t i = 0; i < n; i++)
	{
		if (gcd(i, n) == 1)
		{
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
uint64_t choose_g_in_vec(std::vector<long uint64_t> &set, const uint64_t &n, const uint64_t &lambda)
{
	uint64_t x;
	int i_position = 0;
	uint64_t g = 0, r = 1, r2 = 1;
	while (r != 0 && r2 != 0)
	{
		i_position = rand() % set.size();
		g = set.at(i_position);
		x = fastMod(g, lambda, n * n);
		r = (x - 1) % n;
		r2 = (x - 1) / n;
	}
	return g;
}

uint64_t L(uint64_t x, uint64_t n)
{
	return (x - 1) / n;
}

// least common multiple
uint64_t lcm(uint64_t a, uint64_t b)
{
	return a * b / gcd(a, b);
}

uint64_t modInverse(uint64_t a, uint64_t n)
{
	a = a % n;
	for (uint64_t x = 1; x < n; x++)
	{
		if ((a * x) % n == 1)
			return x;
	}

	return 0;
}

uint64_t pow_uint64_t(uint64_t x, uint64_t n)
{
	if (n == 0)
	{
		return 1;
	}
	return x * pow_uint64_t(x, n - 1);
}

uint64_t paillierEncryption(uint64_t n, uint64_t g, uint64_t m)
{
	uint64_t c;
	uint64_t r = rand() % n;
	while (gcd(r, n) != 1 || r == 0)
	{
		r = rand() % n;
	}

	uint64_t fm1 = fastMod(g, m, n * n);
	uint64_t fm2 = fastMod(r, n, n * n);
	c = (fm1 * fm2) % (n * n); // (a+b)%n = (a%n + b%n) % n

	return c;
}
uint64_t paillierEncryption(uint64_t n, uint64_t g, uint64_t m, uint64_t r)
{
	uint64_t c;
	
	// c = ((pow_uint64_t(g,m))*(pow_uint64_t(r,n)) ) % (n * n);

	uint64_t fm1 = fastMod(g, m, n * n);
	uint64_t fm2 = fastMod(r, n, n * n);
	c = (fm1 * fm2) % (n * n); // (a+b)%n = (a%n + b%n) % n

	return c;
}

void generateMu(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n)
{
	uint64_t u = fastMod(g, lambda, n * n);
	uint64_t l = (u - 1) / n;
	mu = modInverse(l, n);
}

void generatePrivateKey(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g)
{
	lambda = lcm(p - 1, q - 1);

	generateMu(mu, g, lambda, n);
}

uint64_t paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, uint64_t c)
{
	return (((fastMod(c, lambda, n * n) - 1) / n) * mu) % n;
}

///////////////////////// Opti
/* Paramètres
p : uint8_t
q : uint8_t
n : uint8_t
g : int 
lambda : int
mu : int
r : uint8_t
m (pixel origin) : uint8_t
pix_enc : uint16_t
*/

int fastMod(int x, uint16_t e, uint16_t n){
	int c = 1;
	bitset<16> bits = bitset<16>(e);

	for (int i = 16 - 1; i >= 0; i--)
	{
		c = c * c % n;
		if (bits[i] & 1)
			c = c * x % n;
	}

	return c;
}
int fastMod(int x, uint16_t e, uint32_t n){
	int c = 1;
	bitset<32> bits = bitset<32>(e);

	for (int i = 32 - 1; i >= 0; i--)
	{
		c = c * c % n;
		if (bits[i] & 1)
			c = c * x % n;
	}

	return c;
}

int fastMod(uint16_t x, uint16_t e, uint32_t n){
	int c = 1;
	bitset<16> bits = bitset<16>(e);

	for (int i = 16 - 1; i >= 0; i--)
	{
		c = c * c % n;
		if (bits[i] & 1)
			c = c * x % n;
	}

	return c;
}

uint8_t gcd(uint16_t a, uint16_t b){
	if (b == 0)
	{
		return a;
	}
	return gcd(b, a % b);
}

std::vector<int> calc_set_same_remainder_divide_euclide_g(int n)
{
	std::vector<int> result;
	for (int i = 0; i < n; i++)
	{
		if (gcd(i, n) == 1)
		{
			result.push_back(i);
		}
	}
	return result;
}
std::vector<uint16_t> calc_set_same_remainder_divide_euclide_r(int n){
	std::vector<uint16_t> result;
	for (uint16_t i = 0; i < n; i++)
	{
		if (gcd(i, n) == 1)
		{
			result.push_back(i);
		}
	}
	return result;
}

int choose_g_in_vec(std::vector<int> &set, const uint16_t &n, const uint16_t &lambda){
	int x;
	int i_position = 0;
	int g = 0, r = 1, r2 = 1;
	while (r != 0 && r2 != 0)
	{
		i_position = rand() % set.size();
		g = set.at(i_position);
		x = fastMod(g, lambda, (uint32_t) n * n);
		r = (x - 1) % n;
		r2 = (x - 1) / n;
	}
	return g;
}

int L(int x, uint16_t n)
{
	return (x - 1) / n;
}

uint16_t lcm(uint16_t a, uint16_t b){
	return a * b / gcd(a, b);
}

int modInverse(uint16_t a, uint16_t n){
	a = a % n;
	for (uint16_t x = 1; x < n; x++)
	{
		if ((a * x) % n == 1)
			return x;
	}
	return 0;
}

uint16_t paillierEncryption(uint16_t n, int g, uint8_t m)
{
	uint16_t c;
	uint8_t r = rand() % n;
	while (gcd(r, n) != 1 || r == 0)
	{
		r = rand() % n;
	}

	int fm1 = fastMod(g, m, (uint32_t) n * n);
	int fm2 = fastMod(r, n, (uint32_t) n * n);
	c = (fm1 * fm2) % ((uint32_t) n * n); // (a+b)%n = (a%n + b%n) % n

	return c;
}
uint16_t paillierEncryption(uint16_t n, int g, uint8_t m, uint16_t r){
	uint16_t c;
	int fm1 = fastMod(g, m, (uint16_t) n * n);
	int fm2 = fastMod(r, n, (uint16_t) n * n);
	c = (fm1 * fm2) % ((uint16_t) n * n);
	return c;
}

void generateMu(int &mu, const int &g, const uint16_t &lambda, const uint16_t &n)
{
	int u = fastMod(g, lambda, (uint32_t) n * n);
	uint16_t l = (u - 1) / n;
	mu = modInverse(l, n);
}

void generatePrivateKey(uint16_t &lambda, int &mu, const uint16_t &p, const uint16_t &q, const uint16_t &n, const int &g)
{
	lambda = lcm(p - 1, q - 1);
	generateMu(mu, g, lambda, n);
}

uint8_t paillierDecryption(uint16_t n, uint16_t lambda, int mu, uint16_t c)
{
	return (((fastMod(c, lambda, (uint32_t)n * n) - 1) / n) * mu) % n;
}