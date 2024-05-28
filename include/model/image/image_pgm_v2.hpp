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
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

#define allocation_tableau(nom, type, nombre)                                     \
    if ((nom = (type *)calloc(nombre, sizeof(type))) == NULL)                     \
    {                                                                             \
        printf("\n Allocation dynamique impossible pour un pointeur-tableau \n"); \
        exit(EXIT_FAILURE);                                                       \
    }

typedef unsigned char OCTET;

template <typename T>
class image_pgm
{
public:
    void ignorer_commentaires(FILE *f)
    {
        unsigned char c;
        while ((c = fgetc(f)) == '#')
            while ((c = fgetc(f)) != '\n')
                ;
        fseek(f, -sizeof(unsigned char), SEEK_CUR);
    };

    void lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes)
    {
        FILE *f_image;
        int max_grey_val;

        /* cf : l'entete d'une image .pgm : P5                    */
        /*				       nb_colonnes nb_lignes */
        /*    			       max_grey_val          */

        if ((f_image = fopen(nom_image, "rb")) == NULL)
        {
            printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        else
        {
            fscanf(f_image, "P5 ");
            ignorer_commentaires(f_image);
            fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
            fclose(f_image);
        }
    }

    void lire_image_p(char nom_image[], T *pt_image, int taille_image)
    {
        FILE *f_image;
        int nb_colonnes, nb_lignes, max_grey_val;

        if ((f_image = fopen(nom_image, "rb")) == NULL)
        {
            printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        else
        {
            fscanf(f_image, "P5 ");
            ignorer_commentaires(f_image);
            fscanf(f_image, "%d %d %d%*c",
                   &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

            if ((fread((OCTET *)pt_image, sizeof(OCTET), taille_image, f_image)) != (size_t)taille_image)
            {
                printf("\nErreur de lecture de l'image %s \n", nom_image);
                exit(EXIT_FAILURE);
            }
            fclose(f_image);
        }
    }

    void ecrire_image_p(char nom_image[], T *pt_image, int nb_lignes, int nb_colonnes)
    {
        FILE *f_image;
        int taille_image = nb_colonnes * nb_lignes;

        if ((f_image = fopen(nom_image, "wb")) == NULL)
        {
            printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        else
        {
            fprintf(f_image, "P5\r"); /*ecriture entete*/
            fprintf(f_image, "%d %d\r255\r", nb_colonnes, nb_lignes);

            if ((fwrite((T *)pt_image, sizeof(T), taille_image, f_image)) != (size_t)taille_image)
            {
                printf("\nErreur d'écriture de l'image %s \n", nom_image);
                exit(EXIT_FAILURE);
            }
            fclose(f_image);
        }
    };

    void ecrire_image_pgm_variable_size(char nom_image[], T *pt_image, int nb_lignes, int nb_colonnes, T max_value)
    {
        FILE *f_image;
        int taille_image = nb_colonnes * nb_lignes;

        if ((f_image = fopen(nom_image, "wb")) == NULL)
        {
            printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        else
        {
            fprintf(f_image, "P5\r"); /*ecriture entete*/
            fprintf(f_image, "%d %d\r%" PRIu8 "\r", nb_colonnes, nb_lignes, max_value);

            if ((fwrite((T *)pt_image, sizeof(T), taille_image, f_image)) != (size_t)taille_image)
            {
                printf("\nErreur d'écriture de l'image %s \n", nom_image);
                exit(EXIT_FAILURE);
            }
            fclose(f_image);
        }
    };

    void lire_image_pgm_variable_size(char nom_image[], T *pt_image, int taille_image)
    {
        FILE *f_image;
        int nb_colonnes, nb_lignes;
        T max_grey_val;

        if ((f_image = fopen(nom_image, "rb")) == NULL)
        {
            printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
            exit(EXIT_FAILURE);
        }
        else
        {
            fscanf(f_image, "P5 ");
            ignorer_commentaires(f_image);
            fscanf(f_image, "%d %d %" SCNd64 "%*c",
                   &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

            if ((fread((T *)pt_image, sizeof(T), taille_image, f_image)) != (size_t)taille_image)
            {
                printf("\nErreur de lecture de l'image %s \n", nom_image);
                exit(EXIT_FAILURE);
            }
            fclose(f_image);
        }
    }
};

#endif