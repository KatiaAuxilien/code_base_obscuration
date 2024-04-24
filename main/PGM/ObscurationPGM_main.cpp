#include "../../include/ImageBase.h"
#include "../../include/obscurationCommon.h"
#include "../../include/obscurationPGM.h"
#include "../../include/filesystemPGM.h"
#include "../../include/filesystemCommon.h"
#include "../../include/AES.h"
extern "C"
{
#include "../../include/image_ppm.h"
}

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#define FILE_EXT ".pgm"

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
 * Pour utiliser ce programme, les images contenues dans vos fichiers doivent avoir le nom 'nomdudossier_ (i)' i allant de 0 à n images.
 **/
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : directory\n");
        return 1;
    }

    char t_cImagePath[200];
    std::string sFolderPath = argv[1];
    std::string sImgClass = getLastDirectoryName(sFolderPath);
    std::string sNewFolderPath;
    std::vector<std::string> v_sImagePaths;

    // ============================ DEBUT Blurring ============================ //
    std::cout << "Floutage moyenneur..."
              << "\n";

    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/blurring/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    int nTotalImg = v_sImagePaths.size();
/*
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
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        std::vector<ImageBase> v_ibImgOut;
        newAverageBlurring_PGM(ibImgInResized, v_ibImgOut);

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
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/scrambling/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

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
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int cpt = 1; cpt <= 50; ++cpt)
        {
            ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());

            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            scrambling_PGM(ibImgInResized, ibImgOut, cpt, cpt);
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
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/pixeliser/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

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
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int cpt = 1; cpt <= 50; ++cpt)
        {
            ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());

            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            averageByRegion_PGM(ibImgInResized, ibImgOut, cpt, cpt);
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
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/individual/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

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
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        selectiveIndividualEncryption_PGM(ibImgInResized, t_ibImages);

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
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/consecutive-MSB2LSB/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

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
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        selectiveProgressiveEncryption_PGM(ibImgInResized, t_ibImages, true);

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
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/consecutive-LSB2MSB/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

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
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        selectiveProgressiveEncryption_PGM(ibImgInResized, t_ibImages, false);

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
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/ranged/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

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
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int nGSize = 1; nGSize <= 8; ++nGSize)
        {
            std::vector<std::vector<int>> v_nBitGroup;
            genBitsGroups(v_nBitGroup, nGSize);
            for (size_t i = 0; i < v_nBitGroup.size(); ++i)
            {
                int nGroup[8];
                intVec2intArray(v_nBitGroup[i], nGroup);
                ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());
                selectiveGroupEncryption_PGM(ibImgInResized, ibImgOut, nGroup, nGSize);

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
    */
    std::cout << "\t"
              << "Chiffrement AES"
              << "\n";

    char t_cImageInPath[200], t_cImageOutPath[200];
/*
    // ============== DEBUT Chiffrement AES ECB ============== //

    std::cout << "mode ECB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/ECB/";
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_ECB_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};

        oImgOut = aes.EncryptECB(oImgIn, nTaille, key);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
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
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CBC/";
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_CBC_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());


        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCBC(oImgIn, nTaille, key, iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
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
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CTR/";
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_CTR_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());


        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCTR(oImgIn, nTaille, key, iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement AES CTR ============== //
*/
    // ============== DEBUT Chiffrement AES CFB ============== //

    std::cout << "mode CFB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CFB/";
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);

        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";

        std::string sNewImgPath = sNewFolderPath + "/";
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_CFB_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());


        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCFB(oImgIn, nTaille, key, iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement AES CFB ============== //
/*
    // ============== DEBUT Chiffrement AES OFB ============== //

    std::cout << "mode OFB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/OFB/";
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);

        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        // std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
        //           << "\n";


        std::string sNewImgPath = sNewFolderPath + "/";
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_OFB_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptOFB(oImgIn, nTaille, key, iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        // std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";

    // ============== FIN Chiffrement AES OFB ============== //
*/
    // ============================ FIN Chiffrement AES ============================ //

    // ============================ Chiffrement AES avec autre clé ============================ //

    std::cout << "mode CFB avec déchiffrement par clé différente..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CFB_dec_bad_key/";
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (size_t nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        afficherBarreDeChargement(nImg_cpt, nTotalImg);

        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        std::string sNewImgPath = sNewFolderPath + "/";
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_CFB_dec_bad_key_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());


        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut, *oImgOutDec;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);


        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCFB(oImgIn, nTaille, key, iv);

        unsigned char key_falsified[] = {0xa7, 0xe8, 0x46, 0x9f, 0x3a, 0x67, 0x89, 0xab, 0x92, 0x7a, 0x8b, 0x2e, 0x7c, 0xd2, 0xd1, 0xe3};

        allocation_tableau(oImgOutDec, OCTET, nTaille);

        oImgOutDec = aes.DecryptCFB(oImgOut, nTaille,key_falsified,iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOutDec, nH, nW);
        free(oImgIn);
        free(oImgOut);

    }
    afficherBarreDeChargement(nTotalImg, nTotalImg);
    std::cout << "\n";



    return 0;
}