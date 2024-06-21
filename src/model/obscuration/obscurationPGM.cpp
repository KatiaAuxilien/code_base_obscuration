/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : ObscurationPGM.cpp
 *
 * Description : Implement functions to obscure images in the PGM format.
 *              The functions are inspired by Norman Hutte's methods for PPM images.
 *
 * Authors : Katia Auxilien, Norman Hutte
 *
 * Mail : katia.auxilien@mail.fr, ?
 *
 * Date : Avril 2024
 *
 *******************************************************************************/

#include "../../../include/model/obscuration/obscurationPGM.hpp"

//====================== Interpolate ======================//
int obscurationPGM::interpolate_grey(int p11, int p21, int p12, int p22, float dx, float dy)
{
    float interpolated_value =
        p11 * (1 - dx) * (1 - dy) +
        p21 * dx * (1 - dy) +
        p12 * (1 - dx) * dy +
        p22 * dx * dy;
    return static_cast<int>(interpolated_value);
}

void obscurationPGM::interpolate_bilinear_PGM(ImageBase &image, int &valV, float i, float j)
{
    int i1 = static_cast<int>(i), j1 = static_cast<int>(j);
    int i2 = i + 1,
        j2 = j + 1;
    float di = i - i1,
          dj = j - j1;

    valV = interpolate_grey(image[i1][j1], image[i2][j1], image[i1][j2], image[i2][j2], di, dj);
}

void obscurationPGM::bilinearRedim299_PGM(ImageBase &image, ImageBase &o_image)
{
    float ratio_w = (image.getWidth() - 1) / 299.;
    float ratio_h = (image.getHeight() - 1) / 299.;

    for (int i = 0; i < 299; ++i)
    {
        for (int j = 0; j < 299; ++j)
        {
            float original_i = i * ratio_h;
            float original_j = j * ratio_w;

            int V;
            interpolate_bilinear_PGM(image, V, original_i, original_j);
            o_image[i][j + 0] = V;
        }
    }
}

//====================== Average blurring ======================//

void obscurationPGM::newAverageBlurring_PGM(ImageBase &image, std::vector<ImageBase> &o_images)
{
    int imageWidth = image.getWidth();
    int imageHeight = image.getHeight();

    o_images.clear();
    for (int img_i = 0; img_i < 51; ++img_i) // Générer 51 images floues avec différents niveaux de flou via step
    {
        o_images.push_back(ImageBase(image.getWidth(), image.getHeight(), image.getColor()));
    }

    for (int i = 0; i < imageHeight; ++i)
    {
        for (int j = 0; j < imageWidth; ++j)
        {
            int sumV = 0, nbV = 0;
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
                                sumV += image[i + v_i][j + v_j];
                                ++nbV;
                            }
                    }
                    else
                    {
                        int v_j = -step;
                        if (!(i + v_i < 0 || i + v_i >= image.getHeight() || j + v_j < 0 ||
                              j + v_j >= image.getWidth()))
                        {
                            sumV += image[i + v_i][j + v_j];
                            ++nbV;
                        }
                        v_j = step;
                        if (!(i + v_i < 0 || i + v_i >= image.getHeight() || j + v_j < 0 ||
                              j + v_j >= image.getWidth()))
                        {
                            sumV += image[i + v_i][j + v_j];
                            ++nbV;
                        }
                    }
                }
                o_images[r / 2][i][j] = sumV / nbV;
            }
        }
    }
}

//====================== Scrambling ======================//

void obscurationPGM::areaScrambling_PGM(ImageBase &image, ImageBase &o_image, int start_i, int start_j, int area_h, int area_w)
{
    int nbPixels = area_h * area_w;
    std::random_device randev;
    std::mt19937 rng(randev());
    std::uniform_int_distribution<unsigned int> distrbit(0, nbPixels - 1);
    ImageBase unavailability(area_w, area_h, false);
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
            o_image[start_i + randI][start_j + randJ] = image[start_i + i][start_j + j];
        }
}

