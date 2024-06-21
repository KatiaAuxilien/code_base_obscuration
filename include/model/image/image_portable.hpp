/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : image_portable.hpp
 *
 * Description : This file defines the image_portable class, which is a base class for
 * different image formats. It provides a protected method for ignoring
 * comments in a file.
 * Source file is image.h, ICAR_Library, by William Puech, Tue Mar 31 13:26:36 2005
 *
 * Authors : Katia Auxilien, William Puech
 *
 * Mail : katia.auxilien@mail.fr ,
 *
 * Date : Mai 2024 - Tue Mar 31 13:26:36 2005
 *
 *******************************************************************************/
#ifndef IMAGE_PORTABLE
#define IMAGE_PORTABLE

#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>

/**
 * \brief Allocate a dynamic array of a given type and size.
 * \param nom The name of the pointer to the array.
 * \param type The type of the elements in the array.
 * \param nombre The number of elements in the array.
 * \author William Puech
 * \date Tue Mar 31 13:26:36 2005
 */
#define allocation_tableau(nom, type, nombre)                                     \
    if ((nom = (type *)calloc(nombre, sizeof(type))) == NULL)                     \
    {                                                                             \
        printf("\n Allocation dynamique impossible pour un pointeur-tableau \n"); \
        exit(EXIT_FAILURE);                                                       \
    }

typedef unsigned char OCTET;

/**
 * \class image_portable
 * \brief Base class for portable image formats.
 * This class provides an interface for reading and writing portable image
 * formats, such as PGM and PPM. It defines pure virtual methods for reading
 * the number of lines and columns of an image, reading an image into a buffer,
 * and writing an image from a buffer. Derived classes must implement these
 * methods to provide support for a specific image format.
 * \author William Puech
 * \date Tue Mar 31 13:26:36 2005
 */
class image_portable
{
protected:
    /**
     * \brief A base class for different image formats. / class image_portable{ protected: /*
     * \brief Ignore comments in a file.
     * \param f The file pointer.
     * \author William Puech
     * \date Tue Mar 31 13:26:36 2005
     */
    static void ignorer_commentaires(FILE *f);
    // public:

    /**
     * \brief Read the number of lines and columns of an image.
     * \param nom_image The name of the image file.
     * \param nb_lignes The pointer to store the number of lines.
     * \param nb_colonnes The pointer to store the number of columns
     * \author William Puech
     * \date Tue Mar 31 13:26:36 2005
     */
    //     virtual void lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes) = 0;

    /**
     * \brief Read an image into a buffer.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the buffer where the image data will be stored.
     * \param taille_image The size of the buffer.
     * \author William Puech
     * \date Tue Mar 31 13:26:36 2005
     */
    //     virtual void lire_image_p(char nom_image[], OCTET *pt_image, int taille_image) = 0;

    /**
     * \brief Write an image from a buffer.
     * \param nom_image The name of the image file.
     * \param pt_image The pointer to the buffer containing the image data.
     * \param nb_lignes The number of lines in the image.
     * \param nb_colonnes The number of columns in the image.
     * \author William Puech
     * \date Tue Mar 31 13:26:36 2005
     */
    //     virtual void ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes) = 0;
};

#endif // IMAGE