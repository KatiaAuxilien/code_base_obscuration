//
// Created by Norman on 06/03/2024.
//
#include "ImageBase.h"
#include "obscurationCommon.h"

#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <cstring>
#include <fstream>

#ifndef STAGE_IMAGE_FUNCTIONS_H
#define STAGE_IMAGE_FUNCTIONS_H

#define M_PI 3.14159265358979323846

//====================== Interpolate ======================//

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *  ?
 *
 *  @details
 */
int interpolate_color(int p11, int p21, int p12, int p22, float dx, float dy)
{
    float interpolated_value =
        p11 * (1 - dx) * (1 - dy) +
        p21 * dx * (1 - dy) +
        p12 * (1 - dx) * dy +
        p22 * dx * dy;
    return static_cast<int>(interpolated_value);
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *  ??
 *
 *  @details
 */
void interpolate_bilinear(ImageBase &image, int &valR, int &valG, int &valB, float i, float j)
{
    int i1 = static_cast<int>(i), j1 = static_cast<int>(j);
    int i2 = i + 1, j2 = j + 1;
    float di = i - i1, dj = j - j1;

    valR = interpolate_color(image[3 * i1][3 * j1 + 0], image[3 * i2][3 * j1 + 0], image[3 * i1][3 * j2 + 0], image[3 * i2][3 * j2 + 0], di, dj);
    valG = interpolate_color(image[3 * i1][3 * j1 + 1], image[3 * i2][3 * j1 + 1], image[3 * i1][3 * j2 + 1], image[3 * i2][3 * j2 + 1], di, dj);
    valB = interpolate_color(image[3 * i1][3 * j1 + 2], image[3 * i2][3 * j1 + 2], image[3 * i1][3 * j2 + 2], image[3 * i2][3 * j2 + 2], di, dj);
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *  ??
 *
 *  @details
 */
void bilinearRedim299(ImageBase &image, ImageBase &o_image)
{
    float ratio_w = (image.getWidth() - 1) / 299.;
    float ratio_h = (image.getHeight() - 1) / 299.;

    for (int i = 0; i < 299; ++i)
    {
        for (int j = 0; j < 299; ++j)
        {
            float original_i = i * ratio_h;
            float original_j = j * ratio_w;

            int R, G, B;
            interpolate_bilinear(image, R, G, B, original_i, original_j);
            o_image[3 * i][3 * j + 0] = R;
            o_image[3 * i][3 * j + 1] = G;
            o_image[3 * i][3 * j + 2] = B;
        }
    }
}

//====================== Histogram ======================//

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *  Calcule les histogrammes des composantes couleur d'une image pass�e en entr�e
 *
 *  @details
 */
void computeColorHist(ImageBase &image, int histR[256], int histG[256], int histB[256])
{
    for (int v = 0; v < 256; ++v)
    {
        histR[v] = 0;
        histG[v] = 0;
        histB[v] = 0;
    }
    for (int i = 0; i < image.getHeight(); ++i)
        for (int j = 0; j < image.getWidth(); ++j)
        {
            histR[image[3 * i][3 * j + 0]] += 1;
            histG[image[3 * i][3 * j + 1]] += 1;
            histB[image[3 * i][3 * j + 2]] += 1;
        }
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *  Compare les histogrammes de deux images
 *
 *  @details
 */
void compareImagesByHist(ImageBase &image1, ImageBase &image2)
{
    bool isSame = true;
    int histR1[256], histG1[256], histB1[256];
    computeColorHist(image1, histR1, histG1, histB1);
    int histR2[256], histG2[256], histB2[256];
    computeColorHist(image2, histR2, histG2, histB2);
    for (int v = 0; v < 256; ++v)
    {
        if (histR1[v] != histR2[v] || histG1[v] != histG2[v] || histB1[v] != histB2[v])
            isSame = false;
    }
    printf("Memes histogrammes ? %i", isSame);
}

//====================== Gaussian blurring ======================//

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *  G�n�re un kernel de flou gaussien selon la taille et le sigma pass�s en param�tres
 *
 *  @details
 */
void generateGaussianKernel(std::vector<std::vector<float>> &kernel, int size, float sigma)
{
    float sum = 0.0;
    for (int y = -size / 2; y <= size / 2; ++y)
    {
        for (int x = -size / 2; x <= size / 2; ++x)
        {
            float value = exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            kernel[y + size / 2][x + size / 2] = value;
            sum += value;
        }
    }
    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            kernel[y][x] /= sum;
        }
    }
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *  Applique un flou gaussien � l'image d'entr�e, sur l'image de sortie
 *
 *  @details
 */
void gaussianBlur(ImageBase &image, ImageBase &o_image, int kernelSize, float sigma)
{
    std::vector<std::vector<float>> kernel(kernelSize, std::vector<float>(kernelSize));
    generateGaussianKernel(kernel, kernelSize, sigma);

    int height, width;
    height = image.getHeight();
    width = image.getWidth();

    for (unsigned int i = 0; i < height; ++i)
    {
        for (unsigned int j = 0; j < width; ++j)
        {
            float r = 0.0, g = 0.0, b = 0.0;

            for (int ki = -kernelSize / 2; ki <= kernelSize / 2; ++ki)
            {
                for (int kj = -kernelSize / 2; kj <= kernelSize / 2; ++kj)
                {
                    int pi = i + ki;
                    int pj = j + kj;

                    if (pi >= 0 && pi < height && pj >= 0 && pj < width)
                    {
                        float weight = kernel[ki + kernelSize / 2][kj + kernelSize / 2];
                        r += image[3 * pi][3 * pj + 0] * weight;
                        g += image[3 * pi][3 * pj + 1] * weight;
                        b += image[3 * pi][3 * pj + 2] * weight;
                    }
                }
            }
            o_image[3 * i][3 * j + 0] = static_cast<unsigned int>(r);
            o_image[3 * i][3 * j + 1] = static_cast<unsigned int>(g);
            o_image[3 * i][3 * j + 2] = static_cast<unsigned int>(b);
        }
    }
}

//====================== Average blurring ======================//

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void averageBlurring(ImageBase &image, ImageBase &o_image, int regionSize)
{
    int sum_R, sum_G, sum_B, nbV;
    for (int i = 0; i < image.getHeight(); ++i)
        for (int j = 0; j < image.getWidth(); ++j)
        {
            sum_R = 0;
            sum_G = 0;
            sum_B = 0;
            nbV = 0;
            for (int v_i = -regionSize / 2; v_i <= regionSize / 2; ++v_i)
                for (int v_j = -regionSize / 2; v_j <= regionSize / 2; ++v_j)
                    if (!(i + v_i < 0 || i + v_i >= image.getHeight() || j + v_j < 0 || j + v_j >= image.getWidth()))
                    {
                        sum_R += image[3 * (i + v_i)][3 * (j + v_j) + 0];
                        sum_G += image[3 * (i + v_i)][3 * (j + v_j) + 1];
                        sum_B += image[3 * (i + v_i)][3 * (j + v_j) + 2];
                        ++nbV;
                    }
            o_image[3 * i][3 * j + 0] = sum_R / nbV;
            o_image[3 * i][3 * j + 1] = sum_G / nbV;
            o_image[3 * i][3 * j + 2] = sum_B / nbV;
        }
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void newAverageBlurring(ImageBase &image, std::vector<ImageBase> &o_images)
{
    int imageWidth = image.getWidth();
    int imageHeight = image.getHeight();

    o_images.clear();
    for (int img_i = 0; img_i < 51; ++img_i) // Générer 51 images floues avec différents niveaux de flou via step
        o_images.push_back(ImageBase(image.getWidth(), image.getHeight(), image.getColor()));

    for (int i = 0; i < imageHeight; ++i)
        for (int j = 0; j < imageWidth; ++j)
        {
            int sum_R = 0, sum_G = 0, sum_B = 0, nbV = 0;
            for (int r = 1; r <= 101; r += 2)
            {                     
                int step = r / 2;
                for (int v_i = -step; v_i <= step; ++v_i)
                {
                    if (v_i == -step || v_i == step)
                    {
                        for (int v_j = -step; v_j <= step; ++v_j)
                            if (!(i + v_i < 0 || i + v_i >= image.getHeight() || j + v_j < 0 ||
                                  j + v_j >= image.getWidth()))
                            {
                                sum_R += image[3 * (i + v_i)][3 * (j + v_j) + 0]; // Somme des valeurs des pixels voisins
                                sum_G += image[3 * (i + v_i)][3 * (j + v_j) + 1];
                                sum_B += image[3 * (i + v_i)][3 * (j + v_j) + 2];
                                ++nbV;
                            }
                    }
                    else
                    {
                        int v_j = -step;
                        if (!(i + v_i < 0 || i + v_i >= image.getHeight() || j + v_j < 0 ||
                              j + v_j >= image.getWidth()))
                        {
                            sum_R += image[3 * (i + v_i)][3 * (j + v_j) + 0];
                            sum_G += image[3 * (i + v_i)][3 * (j + v_j) + 1];
                            sum_B += image[3 * (i + v_i)][3 * (j + v_j) + 2];
                            ++nbV;
                        }
                        v_j = step;
                        if (!(i + v_i < 0 || i + v_i >= image.getHeight() || j + v_j < 0 ||
                              j + v_j >= image.getWidth()))
                        {
                            sum_R += image[3 * (i + v_i)][3 * (j + v_j) + 0];
                            sum_G += image[3 * (i + v_i)][3 * (j + v_j) + 1];
                            sum_B += image[3 * (i + v_i)][3 * (j + v_j) + 2];
                            ++nbV;
                        }
                    }
                }
                o_images[r / 2][3 * i][3 * j + 0] = sum_R / nbV; // QUESTION : Pourquoi on divise r ? => Pour revenir à 0,1,2, ...
                o_images[r / 2][3 * i][3 * j + 1] = sum_G / nbV;
                o_images[r / 2][3 * i][3 * j + 2] = sum_B / nbV;
            }
        }
}

//====================== Scrambling ======================//

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void areaScrambling(ImageBase &image, ImageBase &o_image, int start_i, int start_j, int area_h, int area_w)
{
    int nbPixels = area_h * area_w;
    std::random_device randev;
    std::mt19937 rng(randev()); // QUESTION : Qu'est-ce que rng ?
                                //  => Générateur de pseudo-aléatoire.
    std::uniform_int_distribution<unsigned int> distrbit(0, nbPixels - 1); // QUESTION : A quoi ça sert ?
                                                                           //=> La distribution uniforme distrbit est utilisée pour choisir de manière
                                                                           // aléatoire un pixel dans la région en cours de mélange.
    ImageBase unavailability(area_w, area_h, false); // QUESTION : ?
                                                     //  => Image binaire pour marquer les pixels déjà mélangés.
    for (int i = 0; i < area_h; ++i)
        for (int j = 0; j < area_w; ++j)
        {
            int randIdx = distrbit(rng);
            int randJ = randIdx % area_w;
            int randI = (randIdx - randJ) / area_w;
            while (unavailability[randI][randJ] == 1)
            {
                randIdx = (randIdx == nbPixels - 1 ? 0 : randIdx + 1);
                randJ = randIdx % area_w;
                randI = (randIdx - randJ) / area_w;
            }
            unavailability[randI][randJ] = 1;
            o_image[3 * (start_i + randI)][3 * (start_j + randJ) + 0] = image[3 * (start_i + i)][3 * (start_j + j) + 0];
            o_image[3 * (start_i + randI)][3 * (start_j + randJ) + 1] = image[3 * (start_i + i)][3 * (start_j + j) + 1];
            o_image[3 * (start_i + randI)][3 * (start_j + randJ) + 2] = image[3 * (start_i + i)][3 * (start_j + j) + 2];
        }
}

//====================== Averager ======================//

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void areaAverager(ImageBase &image, ImageBase &o_image, int start_i, int start_j, int area_h, int area_w)
{
    int nbPixels = area_h * area_w;
    int sum_R = 0, sum_G = 0, sum_B = 0;
    for (int i = start_i; i < start_i + area_h; ++i)
        for (int j = start_j; j < start_j + area_w; ++j)
        {
            sum_R += image[3 * i][3 * j + 0];
            sum_G += image[3 * i][3 * j + 1];
            sum_B += image[3 * i][3 * j + 2];
        }
    int val_R = sum_R / nbPixels, val_G = sum_G / nbPixels, val_B = sum_B / nbPixels;
    for (int i = start_i; i < start_i + area_h; ++i)
        for (int j = start_j; j < start_j + area_w; ++j)
        {
            o_image[3 * i][3 * j + 0] = val_R;
            o_image[3 * i][3 * j + 1] = val_G;
            o_image[3 * i][3 * j + 2] = val_B;
        }
}

//====================== Encryption ======================//

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *  Applique un flou selectif progressif � l'ensemble des pixels (on applique un XOR � chaque pixel de gauche �
 * droite (dir == 0) ou de droite � gauche (dir == 1) et stocke les images respectives dans o_images
 *
 *  @details
 */
void selectiveProgressiveEncryption(ImageBase &image, ImageBase o_images[8], bool MSBtoLSB)
{
    unsigned int bSeq[8];
    int height, width;
    height = image.getHeight();
    width = image.getWidth();
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            genPRNS(bSeq);
            std::bitset<8> pBits_R(image[3 * i][3 * j + 0]);
            std::bitset<8> pBits_G(image[3 * i][3 * j + 1]);
            std::bitset<8> pBits_B(image[3 * i][3 * j + 2]);
            for (int b = 0; b < 8; ++b)
            {
                if (MSBtoLSB)
                {
                    pBits_R[7 - b] = (pBits_R[7 - b] ^ bSeq[b]);
                    pBits_G[7 - b] = (pBits_G[7 - b] ^ bSeq[b]);
                    pBits_B[7 - b] = (pBits_B[7 - b] ^ bSeq[b]);
                }
                else
                {
                    pBits_R[b] = (pBits_R[b] ^ bSeq[7 - b]);
                    pBits_G[b] = (pBits_G[b] ^ bSeq[7 - b]);
                    pBits_B[b] = (pBits_B[b] ^ bSeq[7 - b]);
                }
                o_images[b][3 * i][3 * j + 0] = pBits_R.to_ulong();
                o_images[b][3 * i][3 * j + 1] = pBits_G.to_ulong();
                o_images[b][3 * i][3 * j + 2] = pBits_B.to_ulong();
            }
        }
    }
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void selectiveIndividualEncryption(ImageBase &image, ImageBase o_images[8])
{
    unsigned int bSeq[8];
    int height, width;
    height = image.getHeight();
    width = image.getWidth();
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            genPRNS(bSeq);
            std::bitset<8> pBits_R(image[3 * i][3 * j + 0]);
            std::bitset<8> pBits_G(image[3 * i][3 * j + 1]);
            std::bitset<8> pBits_B(image[3 * i][3 * j + 2]);
            for (int b = 0; b < 8; ++b)
            {
                std::bitset<8> newPBits_R = pBits_R;
                std::bitset<8> newPBits_G = pBits_G;
                std::bitset<8> newPBits_B = pBits_B;
                newPBits_R[b] = (pBits_R[b] ^ bSeq[7 - b]);
                newPBits_G[b] = (pBits_G[b] ^ bSeq[7 - b]);
                newPBits_B[b] = (pBits_B[b] ^ bSeq[7 - b]);
                o_images[b][3 * i][3 * j + 0] = newPBits_R.to_ulong();
                o_images[b][3 * i][3 * j + 1] = newPBits_G.to_ulong();
                o_images[b][3 * i][3 * j + 2] = newPBits_B.to_ulong();
            }
        }
    }
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void selectiveGroupEncryption(ImageBase &image, ImageBase &o_image, int bitsGroup[8], int groupSize)
{
    unsigned int bSeq[8];
    int height, width;
    height = image.getHeight();
    width = image.getWidth();

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            genPRNS(bSeq);
            std::bitset<8> pBits_R(image[3 * i][3 * j + 0]);
            std::bitset<8> pBits_G(image[3 * i][3 * j + 1]);
            std::bitset<8> pBits_B(image[3 * i][3 * j + 2]);
            for (int b_i = 0; b_i < groupSize; ++b_i)
            {
                int b = bitsGroup[b_i];
                pBits_R[b] = (pBits_R[b] ^ bSeq[7 - b]);
                pBits_G[b] = (pBits_G[b] ^ bSeq[7 - b]);
                pBits_B[b] = (pBits_B[b] ^ bSeq[7 - b]);
            }
            o_image[3 * i][3 * j + 0] = pBits_R.to_ulong();
            o_image[3 * i][3 * j + 1] = pBits_G.to_ulong();
            o_image[3 * i][3 * j + 2] = pBits_B.to_ulong();
        }
    }
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
double computePSNR(ImageBase &image1, ImageBase &image2)
{
    double mse = 0;
    double maxIntensity = 255.0;

    if (image1.getHeight() != image2.getHeight() || image1.getWidth() != image2.getWidth())
    {
        printf("Les images ne sont pas de la m�me taille !\n");
        return -1;
    }

    for (int i = 0; i < image1.getHeight(); ++i)
        for (int j = 0; j < image1.getWidth(); ++j)
            for (int c = 0; c < 3; ++c)
                mse += pow((image1[3 * i][3 * j + c] - image2[3 * i][3 * j + c]), 2);

    mse /= (image1.getHeight() * image1.getWidth() * 3);
    double psnr = 10 * log10(pow(maxIntensity, 2) / mse);
    return psnr;
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void computePSNRforAllAlterations(std::vector<double> &PSNRArray, const char *baseName, int i_min, int i_max, int step)
{
    char filePath[200];
    std::strcpy(filePath, baseName);
    std::strcat(filePath, (char *)"base.ppm");
    ImageBase imBase, imAlt;
    imBase.load(filePath);
    double val_PSNR;
    for (int i = i_min; i <= i_max; i += step)
    {
        sprintf(filePath, "%s%d", baseName, i);
        std::strcat(filePath, (char *)".ppm");
        imAlt.load(filePath);
        val_PSNR = computePSNR(imBase, imAlt);
        PSNRArray.push_back(val_PSNR);
    }
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void writeDataOnTxt(std::vector<double> &data, std::string filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (double val : data)
        {
            file << val << std::endl;
        }
        file.close();
        std::cout << "L'ecriture a ete achevee correctement !" << std::endl;
    }
    else
    {
        std::cerr << "Ouverture du fichier impossible !" << std::endl;
    }
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
void RGB2GREY(ImageBase &imColor, ImageBase &imGrey)
{
    for (int i = 0; i < imColor.getHeight(); ++i)
        for (int j = 0; j < imColor.getWidth(); ++j)
            imGrey[i][j] = 0.299 * imColor[3 * i][3 * j] + 0.587 * imColor[3 * i][3 * j + 1] + 0.114 * imColor[3 * i][3 * j + 2];
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
double computeImageMean(ImageBase &image)
{
    double sum = 0.;
    for (int i = 0; i < image.getHeight(); ++i)
        for (int j = 0; j < image.getWidth(); ++j)
            sum += image[i][j];
    return sum / (image.getWidth() * image.getHeight());
}

/**
 *  @brief
 *  @param
 *  @author Norman Hutte
 *  @date 06/03/2024
 *
 *
 *
 *  @details
 */
double computeSSIM(ImageBase &image1, ImageBase &image2)
{
    ImageBase image1grey(image1.getWidth(), image1.getHeight(), false);
    ImageBase image2grey(image1.getWidth(), image1.getHeight(), false);
    RGB2GREY(image1, image1grey);
    RGB2GREY(image2, image2grey);

    return 0.;
}

#endif // STAGE_IMAGE_FUNCTIONS_H
