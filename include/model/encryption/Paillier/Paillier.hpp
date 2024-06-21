/**
 * \file Paillier.hpp
 * \brief This file contains the Paillier cryptosystem implementation in
 * C++.
 * \author Katia Auxilien
 * \date Avril 2024 - Mai 2024
 * \details The Paillier cryptosystem is an additive homomorphic encryption scheme
 * that allows computations to be performed on encrypted data without decrypting it.
 * File source is Paillier_image.cpp by Bianca Jansen Van Rensburg
 */
#define BITSETSIZE 64

#ifndef PAILLIER_CRYPTOSYSTEM
#define PAILLIER_CRYPTOSYSTEM

#include <iostream>
#include <bitset>
#include <vector>
#include <random> //Randomdevice and mt19937

using namespace std;

/**
 * \class Paillier
 * \brief This class implements the Paillier cryptosystem.
 * \tparam T_in The input data type.
 * \tparam T_out The output data type.
 * \author Katia Auxilien
 * \date April 2024 - May 2024
 */
template <typename T_in, typename T_out>
class Paillier
{
public:
    /**
     * \brief Construct a new Paillier object
     * \author Katia Auxilien
     * \date April 2024 - May 2024
     */
    Paillier(){};

    /**
     * \brief Destroy the Paillier object
     *
     * \author Katia Auxilien
     * \date April 2024 - May 2024
     */
    ~Paillier(){};

    /**
     *  \brief Generate a random 64-bit unsigned integer.
     * \details This function generates a random 64-bit unsigned integer between a given range using the Mersenne Twister algorithm.
     * \param uint64_t min - The minimum value of the range.
     * \param uint64_t max - The maximum value of the range.
     * \return uint64_t - A random 64-bit unsigned integer between min and max.
     *  \author Katia Auxilien
     *  \date 23 May 2024
     */
    uint64_t random64(uint64_t min, uint64_t max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<std::uint64_t> dis(min, max);
        return dis(gen);
    }

