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
* Date : 
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

#ifndef IMAGE_PGM
#define IMAGE_PGM

typedef unsigned char OCTET;

void lire_nb_lignes_colonnes_image_pgm(char nom_image[], int* nb_lignes, int* nb_colonnes);

void lire_image_pgm(char  nom_image[], OCTET* pt_image, int taille_image);

void ecrire_image_pgm(char  nom_image[], OCTET* pt_image, int nb_lignes, int nb_colonnes);

void ecrire_image_pgm_variable_size(char  nom_image[], uint64_t * pt_image, int nb_lignes, int nb_colonnes, uint64_t max_value);

void lire_image_pgm_variable_size(char  nom_image[], uint64_t * pt_image, int taille_image);

#endif