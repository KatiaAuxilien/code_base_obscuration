/**
 * @file ObscurationPGM.hpp
 * @brief This library provides functions to obscure images in the PGM format.
 * The functions are inspired by Norman Hutte's methods for PPM images.
 * @authors Katia Auxilien, Norman Hutte
 * @date April 2024
 * @details 
 */
#include "obscurationCommon.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <string>

#ifndef OBSCURATION_PGM_LIBRARY
#define OBSCURATION_PGM_LIBRARY

/**
 * \class obscurationPGM
 * \brief A subclass of obscurationCommon for obscuring images in the PGM format.
 * \details This class provides functions to obscure images in the PGM format,
 * inspired by Norman Hutte's methods for PPM images.
 * \authors Katia Auxilien, Norman Hutte
 * \date April 2024
 */
class obscurationPGM : public obscurationCommon
{
public:
    //====================== Interpolate ======================//
    /**
     *  \brief Interpolates a greyscale value between four neighboring pixels.
     *  \details Inspired by Norman Hutte's method interpolate_color.
     *  \param p11 The top-left pixel value.
     *  \param p21 The top-right pixel value.
     *  \param p12 The bottom-left pixel value.
     *  \param p22 The bottom-right pixel value.
     *  \param dx The distance between the desired point and the top-left pixel along the x-axis.
     *  \param dy The distance between the desired point and the top-left pixel along the y-axis.
     *  \return The interpolated greyscale value.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 12 April 2024
     */
    static int interpolate_grey(int p11, int p21, int p12, int p22, float dx, float dy);

    /**
     *  \brief Interpolates a greyscale value at a specific point in an image using bilinear interpolation.
     *  \details Inspired by Norman Hutte's method interpolate_bilinear.
     *  \param image The image to interpolate.
     *  \param valV The interpolated greyscale value.
     *  \param i The x-coordinate of the point to interpolate.
     *  \param j The y-coordinate of the point to interpolate.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 12 April 2024
     */
    static void interpolate_bilinear_PGM(ImageBase &image, int &valV, float i, float j);

    /**
     *  \brief Resizes an image to 299x299 pixels using bilinear interpolation.
     *  \details Inspired by Norman Hutte's method bilinearRedim299.
     *  \param image The image to resize.
     *  \param o_image The resized image.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 12 April 2024
     */
    static void bilinearRedim299_PGM(ImageBase &image, ImageBase &o_image);

    //====================== Average blurring ======================//

    /**
     *  \brief Applies average blurring to an image.
     *  \details Inspired by Norman Hutte's method newAverageBlurring.
     *  \param image The image to blur.
     *  \param o_images The blurred images.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 11 April 2024
     */
    static void newAverageBlurring_PGM(ImageBase &image, std::vector<ImageBase> &o_images);

    //====================== Scrambling ======================//

    /**
     *  \brief Scrambles the pixels in a specific area of an image.
     *  \details Inspired by Norman Hutte's method areaScrambling.
     *  \param image The image to scramble.
     *  \param o_image The scrambled image.
     *  \param start_i The starting row of the area to scramble.
     *  \param start_j The starting column of the area to scramble.
     *  \param area_h The height of the area to scramble.
     *  \param area_w The width of the area to scramble.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 12 April 2024
     */
    static void areaScrambling_PGM(ImageBase &image, ImageBase &o_image, int start_i, int start_j, int area_h, int area_w);

    /**
     *  \brief Scrambles the pixels in an image.
     *  \details Inspired by Norman Hutte's method scrambling.
     *  \param image The image to scramble.
     *  \param o_image The scrambled image.
     *  \param regionHeight The height of the regions to scramble.
     *  \param regionWidth The width of the regions to scramble.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 12 April 2024
     */
    static void scrambling_PGM(ImageBase &image, ImageBase &o_image, int regionHeight, int regionWidth);

    //====================== Averager ======================//

    /**
     *  \brief Applies averaging to a specific area of an image.
     *  \details Inspired by Norman Hutte's method areaAverager.
     *  \param image The image to average.
     *  \param o_image The averaged image.
     *  \param start_i The starting row of the area to average.
     *  \param start_j The starting column of the area to average.
     *  \param area_h The height of the area to average.
     *  \param area_w The width of the area to average.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 12 April 2024
     */
    static void areaAverager_PGM(ImageBase &image, ImageBase &o_image, int start_i, int start_j, int area_h, int area_w);

    /**
     *  \brief Applies averaging to an image.
     *  \details Inspired by Norman Hutte's method averageByRegion.
     *  \param image The image to average.
     *  \param o_image The averaged image.
     *  \param regionHeight The height of the regions to average.
     *  \param regionWidth The width of the regions to average.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 12 April 2024
     */
    static void averageByRegion_PGM(ImageBase &image, ImageBase &o_image, int regionHeight, int regionWidth);

    //====================== Encryption ======================//

    /**
     *  \brief Encrypts an image using selective individual encryption.
     *  \details Inspired by Norman Hutte's method selectiveIndividualEncryption.
     *  \param image The image to encrypt.
     *  \param o_images The encrypted images.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 15 April 2024
     */
    static void selectiveIndividualEncryption_PGM(ImageBase &image, ImageBase o_images[8]);

    /**
     *  \brief Encrypts an image using selective progressive encryption.
     *  \details Inspired by Norman Hutte's method selectiveProgressiveEncryption.
     *  \param image The image to encrypt.
     *  \param o_images The encrypted images.
     *  \param MSBtoLSB Whether to encrypt from MSB to LSB or vice versa.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 15 April 2024
     */
    static void selectiveProgressiveEncryption_PGM(ImageBase &image, ImageBase o_images[8], bool MSBtoLSB);

    /**
     *  \brief Encrypts an image using selective group encryption.
     *  \details Inspired by Norman Hutte's method selectiveGroupEncryption.
     *  \param image The image to encrypt.
     *  \param o_image The encrypted image.
     *  \param bitsGroup The group of bits to encrypt.
     *  \param groupSize The size of the group of bits to encrypt.
     *  \authors Katia Auxilien, Norman Hutte
     *  \date 15 April 2024
     */
    static void selectiveGroupEncryption_PGM(ImageBase &image, ImageBase &o_image, int bitsGroup[8], int groupSize);
};

#endif // OBSCURATION_PGM_LIBRARY