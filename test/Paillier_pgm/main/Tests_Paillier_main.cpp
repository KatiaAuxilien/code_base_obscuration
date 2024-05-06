/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Tests_Paillier_main.cpp
 *
 * Description : Main qui permet de tester et vérifier le bon fonctionnement de
 * 	l'enregistrement des clés et la génération de g.
 *   Fichier source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 03/05/2024 9:50:00
 *
 *******************************************************************************/
#include "../../include/Paillier.h"
#include "../../include/filesystemCommon.h"
#include "../../include/filesystemPGM.h"
#include "../../include/Paillier_private_key.hpp"
#include "../../include/Paillier_public_key.hpp"
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <vector>
using namespace std;

uint64_t checkNumbersArgument(string pos, char *arg)
{
    for (size_t i = 0; i < strlen(arg); i++)
    {
        if (!isdigit(arg[i]))
        {
            fprintf(stderr, "The %s argument must be an int.\n", pos.c_str());
            return 1;
        }
    }
    int p = atoi(arg);
    if (!isPrime(p, 2))
    {
        fprintf(stderr, "The %s argument must be a prime number.\n", pos.c_str());
        return 1;
    }

    return p;
}

bool endsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int main(int argc, char **argv)
{

    if (argc < 4)
    {
        printf("Usage : [e or ek or dk] [params] image_file.pgm\n e p q file.pgm\n ek public_key.bin image_file.pgm\n dk private_key.bin image_file_encrypted.pgm\n");
        return 1;
    }

    int argImg = 4;
    string englishArgNumb = "fourth";

    char *c_file = argv[argImg];
    string s_file = c_file;
    ifstream file(c_file);
    if (!file || !endsWith(s_file, ".pgm"))
    {
        cerr << "The " + englishArgNumb + " argument must be an existing .pgm file." << endl;
        return 1;
    }

    PaillierPrivateKey pk;
    PaillierPublicKey pubk;

    uint64_t p = checkNumbersArgument("second", argv[2]);
    if (p == 1)
    {
        return 1;
    }
    uint64_t q = checkNumbersArgument("third", argv[3]);
    if (q == 1)
    {
        return 1;
    }
    uint64_t n, lambda, mu;

    n = p * q;
    uint64_t pgc_pq = gcd(p * q, (p - 1) * (q - 1));

    if (pgc_pq != 1)
    {
        fprintf(stderr, " gcd(p * q, (p - 1) * (q - 1)) arguments must have a gcd = 1. Please retry with others p and q.\n");
        return 1;
    }

    vector<long uint64_t> set = calc_set_same_remainder_divide_euclide(n * n);
    for (long unsigned int i = 0; i < set.size(); i++)
    {
        std::cout << set.at(i) << " ";
    }

    uint64_t g = choose_g_in_vec(set, n, lambda);

    generatePrivateKey(lambda, mu, p, q, n, g);
    pk = PaillierPrivateKey(lambda, mu);
    pubk = PaillierPublicKey(n, g);

    FILE *f_private_key = NULL;

    f_private_key = fopen("Paillier_private_key.bin", "w+b");

    if (f_private_key == NULL)
    {
        fprintf(stderr, "Error ! Opening Paillier_private_key.bin\n");
        return 1;
    }

    fwrite(&pk, sizeof(PaillierPrivateKey), 1, f_private_key);

    fclose(f_private_key);

    FILE *f_public_key = NULL;
    f_public_key = fopen("Paillier_public_key.bin", "w+b");

    if (f_public_key == NULL)
    {
        fprintf(stderr, "Error ! Opening Paillier_public_key.bin\n");
        return 1;
    }
    fwrite(&pubk, sizeof(PaillierPublicKey), 1, f_public_key);

    fclose(f_public_key);

    printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
    printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
    printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
    printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());

    PaillierPrivateKey pk2;
    PaillierPublicKey pubk2;

    FILE *f_private_key2 = NULL;

    f_private_key2 = fopen("Paillier_private_key.bin", "rb");

    if (f_private_key2 == NULL)
    {
        fprintf(stderr, "Error ! Opening Paillier_private_key.bin \n");
        return 1;
    }

    fread(&pk2, sizeof(PaillierPrivateKey), 1, f_private_key2);

    fclose(f_private_key2);

    FILE *f_public_key2 = NULL;
    f_public_key2 = fopen("Paillier_public_key.bin", "rb");

    if (f_public_key2 == NULL)
    {
        fprintf(stderr, "Error ! Opening Paillier_public_key.bin \n");
        return 1;
    }
    fread(&pubk2, sizeof(PaillierPublicKey), 1, f_public_key2);

    fclose(f_public_key2);
    printf("Pub Key 2 G = %" PRIu64 "\n", pubk2.getG());
    printf("Pub Key 2 N = %" PRIu64 "\n", pubk2.getN());
    printf("Priv Key 2 lambda = %" PRIu64 "\n", pk2.getLambda());
    printf("Priv Key 2 mu = %" PRIu64 "\n", pk2.getMu());
}