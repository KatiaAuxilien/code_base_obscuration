/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : filesystementPGM.h
 *
 * Description : Class containing functions that allow to retrieve images in .pgm format.
 * Class inspired by Functions.h of Norman Hutte.
 *
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024
 *
 *******************************************************************************/

#ifndef FILESYSTEM_PGM_LIBRARY
#define FILESYSTEM_PGM_LIBRARY
#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <string>

/**
 * \class filesystemPGM
 * \brief Utility class for handling .pgm image files.
 * \details This class provides functions for checking if a file extension is .pgm and for retrieving the file paths of all .pgm images in a folder. It is inspired by Norman Hutte's Functions.h.
 * \author Katia Auxilien
 */
class filesystemPGM
{

public:
    /**
     *  \brief Check if the file extension is .pgm
     *  \param extension The file extension to check
     *  \return True if the extension is .pgm, false otherwise
     *  \authors Norman Hutte, Katia Auxilien
     *  \date 11 April 2024
     */
    static bool is_pgm(const std::string &extension)
    {
        return extension == ".pgm";
    }

    /**
     * \brief Get the file paths of all .pgm images in a folder
     * \param imagePaths Vector to store the file paths of the .pgm images
     * \param folderPath Path of the folder to search for .pgm images
     * \details This function clears the imagePaths vector and then iterates through all the files in the folder specified by folderPath. If a file is a regular file (not a directory) and its extension is .pgm, the file path is added to the imagePaths vector.
     * \authors Norman Hutte, Katia Auxilien
     * \date 11 April 2024
     */
    static void getFilePathsOfPGMFilesFromFolder(std::vector<std::string> &imagePaths, std::string folderPath)
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
};

#endif // FILESYSTEM_PGM_LIBRARY