/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : image_ppm.h
 *
 * Description :
 *   Fichier source de départ image.h, ICAR_Library, de William Puech, en Tue Mar 31 13:26:36 2005
 * 
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Mai 2024
 *
 *******************************************************************************/
#include "../../include/model/image/image_portable.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#define __STDC_FORMAT_MACROS

#ifndef IMAGE_PPM
#define IMAGE_PPM

typedef unsigned char OCTET;

//TODO : Documentation

class image_ppm : public image_portable {

    public:
        void planR(OCTET *pt_image, OCTET *src, int taille_image);
        void planV(OCTET *pt_image, OCTET *src, int taille_image);
        void planB(OCTET *pt_image, OCTET *src, int taille_image);
    //inherit
    public:
        void lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes);
        void lire_image_p(char nom_image[], OCTET *pt_image, int taille_image);
        void ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes);

};

#endif