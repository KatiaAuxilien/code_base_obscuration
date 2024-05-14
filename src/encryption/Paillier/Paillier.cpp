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
#include "../../../include/encryption/Paillier/Paillier.hpp"
#include <numeric>
#include <climits>
#include <random>

#define BITSETSIZE 64

using namespace std;

Paillier::Paillier(){};

uint64_t Paillier::fastMod_64t(uint64_t x, uint64_t e, uint64_t n)
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

uint64_t Paillier::gcd_64t(uint64_t a, uint64_t b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd_64t(b, a % b);
}

std::vector<uint64_t> Paillier::calc_set_same_remainder_divide_euclide_64t(uint64_t n)
{
	std::vector<uint64_t> result;
	for (uint64_t i = 0; i < n; i++)
	{
		if (gcd_64t(i, n) == 1)
		{
			result.push_back(i);
		}
	}
	return result;
}

uint64_t Paillier::choose_g_in_vec_64t(std::vector<uint64_t> &set, const uint64_t &n, const uint64_t &lambda)
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

uint64_t Paillier::L_64t(uint64_t x, uint64_t n)
{
	return (x - 1) / n;
}

uint64_t Paillier::lcm_64t(uint64_t a, uint64_t b)
{
	return a * b / gcd_64t(a, b);
}

uint64_t Paillier::modInverse_64t(uint64_t a, uint64_t n)
{
	a = a % n;
	for (uint64_t x = 1; x < n; x++)
	{
		if ((a * x) % n == 1)
			return x;
	}

	return 0;
}

uint64_t Paillier::pow_uint64_t(uint64_t x, uint64_t n)
{
	if (n == 0)
	{
		return 1;
	}
	return x * pow_uint64_t(x, n - 1);
}

void Paillier::generateMu_64t(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n)
{
	uint64_t u = fastMod_64t(g, lambda, n * n);
	uint64_t l = (u - 1) / n;
	mu = modInverse_64t(l, n);
}

void Paillier::generatePrivateKey_64t(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g)
{
	lambda = lcm_64t(p - 1, q - 1);

	generateMu_64t(mu, g, lambda, n);
}

uint16_t Paillier::paillierEncryption_8t(uint64_t n, uint64_t g, uint8_t m){
    uint64_t c;
    uint64_t r = rand() % n;
    while (gcd_64t(r, n) != 1 || r == 0)
    {
        r = rand() % n;
    }

    uint64_t fm1 = fastMod_64t(g, m, n * n);
    uint64_t fm2 = fastMod_64t(r, n, n * n);
    c = (fm1 * fm2) % (n * n);

    // Vérifier que le résultat peut être stocké dans un uint16_t
    if (c >= std::numeric_limits<uint16_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 16 bits.");
    }

    return static_cast<uint16_t>(c);
}

uint16_t Paillier::paillierEncryption_8tr(uint64_t n,uint64_t g, uint8_t m, uint64_t r)
{
    uint64_t c;

    uint64_t fm1 = fastMod_64t(g, m, n * n);
    uint64_t fm2 = fastMod_64t(r, n, n * n);
    c = (fm1 * fm2) % (n * n);

    // Vérifier que le résultat peut être stocké dans un uint16_t
    if (c >= std::numeric_limits<uint16_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 16 bits.");
    }

    return static_cast<uint16_t>(c);
}

uint8_t Paillier::paillierDecryption_16t(uint64_t n, uint64_t lambda, uint64_t mu, uint16_t c)
{
    uint64_t result = (((fastMod_64t(c, lambda, n * n) - 1) / n) * mu) % n;

    // Vérifier que le résultat peut être stocké dans un uint8_t
    if (result >= std::numeric_limits<uint8_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 8 bits.");
    }

    return static_cast<uint8_t>(result);
}

uint8_t Paillier::paillierDecryption_8t(uint64_t n, uint64_t lambda, uint64_t mu, uint8_t c)
{
    uint64_t result = (((fastMod_64t(c, lambda, n * n) - 1) / n) * mu) % n;

    // Vérifier que le résultat peut être stocké dans un uint8_t
    if (result >= std::numeric_limits<uint8_t>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 8 bits.");
    }

    return static_cast<uint8_t>(result);
}

Paillier::~Paillier() {}
