
#include "../include/ImageBase.h"
#include "../include/Functions.h"
extern "C"{
    #include "../include/image_ppm.h"
}


#include <cstdio>
#include <cstring>
#include <string>
#include <filesystem>


bool is_ppm(const std::string& extension) {
    return extension == ".ppm";
}

std::string getLastDirectoryName(const std::string & path) {
    std::filesystem::path chemin(path);
    return chemin.filename().string();
}

std::string getProgramFolderPath(std::string programName) {
    return std::filesystem::canonical(std::filesystem::path(programName)).parent_path().parent_path().string();
}


void getImagesFromFolder(std::vector<std::string> & imagePaths, std::string folderPath) {
    imagePaths.clear();
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string file_extension = entry.path().extension().string();
            if (is_ppm(file_extension)) {
                imagePaths.push_back(entry.path().string());
            }
        }
    }
}

void createDirectoryIfNotExists(const std::string & path) {
    if (!std::filesystem::exists(path)) {
        if (!std::filesystem::create_directories(path)) {
            std::cerr << "Erreur : Impossible de creer le repertoire " << path << "\n";
        } else {
            std::cout << "Repertoire cree : " << path << "\n";
        }
    } else {
        std::cout << "Le repertoire existe deja : " << path << "\n";
    }
}


void convertPpmToPgm(char * cNameImageIn, char* cNameImageOut){

    int nH, nW, nTaille, nTaille3, nR, nG,nB;
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNameImageIn, &nH, &nW);

        nTaille = nH * nW;
        nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNameImageIn, ImgIn, nTaille);

    allocation_tableau(ImgOut, OCTET, nTaille);

    int k = 0;
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nW; j++)
        {
            k =  (i * nW + j) * 3;
            nR = k;
            nG = k+1;
            nB = k+2;
            ImgOut[i*nW+j] = 0.2126 * ImgIn[nR] + 0.7152 * ImgIn[nG] + 0.0722 * ImgIn[nB];

        }
    }
    

    ecrire_image_pgm(cNameImageOut, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

}


int main(int argc, char const *argv[])
{
	if (argc != 2) {
		printf("Usage : directory\n");
		return 1;
	}
    char imageInPath[200],imageOutPath[200];
    char cNameFolder[200];
    std::string sNameFolder = argv[1];
    std::string sNameclassString = getLastDirectoryName(sNameFolder);

    std::string sNewfolderpath;
    std::vector<std::string> imagePaths;
    
    std::strcpy(cNameFolder,sNameFolder.c_str());

    sNewfolderpath = getProgramFolderPath(argv[0]) + "/pgm/"+ sNameclassString ;
    createDirectoryIfNotExists(sNewfolderpath);

    std::cout << "Conversion ppm en pgm ..." << "\n";

    getImagesFromFolder(imagePaths, cNameFolder);
    for (int img_cpt = 0; img_cpt < imagePaths.size(); ++img_cpt) {
        std::cout << "Image " << img_cpt+1 << " sur " << imagePaths.size() << "\n";


        std::string sImgInPath = sNameFolder + '/'+ sNameclassString +" (" + std::to_string(img_cpt+1) + ").ppm";
        std::strcpy(imageInPath, sImgInPath.c_str());
        std::string sImgOutPath = sNewfolderpath + '/'+ sNameclassString  +" (" + std::to_string(img_cpt+1) + ").pgm";
        std::strcpy(imageOutPath, sImgOutPath.c_str());

        convertPpmToPgm(imageInPath,imageOutPath);
    }

    std::cout << "Fin.." << "\n";
    return 0;
}
