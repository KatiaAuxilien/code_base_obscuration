/**
 * @file filesystemCommon.cpp
 * @brief
 * @authors Katia Auxilien, Norman Hutte
 * @date April 2024
 * @details This file contains the implementation of the filesystemCommon class,
 * which provides various utility functions for handling files and directories.
 */

#include "../../../include/model/filesystem/filesystemCommon.hpp"

std::string filesystemCommon::getLastDirectoryName(const std::string &path)
{
    std::filesystem::path chemin(path);
    return chemin.filename().string();
}

std::string filesystemCommon::getProgramFolderPath(std::string programName)
{
    return std::filesystem::canonical(std::filesystem::path(programName)).parent_path().parent_path().string();
}

void filesystemCommon::createDirectoryIfNotExists(const std::string &path)
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
};
