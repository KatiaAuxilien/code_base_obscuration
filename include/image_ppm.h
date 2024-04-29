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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#ifndef IMAGE_PPM
#define IMAGE_PPM

typedef unsigned char OCTET;

void planR(OCTET *pt_image, OCTET *src, int taille_image);

void planV(OCTET *pt_image, OCTET *src, int taille_image);

void planB(OCTET *pt_image, OCTET *src, int taille_image);

void lire_nb_lignes_colonnes_image_ppm(char nom_image[], int* nb_lignes, int* nb_colonnes);

void lire_image_ppm(char  nom_image[], OCTET* pt_image, int taille_image);

void ecrire_image_ppm(char  nom_image[], OCTET* pt_image, int nb_lignes, int nb_colonnes);

#endif