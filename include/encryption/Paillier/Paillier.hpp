/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier.hpp
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
#include <random>
#include "../../../include/image/image_pgm.hpp"

#define BITSETSIZE 64

#ifndef PAILLIER_CRYPTOSYSTEM
#define PAILLIER_CRYPTOSYSTEM

using namespace std;

template <typename T_in, typename T_out>
class Paillier
{
public:
    Paillier(){};
    ~Paillier(){};



    /**
     *  @brief 
     *  @details Générer une variable de type uint64_t aléatoirement
     *  @param uint64_t min
     *  @param uint64_t max
     *  @authors Katia Auxilien
     *  @date 23/05/2024
     */
    uint64_t random64(uint64_t min, uint64_t max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<std::uint64_t> dis(min, max);

        //unsigned long long
        //std::uniform_int_distribution<unsigned long long> dis(min, max);

        // std::uniform_int_distribution<unsigned long long> dis(
        //     std::numeric_limits<std::uint64_t>::min(),
        //     std::numeric_limits<std::uint64_t>::max()
        // );

        return dis(gen);
    }


    /**
     *  @brief Calcul de l'exponentiation modulaire rapide.
     *  @details Calcul de l'exponentiation modulaire rapide.
     *  @param uint64_t x 
     *  @param uint64_t i puissance
     * 	@param uint64_t n modulo
     *  @authors Katia Auxilien
     *  @date 30/04/2024
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
     *  @brief Calcul du PGCD en récursif.
     *  @details Calcul du PGCD en récursif, de a et b sur 64 bit.
     *  @param uint64_t a
     * 	@param uint64_t b
     *  @authors Katia Auxilien
     *  @date 30/04/2024
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
     *  @deprecated Cette génération n'est pas suffisante pour paillier.
     *  @brief 
     *  @details Calcul de l'ensemble des éléments de  g ∈ (Z/n²Z)*
     *  @param
     *  @authors Katia Auxilien
     *  @date 30/04/2024 15:51:00
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
     *  @deprecated Cette génération n'est pas suffisante pour paillier.
     *  @brief
     *  @details Génération de l'ensemble des éléments de  g ∈ (Z/n²Z)* ET respectant : L(x) = (x-1)/n dont x  ∈ N* ET il existe mu.
     *  @param uint64_t n
     *  @param const uint64_t &lambda
     *  @authors Katia Auxilien
     *  @date 22/05/2024 14:45:00
     */
    std::vector<uint64_t> calc_set_same_remainder_divide_euclide_64t_v2(uint64_t n, const uint64_t &lambda)
    {
        std::vector<uint64_t> result;

        uint64_t x, r = 0, mu = 0;
        for (uint64_t g = 0; g < n; g++)
        {
            if(gcd_64t(g, n) == 1){
                uint64_t u = fastMod_64t(g, lambda, n * n);
                uint64_t l = (u - 1) / n;
                r = (x - 1) % n; //Vérifier si x est entier.
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
     *  @deprecated Cette génération n'est pas suffisante pour paillier.
     *  @brief 
     *  @details Choix de g tant que (x - 1)/n ne donne pas un L(x) entier.
     *  @param
     *  @authors Katia Auxilien
     *  @date 02/05/2024
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
            r = (x - 1) % n; //Vérifier si L(x) est entier.
            r2 = (x - 1) / n; //Vérifier si L(x) est entier.
            mu = modInverse_64t(r2, n); // Calculer μ en utilisant la formule donnée et la fonction modular_inverse pour calculer l'inverse modulaire
        }
        return g;
    };

    /**
     *  @deprecated Cette génération n'est pas suffisante pour paillier.
     *  @brief
     *  @details Choix de g tant que (x - 1)/n ne donne pas un L(x) entier.
     *  @param
     *  @authors Katia Auxilien
     *  @date 22/05/2024 14:45:00
     */
    uint64_t choose_g_in_vec_64t_v2(std::vector<uint64_t> &set)
    {
        int i_position = rand() % set.size();
        return set.at(i_position);
    };

    /**
     *  @brief Calcul de L(x).
     *  @details Calcul de L(x) nécessaire dans la génération de Mu et le déchiffrement par Paillier.
     *  @param uint64_t x
     * 	@param uint64_t n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    uint64_t L_64t(uint64_t x, uint64_t n)
    {
        return (x - 1) / n;
    };

    /**
     *  @brief Calcul du plus petit diviseur commun.
     *  @details Calcul du plus petit diviseur commun de a et b.
     *  @param uint64_t a
     * 	@param uint64_t b
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    uint64_t lcm_64t(uint64_t a, uint64_t b)
    {
        return a * b / gcd_64t(a, b);
    };

    /**
     *  @brief Calcul de l'inverse modulaire de a modulo n.
     *  @details Calcul de l'inverse modulaire de a modulo n sur 64 bit.
     *  @param uint64_t a
     * 	@param uint64_t n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
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
     *  @brief Calcul de la puissance de n de x
     *  @details Calcul de la puissance de n de x en récursif.
     *  @param uint64_t x
     * 	@param uint64_t n
     *  @authors Katia Auxilien
     *  @date 30/04/2024
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
     *  @brief Chosiir un élément de manière aléatoire dans l'ensemble Z/nZ* 
     *  @details Basé sur le programme Paillier.java (https://perso.liris.cnrs.fr/omar.hasan/pprs/paillierdemo/) développé par by Omar Hasan.
     *  @param
     *  @authors Katia Auxilien
     *  @date 23/05/2024 15:00:00
     */
    uint64_t randomZNStar(uint64_t n){
        uint64_t r = 0;
        do
        {
            r = random64(1,n);
        }while(r >= 1 && gcd_64t(r,n) != 1);
        return r;
    };



    /**
     *  @brief Retourner l'ensemble Z/nZ*  sous forme d'un vecteur.
     *  @details 
     *  @param
     *  @authors Katia Auxilien
     *  @date 23/05/2024 9:18:00
     */
    std::vector<uint64_t> get_set_ZNZStar(uint64_t n){
        std::vector<uint64_t> ZNZStar;
        for(uint64_t i = 1; i < n; i++){
            if(gcd_64t(i,n) == 1){
                ZNZStar.push_back(i);
            }
        }
        return ZNZStar;
    }

    /**
     *  @brief
     *  @details Basé sur le programme Paillier.java (https://perso.liris.cnrs.fr/omar.hasan/pprs/paillierdemo/) développé par by Omar Hasan.
     *          On vérifie que la valeur de g donne gcd(L(g^lambda mod n^2), n) = 1 sachant que L(u) = (u-1)/n
     *  @param uint64_t n
     *  @param uint64_t lambda
     *  @authors Katia Auxilien
     *  @date 23/05/2024 15:00:00
     */
    uint64_t generate_g_64t(uint64_t n,uint64_t lambda){
        uint64_t g,u,l;
        do{
            g = randomZNStar(n*n); // generate g, a random integer in Z*_{n^2}
            u = fastMod_64t(g, lambda, n * n);
            l = L_64t(u,n);
        }
        while(gcd_64t(l,n) !=1);
        return g;
    };


    /**
     *  @brief Génération du Mu.
     *  @details Génération du paramètre Mu nécessaire à la clé privée du chiffrement par Paillier.
     *  @param uint64_t &mu
     * 	@param const uint64_t &g
     *  @param const uint64_t &lambda
     *  @param const uint64_t &n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    void generateMu_64t(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n)
    {
        uint64_t u = fastMod_64t(g, lambda, n * n);
        uint64_t l = (u - 1) / n;
        mu = modInverse_64t(l, n);
    };

    /**
     *  @brief Génération de la clé privée du chiffrement par Paillier.
     *  @details Génération de la clé privée du chiffrement par Paillier avec des paramètres sur 64 bit.
     *  @param uint64_t &lambda
     * 	@param uint64_t &mu
     *  @param const uint64_t &p
     *  @param const uint64_t &q
     *  @param const uint64_t &n
     *  @param const uint64_t &g
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    void generatePrivateKey_64t(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g)
    {
        lambda = lcm_64t(p - 1, q - 1);

        generateMu_64t(mu, g, lambda, n);
    };

    //================ Overload and Generic programming ================//

    /**
     *  @overload
     *  @brief Chiffrement par paillier.
     *  @details Chiffrement par paillier d'un message m sur n bit.
     *  @param uint64_t n valeur p*q.
     * 	@param uint64_t g élément choisit dans l'ensemble (Z/n2Z)*.
     *  @param T_in m message en clair sur n bit.
     *  @return static_cast<T_in>(c) : Le message m chiffré, dont le chiffré est sur 2*n bit.
     *  @retval T_in
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
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
     *  @overload
     *  @brief Chiffrement par paillier.
     *  @details Chiffrement par paillier d'un message m sur n bit.
     *  @param uint64_t n valeur p*q, fait partie de la clé publique.
     * 	@param uint64_t g élément choisit dans l'ensemble (Z/n2Z)*, fait partie de la clé publique.
     *  @param T_in m message en clair sur nbit. 
     *  @param uint64_t r élément aléatoire appartenant à l'ensemble r ∈ (Z/nZ)*.
     *  @return static_cast<T_out>(c) : Le message m chiffré, dont le chiffré est sur 2*n bit.
     *  @retval T_out
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
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
     *  @overload
     *  @brief Déchiffrement par paillier.
     *  @details Déchiffrement par paillier d'un chiffré sur 2*n bit.
     *  @param uint64_t n valeur p*q.
     * 	@param uint64_t lambda correspond au lcm(p-1,q-1), fait partie de la clé privée.
     *  @param uint64_t mu généré par la fonction generateMu_64t(...), fait partie de la clé privée.
     *  @param T_out c message chiffré sur 2*nbits.
     *  @return static_cast<T_in>(result) : Le message clair, déchiffré de c, sur n bit.
     *  @retval T_in
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
     */
    T_in paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, T_out c)
    {
        if (c >= std::numeric_limits<uint64_t>::max())
        {
            throw std::runtime_error("Erreur m ne peut pas être stocké dans 64 bits.");
        }
        uint64_t c_64 = static_cast<uint64_t>(c);

        //uint64_t result = (((fastMod_64t(c_64, lambda, n * n) - 1) / n) * mu) % n;
        uint64_t result = ((fastMod_64t(c_64, lambda, n * n) - 1) / n) * mu % n;

        if (result >= std::numeric_limits<T_in>::max())
        {
            throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 8 bits.");
        }
        return static_cast<T_in>(result);
    };
};

#endif // PAILLIER_CRYPTOSYSTEM