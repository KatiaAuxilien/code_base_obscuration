/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : ObscurationPPM_main.cpp
 *
 * Description :
 *   Source files main.cpp and Functions.h by Norman Hutte
 *
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : April 2024
 *
 *******************************************************************************/
#include "../../../../include/model/filesystem/filesystemCommon.hpp"
#include "../../../../include/model/image/ImageBase.hpp"
#include "../../../../include/model/image/image_ppm.hpp"
#include "../../../../include/model/obscuration/obscurationPPM.hpp"
#include "../../../../include/model/obscuration/obscurationCommon.hpp"

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

//TODO : Documentation

bool is_ppm(const std::string &extension)
{
    return extension == ".ppm";
}

void getFilePathsOfPPMFilesFromFolder(std::vector<std::string> &imagePaths, std::string folderPath)
{
    imagePaths.clear();
    for (const auto &entry : std::filesystem::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            std::string file_extension = entry.path().extension().string();
            if (is_ppm(file_extension))
            {
                imagePaths.push_back(entry.path().string());
            }
        }
    }
}

void string2char(std::string str, char *charArray)
{
    charArray = new char[str.length() + 1];
    std::strcpy(charArray, str.c_str());
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Passez un repertoire en parametre !\n");
        return 1;
    }

    char imagePath[200];
    std::string folderpath = argv[1];
    std::string classString = filesystemCommon::getLastDirectoryName(folderpath);
    std::string newfolderpath;
    std::vector<std::string> imagePaths;

    // ============== DEBUT Blurring ==============
    std::cout << "Debut floutage moyenneur..."
              << "\n";
    std::strcpy(imagePath, folderpath.c_str());
    newfolderpath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPPM/blurring/" + classString;
    getFilePathsOfPPMFilesFromFolder(imagePaths, imagePath);
    for (size_t img_cpt = 0; img_cpt < imagePaths.size(); ++img_cpt)
    {
        ImageBase imInOriginal;
        std::cout << "Image " << img_cpt + 1 << " sur " << imagePaths.size() << "\n";
        std::string imInPath = folderpath + '/' + classString + "_ (" + std::to_string(img_cpt + 1) + ").ppm";
        std::strcpy(imagePath, imInPath.c_str());
        imInOriginal.load(imagePath);
        ImageBase imIn(299, 299, true);
        bilinearRedim299(imInOriginal, imIn);
        std::string imgNewFolderPath = newfolderpath + "/" + std::to_string(img_cpt);
        filesystemCommon::createDirectoryIfNotExists(imgNewFolderPath);
        std::vector<ImageBase> o_images;
        newAverageBlurring(imIn, o_images);
        for (int cpt = 1; cpt <= 101; cpt += 2)
        {
            std::string imOutPath = imgNewFolderPath + "/" + classString + "_" + std::to_string(img_cpt) + "_" + std::to_string(cpt) + ".ppm";
            std::strcpy(imagePath, imOutPath.c_str());
            o_images[cpt / 2].save(imagePath);
        }
    }
    std::cout << "Fin floutage moyenneur"
              << "\n";
    // ============== FIN Blurring ==============

    // ============== DEBUT Scrambling ==============
    std::cout << "Debut melange par region..."
              << "\n";
    std::strcpy(imagePath, folderpath.c_str());
    newfolderpath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPPM/scrambling/" + classString;
    getFilePathsOfPPMFilesFromFolder(imagePaths, imagePath);
    for (size_t img_cpt = 0; img_cpt < imagePaths.size(); ++img_cpt)
    {
        ImageBase imInOriginal;
        std::cout << "Image " << img_cpt + 1 << " sur " << imagePaths.size() << "\n";
        std::string imInPath = folderpath + '/' + classString + "_ (" + std::to_string(img_cpt + 1) + ").ppm";
        std::strcpy(imagePath, imInPath.c_str());
        imInOriginal.load(imagePath);
        ImageBase imIn(299, 299, true);
        bilinearRedim299(imInOriginal, imIn);
        std::string imgNewFolderPath = newfolderpath + "/" + std::to_string(img_cpt);
        filesystemCommon::createDirectoryIfNotExists(imgNewFolderPath);

        for (int cpt = 1; cpt <= 50; ++cpt)
        {
            ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
            std::string imOutPath = imgNewFolderPath + "/" + classString + "_" + std::to_string(img_cpt) + "_" + std::to_string(cpt) + ".ppm";
            std::strcpy(imagePath, imOutPath.c_str());
            scrambling(imIn, imOut, cpt, cpt);
            imOut.save(imagePath);
        }
    }
    std::cout << "Fin melange par region"
              << "\n";
    // ============== FIN Scrambling ==============

    // ============== DEBUT Pixelisation ==============
    std::cout << "Debut moyenneur par r�gion..."
              << "\n";
    std::strcpy(imagePath, folderpath.c_str());
    newfolderpath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPPM/pixelizer/" + classString;
    getFilePathsOfPPMFilesFromFolder(imagePaths, imagePath);
    for (size_t img_cpt = 0; img_cpt < imagePaths.size(); ++img_cpt)
    {
        ImageBase imInOriginal;
        std::cout << "Image " << img_cpt + 1 << " sur " << imagePaths.size() << "\n";
        std::string imInPath = folderpath + '/' + classString + "_ (" + std::to_string(img_cpt + 1) + ").ppm";
        std::strcpy(imagePath, imInPath.c_str());
        imInOriginal.load(imagePath);
        ImageBase imIn(299, 299, true);
        bilinearRedim299(imInOriginal, imIn);
        std::string imgNewFolderPath = newfolderpath + "/" + std::to_string(img_cpt);
        filesystemCommon::createDirectoryIfNotExists(imgNewFolderPath);
        for (int cpt = 1; cpt <= 50; ++cpt)
        {
            ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
            std::string imOutPath = imgNewFolderPath + "/" + classString + "_" + std::to_string(img_cpt) + "_" + std::to_string(cpt) + ".ppm";
            std::strcpy(imagePath, imOutPath.c_str());
            averageByRegion(imIn, imOut, cpt, cpt);
            imOut.save(imagePath);
        }
    }
    std::cout << "Fin moyenneur par region"
              << "\n";
    // ============== FIN Pixelisation ==============

    // ============== DEBUT Chiffrement ==============
    std::cout << "Debut chiffrement selectif..."
              << "\n";
    std::strcpy(imagePath, folderpath.c_str());
    newfolderpath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPPM/encryption/" + classString;
    getFilePathsOfPPMFilesFromFolder(imagePaths, imagePath);
    std::string imgNewFolderPath;
    for (size_t img_cpt = 0; img_cpt < imagePaths.size(); ++img_cpt)
    {
        ImageBase imInOriginal;
        std::cout << "Image " << img_cpt + 1 << " sur " << imagePaths.size() << "\n";
        std::string imInPath = folderpath + '/' + classString + "_ (" + std::to_string(img_cpt + 1) + ").ppm";
        std::strcpy(imagePath, imInPath.c_str());
        imInOriginal.load(imagePath);
        ImageBase imIn(299, 299, true);
        bilinearRedim299(imInOriginal, imIn);

        // Bits individuels
        imgNewFolderPath = newfolderpath + "/" + std::to_string(img_cpt) + "/individual";
        filesystemCommon::createDirectoryIfNotExists(imgNewFolderPath);

        ImageBase ind_images[8] = {ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                   ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                   ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                   ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                   ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                   ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                   ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                   ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor())};
        selectiveIndividualEncryption(imIn, ind_images);
        for (int cpt = 0; cpt <= 7; ++cpt)
        {
            std::string imOutPath = imgNewFolderPath + "/" + classString + "_" + std::to_string(img_cpt) + "_" + std::to_string(cpt) + ".ppm";
            std::strcpy(imagePath, imOutPath.c_str());
            ind_images[cpt].save(imagePath);
        }

        // Bits cons�cutifs (MSB -> LSB)
        imgNewFolderPath = newfolderpath + "/" + std::to_string(img_cpt) + "/consecutive-MSB2LSB";
        filesystemCommon::createDirectoryIfNotExists(imgNewFolderPath);

        ImageBase cons1_images[8] = {ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor())};
        selectiveProgressiveEncryption(imIn, cons1_images, true);
        for (int cpt = 0; cpt <= 7; ++cpt)
        {
            std::string imOutPath = imgNewFolderPath + "/" + classString + "_" + std::to_string(img_cpt) + "_" + std::to_string(cpt) + ".ppm";
            std::strcpy(imagePath, imOutPath.c_str());
            cons1_images[cpt].save(imagePath);
        }

        // Bits cons�cutifs (LSB -> MSB)
        imgNewFolderPath = newfolderpath + "/" + std::to_string(img_cpt) + "/consecutive-LSB2MSB";
        filesystemCommon::createDirectoryIfNotExists(imgNewFolderPath);

        ImageBase cons2_images[8] = {ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor()),
                                     ImageBase(imIn.getWidth(), imIn.getHeight(), imIn.getColor())};
        selectiveProgressiveEncryption(imIn, cons2_images, false);
        for (int cpt = 0; cpt <= 7; ++cpt)
        {
            std::string imOutPath = imgNewFolderPath + "/" + classString + "_" + std::to_string(img_cpt) + "_" + std::to_string(cpt) + ".ppm";
            std::strcpy(imagePath, imOutPath.c_str());
            cons2_images[cpt].save(imagePath);
        }

        // Bits group�s
        imgNewFolderPath = newfolderpath + "/" + std::to_string(img_cpt) + "/ranged";
        filesystemCommon::createDirectoryIfNotExists(imgNewFolderPath);

        for (int gsize = 1; gsize <= 8; ++gsize)
        {
            std::vector<std::vector<int>> groups;
            genBitsGroups(groups, gsize);
            for (size_t i = 0; i < groups.size(); ++i)
            {
                int group[8];
                intVec2intArray(groups[i], group);
                ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
                selectiveGroupEncryption(imIn, imOut, group, gsize);
                std::string imOutPath = imgNewFolderPath + "/" + classString + "_" + std::to_string(img_cpt) + "_" + std::to_string(gsize) + "_" + std::to_string(i) + ".ppm";
                std::strcpy(imagePath, imOutPath.c_str());
                imOut.save(imagePath);
            }
        }
    }
    std::cout << "Fin chiffrement selectif"
              << "\n";
    // ============== FIN Chiffrement ==============

    return 0;
}
