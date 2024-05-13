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

uint64_t fastMod_64t(uint64_t x, uint64_t e, uint64_t n)
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
uint64_t gcd_64t(uint64_t a, uint64_t b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd_64t(b, a % b);
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
std::vector<long uint64_t> calc_set_same_remainder_divide_euclide_64t(uint64_t n)
{
	std::vector<long uint64_t> result;
	for (uint64_t i = 0; i < n; i++)
	{
		if (gcd_64t(i, n) == 1)
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
uint64_t choose_g_in_vec_64t(std::vector<long uint64_t> &set, const uint64_t &n, const uint64_t &lambda)
{
	uint64_t x;
	int i_position = 0;
	uint64_t g = 0, r = 1, r2 = 1;
	while (r != 0 && r2 != 0)
	{
		i_position = rand() % set.size();
		g = set.at(i_position);
		x = fastMod_64t(g, lambda, n * n);
		r = (x - 1) % n;
		r2 = (x - 1) / n;
	}
	return g;
}

uint64_t L_64t(uint64_t x, uint64_t n)
{
	return (x - 1) / n;
}

// least common multiple
uint64_t lcm_64t(uint64_t a, uint64_t b)
{
	return a * b / gcd_64t(a, b);
}

uint64_t modInverse_64t(uint64_t a, uint64_t n)
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

uint64_t paillierEncryption_64t(uint64_t n, uint64_t g, uint64_t m)
{
	uint64_t c;
	uint64_t r = rand() % n;
	while (gcd_64t(r, n) != 1 || r == 0)
	{
		r = rand() % n;
	}

	uint64_t fm1 = fastMod_64t(g, m, n * n);
	uint64_t fm2 = fastMod_64t(r, n, n * n);
	c = (fm1 * fm2) % (n * n); // (a+b)%n = (a%n + b%n) % n

	return c;
}
uint64_t paillierEncryption_64t(uint64_t n, uint64_t g, uint64_t m, uint64_t r)
{
	uint64_t c;

	// c = ((pow_uint64_t(g,m))*(pow_uint64_t(r,n)) ) % (n * n);

	uint64_t fm1 = fastMod_64t(g, m, n * n);
	uint64_t fm2 = fastMod_64t(r, n, n * n);
	c = (fm1 * fm2) % (n * n); // (a+b)%n = (a%n + b%n) % n

	return c;
}

void generateMu_64t(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n)
{
	uint64_t u = fastMod_64t(g, lambda, n * n);
	uint64_t l = (u - 1) / n;
	mu = modInverse_64t(l, n);
}

void generatePrivateKey_64t(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g)
{
	lambda = lcm_64t(p - 1, q - 1);

	generateMu_64t(mu, g, lambda, n);
}

uint64_t paillierDecryption_64t(uint64_t n, uint64_t lambda, uint64_t mu, uint64_t c)
{
	return (((fastMod_64t(c, lambda, n * n) - 1) / n) * mu) % n;
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

#define BITSETSIZE2 32

int fastMod_int(int x, int e, int n)
{
	int c = 1;
	bitset<BITSETSIZE2> bits = bitset<BITSETSIZE2>(e);

	for (int i = BITSETSIZE2 - 1; i >= 0; i--)
	{
		c = c * c % n;
		if (bits[i] & 1)
			c = c * x % n;
	}

	return c;
}

int gcd_int(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd_int(b, a % b);
}


long int choose_g_in_vec_int(std::vector<long int> &set, const int &n, const int &lambda)
{
	int x;
	int i_position = 0;
	int g = 0, r = 1, r2 = 1;
	while (r != 0 && r2 != 0)
	{
		i_position = rand() % set.size();
		g = set.at(i_position);
		x = fastMod_int(g, lambda, n * n);
		r = (x - 1) % n;
		r2 = (x - 1) / n;
	}
	return g;
}

/**
 *  @brief
 *  @param
 *  @authors Katia Auxilien
 *  @date 13/05/2024 10:08:00
 *
 *  Calcul de l'ensemble des éléments de  g ∈ (Z/n2Z)*
 *
 *  @details
 */
std::vector<long int> calc_set_same_remainder_divide_euclide_int(int n)
{
	std::vector<long int> result;
	for (int i = 0; i < n; i++)
	{
		if (gcd_int(i, n) == 1)
		{
			result.push_back(i);
		}
	}
	return result;
}

int L_int(int x, int n)
{
	return (x - 1) / n;
}

int lcm_int(int a, int b)
{
	return a * b / gcd_int(a, b);
}

int modInverse_int(int a, int n)
{
	a = a % n;
	for (int x = 1; x < n; x++)
	{
		if ((a * x) % n == 1)
			return x;
	}
	return 0;
}

uint16_t paillierEncryption_8t(int n, long int g, uint8_t m)
{
	int c;
	int r = rand() % n;
	while (gcd_int(r, n) != 1 || r == 0)
	{
		r = rand() % n;
	}

	int fm1 = fastMod_int(g, m, n * n);
	int fm2 = fastMod_int(r, n, n * n);
	c = (fm1 * fm2) % (n * n);

	return (uint16_t) c;
}

uint16_t paillierEncryption_8t_r(int n,long int g, uint8_t m, int r)
{
	int c;
	int fm1 = fastMod_int(g, m, n * n);
	int fm2 = fastMod_int(r, n, n * n);
	c = (fm1 * fm2) % (n * n);
	return (uint16_t) c;
}

void generateMu_int(int &mu, const long int &g, const int &lambda, const int &n)
{
	int u = fastMod_int(g, lambda, n * n);
	int l = (u - 1) / n;
	mu = modInverse_int(l, n);
}

void generatePrivateKey_int(int &lambda, int &mu, const int &p, const int &q, const int &n, const long int &g)
{
	lambda = lcm_int(p - 1, q - 1);
	generateMu_int(mu, g, lambda, n);
}

uint8_t paillierDecryption_16t(int n, int lambda, int mu, uint16_t c)
{
	return (((fastMod_int(c, lambda, n * n) - 1) / n) * mu) % n;
}

uint8_t paillierDecryption_8t(int n, int lambda, int mu, uint8_t c)
{
	return (((fastMod_int(c, lambda, n * n) - 1) / n) * mu) % n;
}