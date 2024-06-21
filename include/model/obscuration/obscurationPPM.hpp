/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : obscurationPPM.h
 *
 * Description : Header of class that implement obscuration for PPM images.
 *
 * Author : Norman HUTTE
 *
 * Mail : ?
 *
 * Date : 06 March 2024
 *
 *******************************************************************************/

#include "../image/ImageBase.hpp"
#include "obscurationCommon.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <cstring>
#include <fstream>

#ifndef STAGE_IMAGE_FUNCTIONS_H
#define STAGE_IMAGE_FUNCTIONS_H

#define M_PI 3.14159265358979323846

/**
 * \class obscurationPPM
 * \brief This class implements various image obscuration techniques for the PPM image format.
 * \details subclass obscurationCommon
 * \author Norman Hutte
 * \date 6 March 2024
 */
class obscurationPPM : public obscurationCommon
{

    //====================== Interpolate ======================//

    /**
     *  \brief Interpolates the color value of a pixel at a given position using bilinear interpolation.
     *  \param p11 The color value at the top-left corner of the interpolation rectangle.
     *  \param p21 The color value at the top-right corner of the interpolation rectangle.
     *  \param p12 The color value at the bottom-left corner of the interpolation rectangle.
     *  \param p22 The color value at the bottom-right corner of the interpolation rectangle.
     *  \param dx The horizontal distance from the top-left corner of the interpolation rectangle to the target position.
     *  \param dy The vertical distance from the top-left corner of the interpolation rectangle to the target position.
     *  \return The interpolated color value.
     *  \author Norman Hutte
     *  \date 6 March 2024
     */
    static int interpolate_color(int p11, int p21, int p12, int p22, float dx, float dy);