void obscurationPGM::scrambling_PGM(ImageBase &image, ImageBase &o_image, int regionHeight, int regionWidth)
{
    int current_i = 0, current_j = 0;
    int height, width;
    height = image.getHeight();
    width = image.getWidth();
    int area_h, area_w;
    while (current_i < height)
    {
        area_h = (current_i + regionHeight <= height ? regionHeight : height - current_i);
        area_w = (current_j + regionWidth <= width ? regionWidth : width - current_j);
        areaScrambling_PGM(image, o_image, current_i, current_j, area_h, area_w);
        current_j += area_w;
        if (current_j == width)
        {
            current_j = 0;
            current_i = (current_i + regionHeight <= height ? current_i + regionHeight : height);
        }
    }
}

//====================== Averager ======================//

void obscurationPGM::areaAverager_PGM(ImageBase &image, ImageBase &o_image, int start_i, int start_j, int area_h, int area_w)
{
    int nbPixels = area_h * area_w;
    int sum_V = 0;
    for (int i = start_i; i < start_i + area_h; ++i)
        for (int j = start_j; j < start_j + area_w; ++j)
        {
            sum_V += image[i][j];
        }
    int val_V = sum_V / nbPixels;
    for (int i = start_i; i < start_i + area_h; ++i)
        for (int j = start_j; j < start_j + area_w; ++j)
        {
            o_image[i][j] = val_V;
        }
}

void obscurationPGM::averageByRegion_PGM(ImageBase &image, ImageBase &o_image, int regionHeight, int regionWidth)
{
    int current_i = 0, current_j = 0;
    int height, width;
    height = image.getHeight();
    width = image.getWidth();
    int area_h, area_w;
    while (current_i < height)
    {
        area_h = (current_i + regionHeight <= height ? regionHeight : height - current_i);
        area_w = (current_j + regionWidth <= width ? regionWidth : width - current_j);
        areaAverager_PGM(image, o_image, current_i, current_j, area_h, area_w);
        current_j += area_w;
        if (current_j == width)
        {
            current_j = 0;
            current_i = (current_i + regionHeight <= height ? current_i + regionHeight : height);
        }
    }
}

//====================== Encryption ======================//

void obscurationPGM::selectiveIndividualEncryption_PGM(ImageBase &image, ImageBase o_images[8])
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
            std::bitset<8> pBits_V(image[i][j + 0]);
            for (int b = 0; b < 8; ++b)
            {
                std::bitset<8> newPBits_V = pBits_V;
                newPBits_V[b] = (pBits_V[b] ^ bSeq[7 - b]);
                o_images[b][i][j + 0] = newPBits_V.to_ulong();
            }
        }
    }
}

void obscurationPGM::selectiveProgressiveEncryption_PGM(ImageBase &image, ImageBase o_images[8], bool MSBtoLSB)
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
            std::bitset<8> pBits_V(image[i][j]);
            for (int b = 0; b < 8; ++b)
            {
                if (MSBtoLSB)
                {
                    pBits_V[7 - b] = (pBits_V[7 - b] ^ bSeq[b]);
                }
                else
                {
                    pBits_V[b] = (pBits_V[b] ^ bSeq[7 - b]);
                }
                o_images[b][i][j + 0] = pBits_V.to_ulong();
            }
        }
    }
}

void obscurationPGM::selectiveGroupEncryption_PGM(ImageBase &image, ImageBase &o_image, int bitsGroup[8], int groupSize)
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
            std::bitset<8> pBits_V(image[i][j]);
            for (int b_i = 0; b_i < groupSize; ++b_i)
            {
                int b = bitsGroup[b_i];
                pBits_V[b] = (pBits_V[b] ^ bSeq[7 - b]);
            }
            o_image[i][j] = pBits_V.to_ulong();
        }
    }
}

