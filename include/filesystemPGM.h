/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : filesystementPGM.h
 *
 * Description : Classe contenant des fonctions qui permettent de récupérer des
 *    images au format .pgm. Classe inspirée de Functions.h de Norman Hutte.
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024
 *
 *******************************************************************************/
#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <string>

#ifndef FILESYSTEM_PGM_LIBRARY
#define FILESYSTEM_PGM_LIBRARY

/**
 *  @brief
 *  @param extension
 *  @authors Norman Hutte, Katia Auxilien
 *  @date 11/04/2024
 *
 *  desc
 *
 *  @details
 */
bool is_pgm(const std::string &extension)
{
    return extension == ".pgm";
}

/**
 *  @brief
 *  @param imagePaths
 *  @param folderPath
 *  @authors Norman Hutte, Katia Auxilien
 *  @date 11/04/2024
 *
 *
 *
 *  @details
 */
void getFilePathsOfPGMFilesFromFolder(std::vector<std::string> &imagePaths, std::string folderPath)
{
    imagePaths.clear();
    for (const auto &entry : std::filesystem::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            std::string file_extension = entry.path().extension().string();
            if (is_pgm(file_extension))
            {
                imagePaths.push_back(entry.path().string());
            }
        }
    }
}

#endif // FILESYSTEM_PGM_LIBRARY