    /**
     *  \brief Calculate the modular exponentiation of a base raised to a power modulo a modulus.
     * \details This function calculates the modular exponentiation of a base raised to a power modulo a modulus using the square-and-multiply algorithm.
     * \param uint64_t x - The base value.
     * \param uint64_t e - The exponent value.
     * \param uint64_t n - The n parameter of public key.
     * \return uint64_t - The result of the modular exponentiation.
     *  \author Bianca Jansen Van Rensburg
     *  \date 30 April 2024
     */
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
    };

    /**
     *  \brief Calculate the greatest common divisor (GCD) of two 64-bit unsigned integers.
     * \details This function calculates the greatest common divisor (GCD) of two 64-bit unsigned integers using the Euclidean algorithm.
     * \param uint64_t a - The first integer.
     * \param uint64_t b - The second integer.
     * \return uint64_t - The greatest common divisor of a and b.
     *  \authors Bianca Jansen Van Rensburg
     *  \date 30 April 2024
     */
    uint64_t gcd_64t(uint64_t a, uint64_t b)
    {
        if (b == 0)
        {
            return a;
        }
        return gcd_64t(b, a % b);
    };

    /**
     *  \deprecated This function is not sufficient for Paillier cryptosystem.
     * \brief Calculate the set of elements in (Z/n²Z)*.
     * \details This function calculates the set of elements in (Z/n²Z)* that are coprime to n.
     * \param uint64_t n - The n parameter of public key.
     * \return std::vector<uint64_t> - The set of elements in (Z/n²Z)* that are coprime to n.
     *  \authors Katia Auxilien
     *  \date 30 April 2024 15:51:00
     */
    std::vector<uint64_t> calc_set_same_remainder_divide_euclide_64t(uint64_t n)
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
    };

    /**
     *  \deprecated This function is not sufficient for Paillier cryptosystem.
     * \brief Calculate the set of elements in (Z/n²Z)* that satisfy the condition L(x) = (x-1)/n where x is a positive integer and mu exists.
     * \details This function calculates the set of elements in (Z/n²Z)* that satisfy the condition L(x) = (x-1)/n where x is a positive integer and mu exists.
     * \param uint64_t n - The n parameter of public key.
     * \param const uint64_t &lambda - The lambda parameter of private key.
     * \return std::vector<uint64_t> - The set of elements in (Z/n²Z)* that satisfy the condition L(x) = (x-1)/n where x is a positive integer and mu exists.
     *  \authors Katia Auxilien
     *  \date 22 May 2024 14:45:00
     */
    std::vector<uint64_t> calc_set_same_remainder_divide_euclide_64t_v2(uint64_t n, const uint64_t &lambda)
    {
        std::vector<uint64_t> result;

        uint64_t x, r = 0, mu = 0;
        for (uint64_t g = 0; g < n; g++)
        {
            if (gcd_64t(g, n) == 1)
            {
                uint64_t u = fastMod_64t(g, lambda, n * n);
                uint64_t l = (u - 1) / n;
                r = (x - 1) % n; // Vérifier si x est entier.
                mu = modInverse_64t(l, n);
                if (mu != 0)
                {
                    result.push_back(g);
                }
            }
        }
        return result;
    };

    /**
     *  \deprecated This function is not sufficient for Paillier cryptosystem.
     * \brief Choose g from the set of elements in (Z/n²Z)* that satisfy the condition L(x) = (x-1)/n where x is a positive integer and mu exists.
     * \details This function chooses g from the set of elements in (Z/n²Z)* that satisfy the condition L(x) = (x-1)/n where x is a positive integer and mu exists.
     * \param std::vector<uint64_t> &set - The set of elements in (Z/n²Z)* that satisfy the condition L(x) = (x-1)/n where x is a positive integer and mu exists.
     * \param const uint64_t &n - The n parameter of public key.
     * \param const uint64_t &lambda - The lambda parameter of private key.
     * \return uint64_t - The chosen value of g.
     *  \authors Katia Auxilien
     *  \date 02 May 2024
     */
    uint64_t choose_g_in_vec_64t(std::vector<uint64_t> &set, const uint64_t &n, const uint64_t &lambda)
    {
        uint64_t x;
        int i_position = 0;
        uint64_t g = 0, r = 1, r2 = 1, mu = 0;
        while (r != 0 && r2 != 0 && mu == 0)
        {
            i_position = rand() % set.size();
            g = set.at(i_position);
            x = fastMod_64t(g, lambda, n * n);
            r = (x - 1) % n;            // Vérifier si L(x) est entier.
            r2 = (x - 1) / n;           // Vérifier si L(x) est entier.
            mu = modInverse_64t(r2, n); // Calculer μ en utilisant la formule donnée et la fonction modular_inverse pour calculer l'inverse modulaire
        }
        return g;
    };

    /**
     * \deprecated This function is not sufficient for Paillier cryptosystem.
     * \brief Choose g from the set of elements in (Z/n²Z)*.
     * \details This function chooses g from the set of elements in (Z/n²Z)*.
     * \param std::vector<uint64_t> &set - The set of elements in (Z/n²Z)*.
     * \return uint64_t - The chosen value of g.
     * \authors Katia Auxilien
     * \date 22 May 2024 14:45:00
     */
    uint64_t choose_g_in_vec_64t_v2(std::vector<uint64_t> &set)
    {
        int i_position = rand() % set.size();
        return set.at(i_position);
    };

    /**
     * \brief Calculate L(x).
     * \details This function calculates L(x) which is used in the generation of Mu and the decryption by Paillier.
     * \param uint64_t x - The value of x.
     * \param uint64_t n - The n parameter of public key.
     * \return uint64_t - The value of L(x).
     * \author Bianca Jansen Van Rensburg
     */
    uint64_t L_64t(uint64_t x, uint64_t n)
    {
        return (x - 1) / n;
    };

    /**
     *  \brief Calculate the least common multiple (LCM) of two 64-bit unsigned integers.
     * \details This function calculates the least common multiple (LCM) of two 64-bit unsigned integers using the GCD function.
     * \param uint64_t a - The first integer.
     * \param uint64_t b - The second integer.
     * \return uint64_t - The least common multiple of a and b.
     *  \author Bianca Jansen Van Rensburg
     */
    uint64_t lcm_64t(uint64_t a, uint64_t b)
    {
        return a * b / gcd_64t(a, b);
    };

    /**
     *  \brief Calculate the modular inverse of a 64-bit unsigned integer modulo a modulus.
     * \details This function calculates the modular inverse of a 64-bit unsigned integer modulo a modulus using the extended Euclidean algorithm.
     * \param uint64_t a - The integer to calculate the modular inverse of.
     * \param uint64_t n - The n parameter of public key.
     * \return uint64_t - The modular inverse of a modulo n.
     *  \author Bianca Jansen Van Rensburg
     */
    uint64_t modInverse_64t(uint64_t a, uint64_t n)
    {
        a = a % n;
        for (uint64_t x = 1; x < n; x++)
        {
            if ((a * x) % n == 1)
                return x;
        }

        return 0;
    };

    /**
     *  \brief Calculate the power of a 64-bit unsigned integer.
     *  \details This function calculates the power of a 64-bit unsigned integer using recursion.
     *  \param uint64_t x - The base value.
     *  \param uint64_t n - The exponent value.
     *  \return uint64_t - The result of the power calculation.
     *  \author Katia Auxilien
     *  \date 30 April 2024
     */
    uint64_t pow_uint64_t(uint64_t x, uint64_t n)
    {
        if (n == 0)
        {
            return 1;
        }
        return x * pow_uint64_t(x, n - 1);
    };

    /**
     *  \brief Choose a random element from the set Z/nZ*.
     *  \details This function chooses a random element from the set Z/nZ*.
     *  From program Paillier.java (https://perso.liris.cnrs.fr/omar.hasan/pprs/paillierdemo/) developped by Omar Hasan.
     *  \param uint64_t n - The n parameter of public key.
     *  \return uint64_t - The chosen random element from the set Z/nZ*.
     *  \param
     *  \author Katia Auxilien
     *  \date 23 May 2024 15:00:00
     */
    uint64_t randomZNStar(uint64_t n)
    {
        uint64_t r = 0;
        do
        {
            r = random64(1, n);
        } while (r >= 1 && gcd_64t(r, n) != 1);
        return r;
    };

    /**
     *  \brief Return the set Z/nZ* as a vector.
     *  \details This function returns the set Z/nZ* as a vector.
     *  \param uint64_t n - The n parameter of public key.
     *  \return std::vector<uint64_t> - The set Z/nZ* as a vector.
     *  \author Katia Auxilien
     *  \date 23 May 2024 9:18:00
     */
    std::vector<uint64_t> get_set_ZNZStar(uint64_t n)
    {
        std::vector<uint64_t> ZNZStar;
        for (uint64_t i = 1; i < n; i++)
        {
            if (gcd_64t(i, n) == 1)
            {
                ZNZStar.push_back(i);
            }
        }
        return ZNZStar;
    }

    /**
     *  \brief Return the set Z/n²Z* that satisfy the condition gcd(L(g^lambda mod n²), n) = 1 as a vector.
     *  \details This function returns the set Z/n²Z* that satisfy the condition gcd(L(g^lambda mod n²), n) = 1 as a vector.
     *  \param uint64_t n - The n parameter of public key.
     *  \param uint64_t lambda - The lambda parameter of private key.
     *  \return std::vector<uint64_t> - The set Z/n²Z* that satisfy the condition gcd(L(g^lambda mod n²), n) = 1 as a vector.
     *  \author Katia Auxilien
     *  \date 27 May 2024 15:00:00
     */
    std::vector<uint64_t> get_set_ZN2ZStar(uint64_t n, uint64_t lambda)
    {
        std::vector<uint64_t> ZN2ZStar;
        for (uint64_t g = 1; g < n * n; g++)
        {
            uint64_t u, l;
            u = fastMod_64t(g, lambda, n * n);
            l = L_64t(u, n);
            if (gcd_64t(l, n) == 1)
            {
                ZN2ZStar.push_back(g);
            }
        }
        return ZN2ZStar;
    }

    /**
     *  \brief Generate g for Paillier cryptosystem.
     *  \details This function generates g for Paillier cryptosystem such that gcd(L(g^lambda mod n²), n) = 1 where L(u) = (u-1)/n.
     *  From program Paillier.java (https://perso.liris.cnrs.fr/omar.hasan/pprs/paillierdemo/) developped by Omar Hasan.
     *  \param uint64_t n - The n parameter of public key.
     *  \param uint64_t lambda - The lambda parameter of private key.
     *  \return uint64_t - The generated value of g.
     *  \authors Katia Auxilien
     *  \date 23 May 2024 15:00:00
     */
    uint64_t generate_g_64t(uint64_t n, uint64_t lambda)
    {
        uint64_t g, u, l;
        do
        {
            g = randomZNStar(n * n); // generate g, a random integer in Z*_{n^2}
            u = fastMod_64t(g, lambda, n * n);
            l = L_64t(u, n);
        } while (gcd_64t(l, n) != 1);
        return g;
    };

    /**
     * \brief Generate Mu for Paillier cryptosystem.
     * \details This function generates Mu for Paillier cryptosystem which is used in the decryption process.
     * \param uint64_t &mu - The generated value of Mu.
     * \param const uint64_t &g - The generator value.
     * \param const uint64_t &lambda - The Carmichael function of n.
     * \param const uint64_t &n - The modulus value.
     * \author Bianca Jansen Van Rensburg
     * \date ?
     */
    void generateMu_64t(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n)
    {
        uint64_t u = fastMod_64t(g, lambda, n * n);
        uint64_t l = (u - 1) / n;
        mu = modInverse_64t(l, n);
    };

    /**
     * \brief Generate private key for Paillier cryptosystem.
     * \details This function generates the private key for Paillier cryptosystem which consists of lambda and Mu values.
     * \param uint64_t &lambda - The generated value of lambda.
     * \param uint64_t &mu - The generated value of Mu.
     * \param const uint64_t &p - The first prime factor of n.
     * \param const uint64_t &q - The second prime factor of n.
     * \param const uint64_t &n - The n parameter of public key.
     * \param const uint64_t &g - The generator value.
     * \author Bianca Jansen Van Rensburg
     */
    void generatePrivateKey_64t(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g)
    {
        lambda = lcm_64t(p - 1, q - 1);

        generateMu_64t(mu, g, lambda, n);
    };

    //================ Overload and Generic programming ================//

    /**
     *  \overload
     *  \brief Encrypt a message using Paillier cryptosystem.
     *  \details This function encrypts a message using Paillier cryptosystem.
     *  \param uint64_t n - The modulus value.
     *  \param uint64_t g - The generator value.
     *  \param T_in m - The message to be encrypted.
     *  \return T_out - The encrypted message.
     *  \authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  \date 13 May 2024
     */
    T_out paillierEncryption(uint64_t n, uint64_t g, T_in m)
    {
        if (m >= std::numeric_limits<uint64_t>::max())
        {
            throw std::runtime_error("Erreur m ne peut pas être stocké dans 64 bits.");
        }
        uint64_t m_64 = static_cast<uint64_t>(m);

        uint64_t c;
        // uint64_t r = random64(0,n);
        // while (gcd_64t(r, n) != 1 || r == 0)
        // {
        //     r = random64(0,n);
        // }
        uint64_t r = randomZNStar(n);

        // fprintf(stdout, "r : %" PRIu64 "\n", r);

        uint64_t fm1 = fastMod_64t(g, m_64, n * n);
        uint64_t fm2 = fastMod_64t(r, n, n * n);
        c = (fm1 * fm2) % (n * n);

        if (c >= std::numeric_limits<T_out>::max())
        {
            throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans n*2 bits.");
        }
        return static_cast<T_out>(c);
    };

    /**
     *  \overload
     *  \brief Encrypt a message using Paillier cryptosystem with a given random value.
     *  \details This function encrypts a message using Paillier cryptosystem with a given random value.
     *  \param uint64_t n - The modulus value.
     *  \param uint64_t g - The generator value.
     *  \param T_in m - The message to be encrypted.
     *  \param uint64_t r - The random value.
     *  \return T_out - The encrypted message.
     *  \authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  \date 13 May 2024
     */
    T_out paillierEncryption(uint64_t n, uint64_t g, T_in m, uint64_t r)
    {
        if (m >= std::numeric_limits<uint64_t>::max())
        {
            throw std::runtime_error("Erreur m ne peut pas être stocké dans 64 bits.");
        }
        uint64_t m_64 = static_cast<uint64_t>(m);

        uint64_t c;
        uint64_t fm1 = fastMod_64t(g, m_64, n * n);
        uint64_t fm2 = fastMod_64t(r, n, n * n);
        c = (fm1 * fm2) % (n * n);

        if (c >= std::numeric_limits<T_out>::max())
        {
            throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans n*2 bits.");
        }
        return static_cast<T_out>(c);
    };

    /**
     *  \overload
     *  \brief Decrypt a ciphertext using Paillier cryptosystem.
     *  \details This function decrypts a ciphertext using Paillier cryptosystem.
     *  \param uint64_t n - The modulus value.
     *  \param uint64_t lambda - The Carmichael function of n.
     *  \param uint64_t mu - The Mu value.
     *  \param T_out c - The ciphertext to be decrypted.
     *  \return T_in - The decrypted message.
     *  \authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  \date 13 May 2024
     */
    T_in paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, T_out c)
    {
        if (c >= std::numeric_limits<uint64_t>::max())
        {
            throw std::runtime_error("Erreur m ne peut pas être stocké dans 64 bits.");
        }
        uint64_t c_64 = static_cast<uint64_t>(c);

        // uint64_t result = (((fastMod_64t(c_64, lambda, n * n) - 1) / n) * mu) % n;
        uint64_t result = ((fastMod_64t(c_64, lambda, n * n) - 1) / n) * mu % n;

        if (result >= std::numeric_limits<T_in>::max())
        {
            throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 8 bits.");
        }
        return static_cast<T_in>(result);
    };
};

#endif // PAILLIER_CRYPTOSYSTEM