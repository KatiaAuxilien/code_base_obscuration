/**
 * @file ObscurationPGM_main.cpp
 * @brief Main file for the PGM image obscuration program using the Paillier cryptosystem.
 * @author Katia Auxilien
 * @date April 2024
 * @details This program implements various image obscuration techniques on PGM images
 * using the Paillier cryptosystem. The techniques include blurring, scrambling,
 * pixelation, and selective encryption. The program takes a directory as input
 * and applies the obscuration techniques to all PGM images in the directory.
 * The obscured images are then saved to separate directories based on the
 * technique used.
 * The main function first checks if the correct number of arguments has been
 * provided. If not, it prints a usage message and returns 1. Otherwise, it
 * initializes an empty PGM image and proceeds to apply the obscuration
 * techniques.
 * The blurring technique uses a simple average filter to blur the image.
 * The scrambling technique divides the image into regions and scrambles the
 * pixels within each region. The pixelation technique replaces each region
 * with its average color. The selective encryption technique encrypts only
 * certain bits of the image data using the Paillier cryptosystem.
 * The program uses the filesystemPGM and filesystemCommon classes to handle
 * file I/O operations. It also uses the AES class from the encryption module
 * to perform AES encryption on the image data.
 * The program displays a progress bar during the obscuration process to provide
 * feedback to the user. It also prints error messages if any issues occur
 * during the process.
 * Source files main.cpp and Functions.h by Norman Hutte
 */
#include "../../../include/model/image/ImageBase.hpp"
#include "../../../include/model/obscuration/obscurationCommon.hpp"
#include "../../../include/model/obscuration/obscurationPGM.hpp"
#include "../../../include/model/filesystem/filesystemPGM.hpp"
#include "../../../include/model/filesystem/filesystemCommon.hpp"
#include "../../../include/model/encryption/AES/AES.hpp"
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#define FILE_EXT ".pgm"

/**
 * @brief Displays a progress bar in the console.
 * @param progress The current progress (number of completed tasks).
 * @param total The total number of tasks.
 * @details This function displays a progress bar in the console using ASCII characters.
 * The color of the progress bar changes based on the percentage of completion.
 * If the completion percentage is less than or equal to 50%, the color is red.
 * If it is between 50% and 70%, the color is yellow. Otherwise, the color is
 * dark green.
 * The function takes two arguments: the current progress and the total number
 * of tasks. It calculates the size of the progress bar based on these values
 * and then prints the progress bar to the console using the std::cout object.
 * The function also prints the completion percentage next to the progress bar.
 * The function uses the std::string object to store the color code for the
 * progress bar. It also uses a loop to print the progress bar characters one
 * by one.
 */
void afficherBarreDeChargement(size_t progress, size_t total)
{
    int barSize = 50;
    int progressSize = (progress * barSize) / total;

    std::string colorCode;
    if (progress <= total * 0.50)
    {
        colorCode = "\e[1;91m";
    }
    else if (progress <= total * 0.70)
    {
        colorCode = "\e[1;93m";
    }
    else
    {
        colorCode = "\e[1;92m"; // Dark green
    }

    std::cout << "[";
    for (int i = 0; i < barSize; ++i)
    {
        if (i < progressSize)
        {
            std::cout << colorCode << "#";
        }
        else
        {
            std::cout << ".";
        }
    }
    std::cout << "\e[0m";
    std::cout << "] " << (progress * 100 / total) << "%\r";
    std::cout.flush();
}

/**
 * @brief Main function for the PGM image obscuration program.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return 0 if the program runs successfully, 1 otherwise.
 * @details This function is the entry point for the PGM image obscuration program.
 * It takes two arguments: the number of command-line arguments and the
 * command-line arguments themselves.
 * The function first checks if the correct number of arguments has been
 * provided. If not, it prints a usage message and returns 1. Otherwise, it
 * initializes an empty PGM image and proceeds to apply the obscuration
 * techniques.
 * The function uses the filesystemPGM and filesystemCommon classes to handle
 * file I/O operations. It also uses the AES class from the encryption module
 * to perform AES encryption on the image data.
 * The function displays a progress bar during the obscuration process to provide
 * feedback to the user. It also prints error messages if any issues occur
 * during the process.
 * Example usage:
 * $ ./ObscurationPGM_main /path/to/image/directory
 * To use this program, the images contained in your files must have the name 'foldername_ (i)' where i goes from 0 to n images.
 */
