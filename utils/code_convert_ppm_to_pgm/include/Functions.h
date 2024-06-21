//
// Created by Norman on 06 March 2024.
//


#ifndef STAGE_IMAGE_FUNCTIONS_H
#define STAGE_IMAGE_FUNCTIONS_H

#define M_PI 3.14159265358979323846

#include "ImageBase.h"


// Calcule les histogrammes des composantes couleur d'une image pass�e en entr�e
void computeColorHist(ImageBase & image, int histR[256], int histG[256], int histB[256]);

// Compare les histogrammes de deux images
void compareImagesByHist(ImageBase & image1, ImageBase & image2);

// G�n�re un kernel de flou gaussien selon la taille et le sigma pass�s en param�tres
void generateGaussianKernel(std::vector<std::vector<float>> & kernel, int size, float sigma);

// Applique un flou gaussien � l'image d'entr�e, sur l'image de sortie
void gaussianBlur(ImageBase & image, ImageBase & o_image, int kernelSize, float sigma);

// Genere une sequence de 8 bits al�atoires
void genPRNS(unsigned int seq[8]);
// Applique un flou selectif progressif � l'ensemble des pixels (on applique un XOR � chaque pixel de gauche �
// droite (dir == 0) ou de droite � gauche (dir == 1) et stocke les images respectives dans o_images
void selectiveProgressiveEncryption(ImageBase & image, ImageBase o_images[8], bool MSBtoLSB);

void selectiveIndividualEncryption(ImageBase & image, ImageBase o_images[8]);

void selectiveGroupEncryption(ImageBase & image, ImageBase & o_image, int bitsGroup[8], int groupSize);

void areaScrambling(ImageBase & image, ImageBase & o_image, int start_i, int start_j, int area_h, int area_w);

void scrambling(ImageBase & image, ImageBase & o_image, int regionHeight, int regionWidth);

void averageBlurring(ImageBase & image, ImageBase & o_image, int regionSize);

void newAverageBlurring(ImageBase & image, std::vector<ImageBase> & o_images);

void areaAverager(ImageBase & image, ImageBase & o_image, int start_i, int start_j, int area_h, int area_w);

void averageByRegion(ImageBase & image, ImageBase & o_image, int regionHeight, int regionWidth);

double computePSNR(ImageBase & image1, ImageBase & image2);

void computePSNRforAllAlterations(std::vector<double> & PSNRArray, const char* baseName, int i_min, int i_max, int step);

void writeDataOnTxt(std::vector<double> & data, std::string filename);

void RGB2GREY(ImageBase & imColor, ImageBase & imGrey);

double computeImageMean(ImageBase & image);

double computeSSIM(ImageBase & image1, ImageBase & image2);

int interpolate_color(int p11, int p21, int p12, int p22, float dx, float dy);

void interpolate_bilinear(ImageBase & image, int & valR, int & valG, int & valB, float i, float j);

void bilinearRedim299(ImageBase & image, ImageBase & o_image);

#endif //STAGE_IMAGE_FUNCTIONS_H
