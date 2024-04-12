#include "include/ImageBase.h"
#include "include/obscurationCommon.h"
#include "include/obscurationPGM.h"
#include "include/filesystemPGM.h"
#include "include/filesystemCommon.h"

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#define FILE_EXT ".pgm"


/**
 * Pour utiliser ce programme, les images contenues dans vos fichiers doivent avoir le nom 'nomdudossier_ (i)' i allant de 0 à n images.
**/
int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage : directory\n");
		return 1;
	}

    char t_cImagePath[200];
    std::string sFolderPath = argv[1];
    std::string sImgClass = getLastDirectoryName(sFolderPath);
    std::string sNewFolderPath;
    std::vector<std::string> v_sImagePaths;

    // ============================ DEBUT Blurring ============================ //
    // std::cout << "Debut floutage moyenneur..." << "\n";
    
    // std::strcpy(t_cImagePath, sFolderPath.c_str());
    // sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPPM/blurring/" + sImgClass;
    // getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    // for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt) {
    //     ImageBase ibImgInOriginal;
    //     std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt+1) + ")" + FILE_EXT;
    //     std::strcpy(t_cImagePath, sImInPath.c_str());
    //     ibImgInOriginal.load(t_cImagePath);
    //     std::cout << "Image n°" << nImg_cpt+1 << " en cours ... " <<"\n";

    //     std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
    //     createDirectoryIfNotExists(sNewImgPath);

    //     ImageBase ibImgInResized(299, 299, false);
    //     bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);
            
    //     std::vector<ImageBase> v_ibImgOut;
    //     newAverageBlurring_PGM(ibImgInResized, v_ibImgOut);

    //     for (int cpt = 1; cpt <= 101; cpt+=2) {
    //         std::string sImOutPath = sNewImgPath + "/" + sImgClass
    //                                 + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
    //         std::strcpy(t_cImagePath, sImOutPath.c_str());
    //         v_ibImgOut[cpt/2].save(t_cImagePath);
    //     }
    //     std::cout << "Image " << nImg_cpt+1 << " sur " << v_sImagePaths.size() << "\n";
    // }
    // std::cout << "Fin floutage moyenneur" << "\n";
    // ============================ FIN Blurring ============================ //

// ============================ DEBUT Scrambling ============================ //
    // std::cout << "Debut melange par region..." << "\n";
    
    // std::strcpy(t_cImagePath, sFolderPath.c_str());
    // sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPPM/scrambling/" + sImgClass;
    // getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    // for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt) {
    //     ImageBase ibImgInOriginal;
    //     std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt+1) + ")" + FILE_EXT;
    //     std::strcpy(t_cImagePath, sImInPath.c_str());
    //     ibImgInOriginal.load(t_cImagePath);
    //     std::cout << "Image n°" << nImg_cpt+1 << " en cours ... " <<"\n";

    //     std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
    //     createDirectoryIfNotExists(sNewImgPath);

    //     ImageBase ibImgInResized(299, 299, false);
    //     bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);
            
    //     for (int cpt = 1; cpt <= 50; ++cpt) {
    //         ImageBase ibImgOut(ibImgInResized.getWidth(),ibImgInResized.getHeight(),ibImgInResized.getColor());

    //         std::string sImOutPath = sNewImgPath + "/" + sImgClass
    //                                 + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
    //         std::strcpy(t_cImagePath, sImOutPath.c_str());

    //         scrambling(ibImgInResized,ibImgOut,cpt,cpt);
    //         ibImgOut.save(t_cImagePath);
    //     }
    //     std::cout << "Image " << nImg_cpt+1 << " sur " << v_sImagePaths.size() << "\n";
    // }
    // std::cout << "Fin melange par region" << "\n";
    // ============================ FIN Scrambling ============================ //

// ============================ DEBUT Scrambling ============================ //
    std::cout << "Debut moyenneur par r�gion..." << "\n";
    
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPPM/pixeliser/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt) {
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt+1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        std::cout << "Image n°" << nImg_cpt+1 << " en cours ... " <<"\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);
            
        for (int cpt = 1; cpt <= 50; ++cpt) {
            ImageBase ibImgOut(ibImgInResized.getWidth(),ibImgInResized.getHeight(),ibImgInResized.getColor());

            std::string sImOutPath = sNewImgPath + "/" + sImgClass
                                    + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            averageByRegion(ibImgInResized,ibImgOut,cpt,cpt);
            ibImgOut.save(t_cImagePath);
        }
        std::cout << "Image " << nImg_cpt+1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin moyenneur par region" << "\n";
    // ============================ FIN Scrambling ============================ //


	return 0;
}