int main(int argc, char **argv)
{
    image_pgm img_pgm;
    img_pgm = image_pgm();

    if (argc != 2)
    {
        printf("Usage : directory\n");
        return 1;
    }

    char t_cImagePath[200];
    std::string sFolderPath = argv[1];
    std::string sImgClass = filesystemCommon::getLastDirectoryName(sFolderPath);
    std::string sNewFolderPath;
    std::vector<std::string> v_sImagePaths;

    // ============================ DEBUT Blurring ============================ //
    std::cout << "Floutage moyenneur..."
              << "\n";

    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/blurring/" + sImgClass;
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    int nTotalImg = v_sImagePaths.size();

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);

        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        obscurationPGM::bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        std::vector<ImageBase> v_ibImgOut;
        obscurationPGM::newAverageBlurring_PGM(ibImgInResized, v_ibImgOut);

        for (int cpt = 1; cpt <= 101; cpt += 2)
        {
            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());
            v_ibImgOut[cpt / 2].save(t_cImagePath);
        }
        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";
    // ============================ FIN Blurring ============================ //

    // ============================ DEBUT Scrambling ============================ //
    std::cout << "Mélange par region..."
              << "\n";

    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/scrambling/" + sImgClass;
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        obscurationPGM::bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int cpt = 1; cpt <= 50; ++cpt)
        {
            ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());

            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            obscurationPGM::scrambling_PGM(ibImgInResized, ibImgOut, cpt, cpt);
            ibImgOut.save(t_cImagePath);
        }
        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";
    // ============================ FIN Scrambling ============================ //

    // ============================ DEBUT Pixelisation ============================ //
    std::cout << "Moyenneur par région..."
              << "\n";

    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/pixeliser/" + sImgClass;
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        obscurationPGM::bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int cpt = 1; cpt <= 50; ++cpt)
        {
            ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());

            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            obscurationPGM::averageByRegion_PGM(ibImgInResized, ibImgOut, cpt, cpt);
            ibImgOut.save(t_cImagePath);
        }
        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";
    // ============================ FIN Pixelisation ============================ //

    // ============================ DEBUT Chiffrement sélectif ============================ //
    std::cout << "\t"
              << "Chiffrement sélectif"
              << "\n";

    // ============== DEBUT Chiffrement sélectif par bit individuel ============== //

    std::cout << "par bit individuel..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/individual/" + sImgClass;
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);

        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        obscurationPGM::bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        obscurationPGM::selectiveIndividualEncryption_PGM(ibImgInResized, t_ibImages);

        for (int cpt = 0; cpt <= 7; ++cpt)
        {

            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            t_ibImages[cpt].save(t_cImagePath);
        }
        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";
    // ============== FIN Chiffrement sélectif par bit individuel ============== //

    // ============== DEBUT Chiffrement sélectif par bit consecutif MSB à LSB ============== //

    std::cout << "par bit consecutif MSB à LSB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/consecutive-MSB2LSB/" + sImgClass;
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        obscurationPGM::bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        obscurationPGM::selectiveProgressiveEncryption_PGM(ibImgInResized, t_ibImages, true);

        for (int cpt = 0; cpt <= 7; ++cpt)
        {
            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            t_ibImages[cpt].save(t_cImagePath);
        }
        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement sélectif par bit consecutif MSB à LSB ============== //

    // ============== DEBUT Chiffrement sélectif par bit consecutif MSB à LSB ============== //

    std::cout << "bit consecutif LSB à MSB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/consecutive-LSB2MSB/" + sImgClass;
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        obscurationPGM::bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        obscurationPGM::selectiveProgressiveEncryption_PGM(ibImgInResized, t_ibImages, false);

        for (int cpt = 0; cpt <= 7; ++cpt)
        {
            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            t_ibImages[cpt].save(t_cImagePath);
        }
        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";
    // ============== FIN Chiffrement sélectif par bit consecutif MSB à LSB ============== //

    // ============== DEBUT Chiffrement sélectif par bit groupé ============== //

    std::cout << "par bits groupé..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/ranged/" + sImgClass;
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        obscurationPGM::bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int nGSize = 1; nGSize <= 8; ++nGSize)
        {
            std::vector<std::vector<int>> v_nBitGroup;
            obscurationPGM::genBitsGroups(v_nBitGroup, nGSize);
            for (size_t i = 0; i < v_nBitGroup.size(); ++i)
            {
                int nGroup[8];
                obscurationPGM::intVec2intArray(v_nBitGroup[i], nGroup);
                ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());
                obscurationPGM::selectiveGroupEncryption_PGM(ibImgInResized, ibImgOut, nGroup, nGSize);

                std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(nGSize) + FILE_EXT;
                std::strcpy(t_cImagePath, sImOutPath.c_str());

                ibImgOut.save(t_cImagePath);
            }
        }
        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";
    // ============== FIN Chiffrement sélectif par bit groupé============== //
    // ============================ FIN Chiffrement sélectif ============================ //

    // ============================ DEBUT Chiffrement AES ============================ //

    std::cout << "\t"
              << "Chiffrement AES"
              << "\n";

    char t_cImageInPath[200], t_cImageOutPath[200];

    // ============== DEBUT Chiffrement AES ECB ============== //

    std::cout << "mode ECB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/ECB/";
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_ECB_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        img_pgm.lire_nb_lignes_colonnes_image_p(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        img_pgm.lire_image_p(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};

        oImgOut = aes.EncryptECB(oImgIn, nTaille, key);

        img_pgm.ecrire_image_p(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement AES ECB ============== //

    // ============== DEBUT Chiffrement AES CBC ============== //
    std::cout << "mode CBC..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CBC/";
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_CBC_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        img_pgm.lire_nb_lignes_colonnes_image_p(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        img_pgm.lire_image_p(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCBC(oImgIn, nTaille, key, iv);

        img_pgm.ecrire_image_p(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement AES CBC ============== //

    // ============== DEBUT Chiffrement AES CTR ============== //

    std::cout << "mode CTR..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CTR/";
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_CTR_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        img_pgm.lire_nb_lignes_colonnes_image_p(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        img_pgm.lire_image_p(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCTR(oImgIn, nTaille, key, iv);

        img_pgm.ecrire_image_p(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement AES CTR ============== //

    // ============== DEBUT Chiffrement AES CFB ============== //

    std::cout << "mode CFB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CFB/";
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);

        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_CFB_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        img_pgm.lire_nb_lignes_colonnes_image_p(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        img_pgm.lire_image_p(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCFB(oImgIn, nTaille, key, iv);

        img_pgm.ecrire_image_p(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement AES CFB ============== //

    // ============== DEBUT Chiffrement AES OFB ============== //

    std::cout << "mode OFB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/OFB/";
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);

        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_OFB_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        img_pgm.lire_nb_lignes_colonnes_image_p(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        img_pgm.lire_image_p(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptOFB(oImgIn, nTaille, key, iv);

        img_pgm.ecrire_image_p(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement AES OFB ============== //

    // ============================ FIN Chiffrement AES ============================ //

    // ============================ Chiffrement AES avec autre clé ============================ //

    std::cout << "mode CFB avec déchiffrement par clé différente..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = filesystemCommon::getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CFB_dec_bad_key/";
    filesystemPGM::getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);

        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        std::string sNewImgPath = sNewFolderPath + "/";
        filesystemCommon::createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_CFB_dec_bad_key_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut, *oImgOutDec;

        img_pgm.lire_nb_lignes_colonnes_image_p(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        img_pgm.lire_image_p(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCFB(oImgIn, nTaille, key, iv);

        unsigned char key_falsified[] = {0xa7, 0xe8, 0x46, 0x9f, 0x3a, 0x67, 0x89, 0xab, 0x92, 0x7a, 0x8b, 0x2e, 0x7c, 0xd2, 0xd1, 0xe3};

        allocation_tableau(oImgOutDec, OCTET, nTaille);

        oImgOutDec = aes.DecryptCFB(oImgOut, nTaille, key_falsified, iv);

        img_pgm.ecrire_image_p(t_cImageOutPath, oImgOutDec, nH, nW);
        free(oImgIn);
        free(oImgOut);
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    return 0;
}