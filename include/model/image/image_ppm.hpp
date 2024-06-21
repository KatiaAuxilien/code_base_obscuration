/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : image_ppm.h
 *
 * Description :
 *   Source file is image.h, ICAR_Library, by William Puech, Tue Mar 31 13:26:36 2005
 *   This header file defines the image_ppm class, which is derived from image_portable.
 *   It provides methods to read and write PPM images, and to extract their R, G, and B planes.
 *
 * Author : Katia Auxilien, William Puech
 *
 * Mail : katia.auxilien@mail.fr, ?
 *
 * Date : May 2024 - Tue Mar 31 13:26:36 2005
 *
 *******************************************************************************/
#include "image_portable.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#define __STDC_FORMAT_MACROS

#ifndef IMAGE_PPM
#define IMAGE_PPM

typedef unsigned char OCTET;

/**
 * \class image_ppm
 * \brief This class represents a PPM image and provides methods to read and write PPM images,
 *        and to extract their R, G, and B planes.
 * \authors Katia Auxilien, William Puech
 * \date May 2024, Tue Mar 31 13:26:36 2005
 */
class image_ppm : public image_portable
{

public:
    /**
     * \brief This method extracts the red plane of the image.
     *
     * \param pt_image Pointer to the image data.
     * \param src Pointer to the source data.
     * \param taille_image Size of the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    void planR(OCTET *pt_image, OCTET *src, int taille_image);
    /**
     * \brief This method extracts the green plane of the image.
     *
     * \param pt_image Pointer to the image data.
     * \param src Pointer to the source data.
     * \param taille_image Size of the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    void planV(OCTET *pt_image, OCTET *src, int taille_image);
    /**
     * \brief This method extracts the blue plane of the image.
     *
     * \param pt_image Pointer to the image data.
     * \param src Pointer to the source data.
     * \param taille_image Size of the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    void planB(OCTET *pt_image, OCTET *src, int taille_image);
    // inherit
public:
    /**
     * \brief This method reads the number of lines and columns of the image from a file.
     *
     * \param nom_image Name of the image file.
     * \param nb_lignes Pointer to store the number of lines.
     * \param nb_colonnes Pointer to store the number of columns.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    void lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes);
    /**
     * \brief This method reads the image data from a file.
     *
     * \param nom_image Name of the image file.
     * \param pt_image Pointer to store the image data.
     * \param taille_image Size of the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    void lire_image_p(char nom_image[], OCTET *pt_image, int taille_image);
    /**
     * \brief This method writes the image data to a file.
     *
     * \param nom_image Name of the image file.
     * \param pt_image Pointer to the image data.
     * \param nb_lignes Number of lines in the image.
     * \param nb_colonnes Number of columns in the image.
     * \authors Katia Auxilien, William Puech
     * \date May 2024, Tue Mar 31 13:26:36 2005
     */
    void ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes);
};

#endif