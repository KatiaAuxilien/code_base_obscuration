/******************************************************************************
 * ICAR_Library
 *
 * Fichier : image_ppm.h
 *
 * Description :
 *
 * Auteur :
 *
 * Mail :
 *
 * Date : Tue Mar 31 13:26:36 2005
 *
 *******************************************************************************/
#ifndef IMAGE_PGM
#define IMAGE_PGM
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

typedef unsigned char OCTET;

void lire_nb_lignes_colonnes_image_pgm(char nom_image[], int *nb_lignes, int *nb_colonnes);

void lire_image_pgm(char nom_image[], OCTET *pt_image, int taille_image);

void ecrire_image_pgm(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes);

//uint8_t

uint8_t lire_image_pgm_and_get_maxgrey_8t(char nom_image[], uint8_t *pt_image, int taille_image);

void ecrire_image_pgm_variable_size_8t(char nom_image[], uint8_t *pt_image, int nb_lignes, int nb_colonnes, uint8_t max_value);

//uint16_t
uint16_t lire_image_pgm_and_get_maxgrey_16t(char nom_image[], uint16_t *pt_image, int taille_image);

void ecrire_image_pgm_variable_size_16t(char nom_image[], uint16_t *pt_image, int nb_lignes, int nb_colonnes, uint16_t max_value);

//uint64_t

uint64_t lire_image_pgm_and_get_maxgrey_64t(char nom_image[], uint64_t *pt_image, int taille_image);

void ecrire_image_pgm_variable_size_64t(char nom_image[], uint64_t *pt_image, int nb_lignes, int nb_colonnes, uint64_t max_value);

void lire_image_pgm_variable_size_64t(char nom_image[], uint64_t *pt_image, int taille_image);

#endif