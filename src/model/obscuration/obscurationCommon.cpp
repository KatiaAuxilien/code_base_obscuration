/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : ObscurationCommon.cpp
 *
 * Description : Implementation of super class containing common and useful methods
 *               for obscuring pgm and ppm images.
 *
 * Authors : Katia Auxilien, Norman Hutte
 *
 * Mail : katia.auxilien@mail.fr , ?
 *
 * Date : April 2024
 *
 *******************************************************************************/

#include "../../../include/model/obscuration/obscurationCommon.hpp"

void obscurationCommon::genPRNS(unsigned int seq[8])
{
    std::random_device randev;
    std::mt19937 rng(randev());
    std::uniform_int_distribution<unsigned int> distrbit(0, 1);
    for (unsigned int i = 0; i < 8; ++i)
        seq[i] = distrbit(rng);
}

void obscurationCommon::genBitsGroups(std::vector<std::vector<int>> &groups, int groupSize)
{
    groups.clear();
    for (int i = 0; i < 7 - groupSize + 2; ++i)
    {
        std::vector<int> indexes;
        for (int j = 0; j < groupSize; ++j)
        {
            indexes.push_back(i + j);
        }
        groups.push_back(indexes);
    }
}

void obscurationCommon::intVec2intArray(std::vector<int> &vec, int arr[8])
{
    for (size_t i = 0; i < vec.size(); ++i)
        arr[i] = vec[i];
}