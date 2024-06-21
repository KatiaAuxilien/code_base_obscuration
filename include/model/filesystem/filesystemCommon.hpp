/**
 * \file filesystemCommon.hpp
 * \brief
 * \authors Katia Auxilien, Norman Hutte
 * \date April 2024
 * \details This file contains the declaration of the filesystemCommon class,
 * which provides various utility functions for handling files and directories.
 */

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
 * \class filesystemCommon
 * \brief A utility class providing functions to handle files and directories.
 * \author Norman Hutte
 * \date 06 March 2024
 */
class filesystemCommon
{
public:
    /**
     *  \brief Get the last directory name from a given path.
     *  \param path The path to extract the last directory name from.
     *  \return std::string The last directory name in the given path.
     *  \author Norman Hutte
     *  \date 06 March 2024
     */
    static std::string getLastDirectoryName(const std::string &path);

    /**
     *  \brief Get the program folder path.
     *  \param programName The name of the program.
     *  \return std::string The path to the program's folder.
     *  \author Norman Hutte
     *  \date 06 March 2024
     */
    static std::string getProgramFolderPath(std::string programName);

    /**
     *  \brief Create a directory at the given path if it does not already exist.
     *  \param path The path where the directory should be created.
     *  \author Norman Hutte
     *  \date 06 March 2024
     */
    static void createDirectoryIfNotExists(const std::string &path);
};

#endif // FILESYSTEM_COMMON_LIBRARY