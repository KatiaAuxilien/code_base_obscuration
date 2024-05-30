/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : image_portable.hpp
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
#ifndef IMAGE_PORTABLE
#define IMAGE_PORTABLE

#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define allocation_tableau(nom, type, nombre)                                     \
    if ((nom = (type *)calloc(nombre, sizeof(type))) == NULL)                     \
    {                                                                             \
        printf("\n Allocation dynamique impossible pour un pointeur-tableau \n"); \
        exit(EXIT_FAILURE);                                                       \
    }

typedef unsigned char OCTET;

class image_portable{
    protected:
        static void ignorer_commentaires(FILE *f);
    // public:
    //     virtual void lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes) = 0;
    //     virtual void lire_image_p(char nom_image[], OCTET *pt_image, int taille_image) = 0;
    //     virtual void ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes) = 0;
};

#endif // IMAGE