    /**
     *  \brief Interpolates the color values of a pixel at a given position in an image using bilinear interpolation.
     *  \param image The input image.
     *  \param valR The interpolated red color value.
     *  \param valG The interpolated green color value.
     *  \param valB The interpolated blue color value.
     *  \param i The vertical coordinate of the target position.
     *  \param j The horizontal coordinate of the target position.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void interpolate_bilinear(ImageBase &image, int &valR, int &valG, int &valB, float i, float j);

    /**
     *  \brief Resizes an image to 299x299 pixels using bilinear interpolation.
     *  \param image The input image.
     *  \param o_image The output image.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void bilinearRedim299(ImageBase &image, ImageBase &o_image);

    //====================== Histogram ======================//

    /**
     *  \brief Computes the histograms of the red, green, and blue color components of an image.
     *  \param image The input image.
     *  \param histR The histogram of the red color component.
     *  \param histG The histogram of the green color component.
     *  \param histB The histogram of the blue color component.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void computeColorHist(ImageBase &image, int histR[256], int histG[256], int histB[256]);

    /**
     *  \brief Compares the histograms of two images.
     *  \param image1 The first image.
     *  \param image2 The second image.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void compareImagesByHist(ImageBase &image1, ImageBase &image2);

    //====================== Gaussian blurring ======================//

    /**
     *  \brief Generates a Gaussian kernel for image blurring.
     *  \param kernel The output kernel.
     *  \param size The size of the kernel.
     *  \param sigma The standard deviation of the Gaussian distribution.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void generateGaussianKernel(std::vector<std::vector<float>> &kernel, int size, float sigma);

    /**
     *  \brief Applies Gaussian blurring to an image using a given kernel size and standard deviation.
     *  \param image The input image.
     *  \param o_image The output image.
     *  \param kernelSize The size of the Gaussian kernel.
     *  \param sigma The standard deviation of the Gaussian distribution.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void gaussianBlur(ImageBase &image, ImageBase &o_image, int kernelSize, float sigma);

    //====================== Average blurring ======================//

    /**
     *  \brief Applies average blurring to an image using a given region size.
     *  \param image The input image.
     *  \param o_image The output image.
     *  \param regionSize The size of the averaging region.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void averageBlurring(ImageBase &image, ImageBase &o_image, int regionSize);

    /**
     *  \brief Applies new average blurring to an image using a given number of images.
     *  \param image The input image.
     *  \param o_images The output images.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void newAverageBlurring(ImageBase &image, std::vector<ImageBase> &o_images);

    //====================== Scrambling ======================//

    /**
     *  \brief Applies area scrambling to an image using a given start position and area size.
     *  \param image The input image.
     *  \param o_image The output image.
     *  \param start_i The vertical start position of the scrambling area.
     *  \param start_j The horizontal start position of the scrambling area.
     *  \param area_h The height of the scrambling area.
     *  \param area_w The width of the scrambling area.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void areaScrambling(ImageBase &image, ImageBase &o_image, int start_i, int start_j, int area_h, int area_w);

    /**
     *  \brief Applies scrambling to an image using a given region size.
     *  \param image The input image.
     *  \param o_image The output image.
     *  \param regionHeight The height of the scrambling region.
     *  \param regionWidth The width of the scrambling region.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void scrambling(ImageBase &image, ImageBase &o_image, int regionHeight, int regionWidth);

    //====================== Averager ======================//

    /**
     *  \brief Applies area averaging to an image using a given start position and area size.
     *  \param image The input image.
     *  \param o_image The output image.
     *  \param start_i The vertical start position of the averaging area.
     *  \param start_j The horizontal start position of the averaging area.
     *  \param area_h The height of the averaging area.
     *  \param area_w The width of the averaging area.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void areaAverager(ImageBase &image, ImageBase &o_image, int start_i, int start_j, int area_h, int area_w);

    /**
     *  \brief Applies average by region to an image using a given region size.
     *  \param image The input image.
     *  \param o_image The output image.
     *  \param regionHeight The height of the averaging region.
     *  \param regionWidth The width of the averaging region.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void averageByRegion(ImageBase &image, ImageBase &o_image, int regionHeight, int regionWidth);

    //====================== Encryption ======================//

    /**
     *  \brief Applies selective progressive encryption to an image using a given encryption direction.
     *  \param image The input image.
     *  \param o_images The output images.
     *  \param MSBtoLSB The encryption direction (true for MSB to LSB, false for LSB to MSB).
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void selectiveProgressiveEncryption(ImageBase &image, ImageBase o_images[8], bool MSBtoLSB);

    /**
     *  \brief Applies selective individual encryption to an image.
     *  \param image The input image.
     *  \param o_images The output images.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void selectiveIndividualEncryption(ImageBase &image, ImageBase o_images[8]);

    /**
     *  \brief Applies selective group encryption to an image using a given bit group and group size.
     *  \param image The input image.
     *  \param o_image The output image.
     *  \param bitsGroup The bit group to encrypt.
     *  \param groupSize The size of the bit group.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void selectiveGroupEncryption(ImageBase &image, ImageBase &o_image, int bitsGroup[8], int groupSize);

    /**
     *  \brief Computes the peak signal-to-noise ratio (PSNR) between two images.
     *  \param image1 The first image.
     *  \param image2 The second image.
     *  \return The PSNR value.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static double computePSNR(ImageBase &image1, ImageBase &image2);

    /**
     *  \brief Computes the PSNR for all alterations in a given range.
     *  \param PSNRArray The output array of PSNR values.
     *  \param baseName The base name of the input files.
     *  \param i_min The minimum alteration index.
     *  \param i_max The maximum alteration index.
     *  \param step The step size between alteration indices.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void computePSNRforAllAlterations(std::vector<double> &PSNRArray, const char *baseName, int i_min, int i_max, int step);

    /**
     *  \brief Writes data to a text file.
     *  \param data The data to write.
     *  \param filename The name of the output file.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void writeDataOnTxt(std::vector<double> &data, std::string filename);

    /**
     *  \brief Converts an RGB image to grayscale.
     *  \param imColor The input RGB image.
     *  \param imGrey The output grayscale image.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static void RGB2GREY(ImageBase &imColor, ImageBase &imGrey);

    /**
     *  \brief Computes the mean value of an image.
     *  \param image The input image.
     *  \return The mean value.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static double computeImageMean(ImageBase &image);

    /**
     *  \brief Computes the structural similarity index (SSIM) between two images.
     *  \param image1 The first image.
     *  \param image2 The second image.
     *  \return The SSIM value.
     *  \author Norman Hutte
     *  \date 06/03/2024
     */
    static double computeSSIM(ImageBase &image1, ImageBase &image2);
}

#endif // STAGE_IMAGE_FUNCTIONS_H
