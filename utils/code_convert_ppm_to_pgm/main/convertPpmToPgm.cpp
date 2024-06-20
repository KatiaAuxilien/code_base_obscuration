#include "../include/Functions.h"

typedef unsigned char OCTET;

std::string getProgramFolderPath(std::string programName) {
    return std::filesystem::canonical(std::filesystem::path(programName)).parent_path().parent_path().string();
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

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		printf("Usage : ImageIn.ppm ImageOut.pgm\n");
		return 1;
	}

    char cNameImageIn[200], cNameImageOut[200];

    std::string sNameImageIn = argv[1];
    std::string sNameImageOut = argv[2];
    std::string sNewfolderpath;

    std::strcpy(cNameImageIn,sNameImageIn.c_str());
        std::strcpy(cNameImageOut,sNameImageOut.c_str());

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

    return 0;
}