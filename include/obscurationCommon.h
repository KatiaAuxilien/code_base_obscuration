/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : ObscurationPgm.h
 *
 * Description : Classe contenant des méthodes communes et utiles pour l'obscuration des images ppm et pgm
 *
 * Auteur : Katia Auxilien, Norman Hutte
 *
 * Mail : katia.auxilien@mail.fr ,
 *
 * Date : Avril 2024
 *
 *******************************************************************************/

#include "ImageBase.h"
#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <cstring>
#include <fstream>

#ifndef OBSCURATION_COMMON_LIBRARY
#define OBSCURATION_COMMON_LIBRARY

//====================== Encryption utils ======================//

/**
 *  @brief 
 *  @param 
 *  @author Norman Hutte
 *  @date 06/03/2024
 * 
 *  Genere une sequence de 8 bits al�atoires
 *
 *  @details 
 */
void genPRNS(unsigned int seq[8])
{
    std::random_device randev;
    std::mt19937 rng(randev());
    std::uniform_int_distribution<unsigned int> distrbit(0, 1);
    for (unsigned int i = 0; i < 8; ++i)
        seq[i] = distrbit(rng);
}

/**
 *  @brief 
 *  @param 
 *  @author Norman Hutte
 *  @date 06/03/2024
 * 
 *  Genere une sequence de 
 *
 *  @details 
 */
void genBitsGroups(std::vector<std::vector<int>> & groups, int groupSize) {
    groups.clear();
    for (int i = 0; i < 7 - groupSize + 2; ++i) {
        std::vector<int> indexes;
        for  (int j = 0; j < groupSize; ++j) {
            indexes.push_back(i + j);
        }
        groups.push_back(indexes);
    }
}

/**
 *  @brief 
 *  @param 
 *  @author Norman Hutte
 *  @date 06/03/2024
 * 
 *  
 *
 *  @details 
 */
void intVec2intArray(std::vector<int> & vec, int arr[8]) {
    for (int i = 0; i < vec.size(); ++i)
        arr[i] = vec[i];
}

//====================== Scrambling ======================//

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void scrambling(ImageBase &image, ImageBase &o_image, int regionHeight, int regionWidth)
{
    int current_i = 0, current_j = 0;
    int height, width;
    height = image.getHeight();
    width = image.getWidth();
    int area_h, area_w;
    while (current_i < height)
    {
        area_h = (current_i + regionHeight <= height ? regionHeight : height - current_i);
        area_w = (current_j + regionWidth <= width ? regionWidth : width - current_j);
        areaScrambling(image, o_image, current_i, current_j, area_h, area_w);
        current_j += area_w;
        if (current_j == width)
        {
            current_j = 0;
            current_i = (current_i + regionHeight <= height ? current_i + regionHeight : height);
        }
    }
}

//====================== Averager ======================//


/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void averageByRegion(ImageBase &image, ImageBase &o_image, int regionHeight, int regionWidth)
{
    int current_i = 0, current_j = 0;
    int height, width;
    height = image.getHeight();
    width = image.getWidth();
    int area_h, area_w;
    while (current_i < height)
    {
        area_h = (current_i + regionHeight <= height ? regionHeight : height - current_i);
        area_w = (current_j + regionWidth <= width ? regionWidth : width - current_j);
        areaAverager(image, o_image, current_i, current_j, area_h, area_w);
        current_j += area_w;
        if (current_j == width)
        {
            current_j = 0;
            current_i = (current_i + regionHeight <= height ? current_i + regionHeight : height);
        }
    }
}



#endif // OBSCURATION_COMMON_LIBRARY