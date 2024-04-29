/******************************************************************************
* ICAR_Library
*
* Fichier : image.h
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

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef IMAGE
#define IMAGE

#include <cstdlib>
#include <cstdio>
#include <cstring>

#define allocation_tableau(nom, type, nombre) \
if( (nom = (type*) calloc (nombre, sizeof(type) ) ) == NULL ) \
{\
 printf("\n Allocation dynamique impossible pour un pointeur-tableau \n");\
 exit(EXIT_FAILURE);\
}

typedef unsigned char OCTET;

void ignorer_commentaires(FILE * f);

#endif