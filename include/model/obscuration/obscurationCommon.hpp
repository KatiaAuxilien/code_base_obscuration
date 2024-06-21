/**
 * \file ObscurationCommon.hpp
 * \brief Header of super class containing common and useful methods
 * for obscuring pgm and ppm images.
 * \authors Katia Auxilien, Norman Hutte
 * \date April 2024
 * \details
 */

#include "../image/ImageBase.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <cstring>
#include <fstream>

#ifndef OBSCURATION_COMMON_LIBRARY
#define OBSCURATION_COMMON_LIBRARY

/**
 * \class obscurationCommon
 * \brief This class contains common and useful methods for obscuring images.
 * \authors Katia Auxilien, Norman Hutte
 * \date April 2024
 */
class obscurationCommon
{
public:
    //====================== Encryption utils ======================//

    /**
     *  \brief Generate a random sequence of 8 bits
     *  \details This function generates a random sequence of 8 bits and stores it in the given array.
     *  \param seq The array to store the generated sequence
     *  \author Norman Hutte
     *  \date 06 March 2024
     */
    static void genPRNS(unsigned int seq[8]);

    /**
     *  \brief Generate groups of bits
     *  \details This function generates groups of bits of the specified size and stores them in the given vector.
     *  \param groups The vector to store the generated groups
     *  \param groupSize The size of each group
     *  \author Norman Hutte
     *  \date 06 March 2024
     */
    static void genBitsGroups(std::vector<std::vector<int>> &groups, int groupSize);

    /**
     *  \brief Convert a vector of integers to an array of integers
     *  \details This function converts a vector of integers to an array of integers and stores it in the given array.
     *  \param vec The vector to convert
     *  \param arr The array to store the converted data
     *  \author Norman Hutte
     *  \date 06 March 2024
     */
    static void intVec2intArray(std::vector<int> &vec, int arr[8]);
};

#endif // OBSCURATION_COMMON_LIBRARY