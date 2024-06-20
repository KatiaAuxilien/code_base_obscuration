/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : image_pgm.h
 *
 * Description :
 *   Fichier source de départ image.h, ICAR_Library, de William Puech, en Tue Mar 31 13:26:36 2005
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Mai 2024
 *
 *******************************************************************************/
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

class image_pgm : public image_portable {
    public:
        //uint8_t
        static uint8_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint8_t *pt_image, int taille_image);
        static void ecrire_image_pgm_variable_size(char nom_image[], uint8_t *pt_image, int nb_lignes, int nb_colonnes, uint8_t max_value);
        //uint16_t
        static uint16_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint16_t *pt_image, int taille_image);
        static void ecrire_image_pgm_variable_size(char nom_image[], uint16_t *pt_image, int nb_lignes, int nb_colonnes, uint16_t max_value);
        //Compress
        static void write_image_pgm_compressed_variable_size(char nom_image[], uint16_t *pt_image, int nb_lignes, int nb_colonnes, uint16_t max_value, int imgSize, int nHOriginal, int nWOriginal);
        static pair<int, int> read_image_pgm_compressed_and_get_originalDimension(char nom_image[], uint16_t *pt_image);

        //uint32_t
        static uint32_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint32_t *pt_image, int taille_image);
        static void ecrire_image_pgm_variable_size(char nom_image[], uint32_t *pt_image, int nb_lignes, int nb_colonnes, uint32_t max_value);
        //uint64_t
        static uint64_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint64_t *pt_image, int taille_image);
        static void ecrire_image_pgm_variable_size(char nom_image[], uint64_t *pt_image, int nb_lignes, int nb_colonnes, uint64_t max_value);
        static void lire_image_pgm_variable_size(char nom_image[], uint64_t *pt_image, int taille_image);

        static void lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes);
        static void lire_image_p(char nom_image[], OCTET *pt_image, int taille_image);
        static void ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes);
    
};

#endif