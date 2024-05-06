/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : filesystemCommon.h
 *
 * Description : Classe contenant des fonctions qui permettent de traiter des
 *  images dans un système de fichiers. Inspirée de function.h de Norman Hutte.
 *
 * Auteurs : Norman Hutte, Katia Auxilien
 *
 * Mail : , katia.auxilien@mail.fr
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

#ifndef FILESYSTEM_COMMON_LIBRARY
#define FILESYSTEM_COMMON_LIBRARY

/**
 *  @brief
 *  @param
 *  @authors Norman Hutte
 *  @date 06/03/2024
 *
 *  desc
 *
 *  @details
 */
std::string getLastDirectoryName(const std::string &path)
{
    std::filesystem::path chemin(path);
    return chemin.filename().string();
}

/**
 *  @brief
 *  @param
 *  @authors Norman Hutte
 *  @date 06/03/2024
 *
 *  desc
 *
 *  @details
 */
std::string getProgramFolderPath(std::string programName)
{
    return std::filesystem::canonical(std::filesystem::path(programName)).parent_path().parent_path().string();
}

/**
 *  @brief
 *  @param
 *  @authors Norman Hutte
 *  @date 06/03/2024
 *
 *  desc
 *
 *  @details
 */
void createDirectoryIfNotExists(const std::string &path)
{
    if (!std::filesystem::exists(path))
    {
        if (!std::filesystem::create_directories(path))
        {
            fprintf(stderr, "Erreur : Impossible de creer le repertoire %s \n", path.c_str());
        }
        else
        {
            // printf("Repertoire cree : %s \n", path.c_str());
        }
    }
    else
    {
        // printf("Le repertoire existe deja : %s \n", path.c_str());
    }
}

#endif // FILESYSTEM_COMMON_LIBRARY