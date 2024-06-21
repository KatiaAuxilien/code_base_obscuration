/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : Tests_Paillier_main.cpp
 *
 * Description : Main qui permet de tester et vérifier le bon fonctionnement de
 * 	l'enregistrement des clés et la génération de g.
 *   File source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
 *
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 03 May 2024 9:50:00
 *
 *******************************************************************************/
#include "../../../include/Paillier.h"
#include "../../../include/filesystemCommon.h"
#include "../../../include/filesystemPGM.h"
#include "../../../include/Paillier_private_key.hpp"
#include "../../../include/Paillier_public_key.hpp"
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
    uint64_t n = 15;
    uint64_t m = 0;
    vector<long uint64_t> set = calc_set_same_remainder_divide_euclide(n);
    for (int i = 0; i < set.size(); i++)
    {
        m = set.at(i);
        std::cout << m << " ";
        for (int y = 1; y < 5; y++)
        {
            if (m == 3 * y || m == 5 * y)
            {
                fprintf(stderr, "ERROR : the set contains 3 or 5 multiple.\n");
                return 1;
            }
        }
    }
    std::cout << "\n";

    uint64_t x, lambda, g1, r, r2;
    uint64_t g = choose_g_in_vec(set, n, lambda);

    x = fastMod(g1, lambda, n * n);
    r = (x - 1) % n;
    r2 = (x - 1) / n;
    if (r != 0 && r2 != 0)
    {
        fprintf(stderr, "ERROR : g is not good.\n");
        return 1;
    }
}