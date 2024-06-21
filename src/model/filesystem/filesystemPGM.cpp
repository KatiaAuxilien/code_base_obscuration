/**
 * \file filesystementPGM.hpp
 * \brief Implementation of functions that allow to retrieve images in .pgm format.
 * \author Katia Auxilien
 * \date April 2024
 * \details Class inspired by Functions.h of Norman Hutte.
 */

#include "../../../include/model/filesystem/filesystemPGM.hpp"

bool filesystemPGM::is_pgm(const std::string &extension)
{
    return extension == ".pgm";
}

void filesystemPGM::getFilePathsOfPGMFilesFromFolder(std::vector<std::string> &imagePaths, std::string folderPath)
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
