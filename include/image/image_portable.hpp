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
        void ignorer_commentaires(FILE *f);
    public:
        virtual void lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes) = 0;
        virtual void lire_image_p(char nom_image[], OCTET *pt_image, int taille_image) = 0;
        virtual void ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes) = 0;
};

#endif // IMAGE