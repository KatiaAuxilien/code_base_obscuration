/**
 * @file image_pgm.hpp
 * @brief This file contains the declaration of the image_pgm class, which is used to
 * read and write PGM images with various bit depths.
 * @authors Katia Auxilien, William Puech
 * @date  May 2024 - Tue Mar 31 13:26:36 2005
 * @details Source file is image.h, ICAR_Library, by William Puech, Tue Mar 31 13:26:36 2005
 */
#ifndef IMAGE_PGM
#define IMAGE_PGM
#include "image_portable.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <string>
using namespace std;

typedef unsigned char OCTET;

/**
 * \class image_pgm
 * \brief The image_pgm class provides methods to read and write PGM images with various bit depths.
 * \author Katia Auxilien
 * \date May 2024
 */
class image_pgm : public image_portable
{
public:
    // uint8_t

    /**
     * \brief Reads a PGM image with 8-bit depth and returns the maximum grey value.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param taille_image The size of the image.
     * \return The maximum grey value in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static uint8_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint8_t *pt_image, int taille_image);

    /**
     * \brief Writes a PGM image with variable size.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param nb_lignes The number of lines in the image.
     * \param nb_colonnes The number of columns in the image.
     * \param max_value The maximum value in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void ecrire_image_pgm_variable_size(char nom_image[], uint8_t *pt_image, int nb_lignes, int nb_colonnes, uint8_t max_value);

    // uint16_t
    /**
     * \brief Reads a PGM image with 16-bit depth and returns the maximum grey value.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param taille_image The size of the image.
     * \return The maximum grey value in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static uint16_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint16_t *pt_image, int taille_image);

    /**
     * \brief Writes a PGM image with variable size and 16-bit depth.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param nb_lignes The number of lines in the image.
     * \param nb_colonnes The number of columns in the image.
     * \param max_value The maximum value in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void ecrire_image_pgm_variable_size(char nom_image[], uint16_t *pt_image, int nb_lignes, int nb_colonnes, uint16_t max_value);

    // Compress
    /**
     * \brief Writes a compressed PGM image with variable size and 16-bit depth.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param nb_lignes The number of lines in the image.
     * \param nb_colonnes The number of columns in the image.
     * \param max_value The maximum value in the image.
     * \param imgSize The size of the image.
     * \param nHOriginal The original number of lines.
     * \param nWOriginal The original number of columns.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void write_image_pgm_compressed_variable_size(char nom_image[], uint16_t *pt_image, int nb_lignes, int nb_colonnes, uint16_t max_value, int imgSize, int nHOriginal, int nWOriginal);

    /**
     * \brief Reads a compressed PGM image with 16-bit depth and returns the original dimensions.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \return A pair containing the original number of lines and columns.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static pair<int, int> read_image_pgm_compressed_and_get_originalDimension(char nom_image[], uint16_t *pt_image);

    // uint32_t

    /**
     * \brief Reads a PGM image with 32-bit depth and returns the maximum grey value.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param taille_image The size of the image.
     * \return The maximum grey value in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static uint32_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint32_t *pt_image, int taille_image);

    /**
     * \brief Writes a PGM image with variable size and 32-bit depth.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param nb_lignes The number of lines in the image.
     * \param nb_colonnes The number of columns in the image.
     * \param max_value The maximum value in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void ecrire_image_pgm_variable_size(char nom_image[], uint32_t *pt_image, int nb_lignes, int nb_colonnes, uint32_t max_value);

    // uint64_t

    /**
     * \brief Reads a PGM image with 64-bit depth and returns the maximum grey value.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param taille_image The size of the image.
     * \return The maximum grey value in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static uint64_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint64_t *pt_image, int taille_image);

    /**
     * \brief Writes a PGM image with variable size and 64-bit depth.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param nb_lignes The number of lines in the image.
     * \param nb_colonnes The number of columns in the image.
     * \param max_value The maximum value in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void ecrire_image_pgm_variable_size(char nom_image[], uint64_t *pt_image, int nb_lignes, int nb_colonnes, uint64_t max_value);

    /**
     * \brief Reads a PGM image with variable size and 64-bit depth.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the image data.
     * \param taille_image The size of the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void lire_image_pgm_variable_size(char nom_image[], uint64_t *pt_image, int taille_image);

    /**
     * \brief Reads the number of lines and columns of a PGM image.
     * \param nom_image The name of the image file.
     * \param nb_lignes The pointer to store the number of lines.
     * \param nb_colonnes The pointer to store the number of columns.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes);

    /**
     * \brief Reads a PGM image with variable size and stores it in an OCTET array.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the OCTET array.
     * \param taille_image The size of the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void lire_image_p(char nom_image[], OCTET *pt_image, int taille_image);

    /**
     * \brief Writes a PGM image from an OCTET array with given dimensions.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the OCTET array.
     * \param nb_lignes The number of lines in the image.
     * \param nb_colonnes The number of columns in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    static void ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes);
};

#endif