/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : image_ppm.cpp
 *
 * Description :
 * 	 This file implements the image_ppm class, which is derived from image_portable.
 *   It provides methods to read and write PPM images, and to extract their R, G, and B planes.
 *   Source file image.cpp by Bianca Jansen Van Rensburg and William Puech
 *
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024 - Mai 2024
 *
 *******************************************************************************/
#include "../../../include/model/image/image_ppm.hpp"

void image_ppm::planR(OCTET *pt_image, OCTET *src, int taille_image)
{
	int i;
	for (i = 0; i < taille_image; i++)
	{
		pt_image[i] = src[3 * i];
	}
}

void image_ppm::planV(OCTET *pt_image, OCTET *src, int taille_image)
{
	int i;
	for (i = 0; i < taille_image; i++)
	{
		pt_image[i] = src[3 * i + 1];
	}
}

void image_ppm::planB(OCTET *pt_image, OCTET *src, int taille_image)
{
	int i;
	for (i = 0; i < taille_image; i++)
	{
		pt_image[i] = src[3 * i + 2];
	}
}

void image_ppm::lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes)
{
	FILE *f_image;
	int max_grey_val;

	/* cf : l'entete d'une image .ppm : P6                   */
	/*				       nb_colonnes nb_lignes */
	/*    			       max_grey_val          */

	if ((f_image = fopen(nom_image, "rb")) == NULL)
	{
		printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else
	{
		fscanf(f_image, "P6 ");
		ignorer_commentaires(f_image);
		fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
		fclose(f_image);
	}
}

void image_ppm::lire_image_p(char nom_image[], OCTET *pt_image, int taille_image)
{
	FILE *f_image;
	int nb_colonnes, nb_lignes, max_grey_val;
	taille_image = 3 * taille_image;

	if ((f_image = fopen(nom_image, "rb")) == NULL)
	{
		printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else
	{
		fscanf(f_image, "P6 ");
		ignorer_commentaires(f_image);
		fscanf(f_image, "%d %d %d%*c",
			   &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

		if ((fread((OCTET *)pt_image, sizeof(OCTET), taille_image, f_image)) != (size_t)(taille_image))
		{
			printf("\nErreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}

void image_ppm::ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
{
	FILE *f_image;
	int taille_image = 3 * nb_colonnes * nb_lignes;

	if ((f_image = fopen(nom_image, "wb")) == NULL)
	{
		printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(f_image, "P6\r"); /*ecriture entete*/
		fprintf(f_image, "%d %d\r255\r", nb_colonnes, nb_lignes);

		if ((fwrite((OCTET *)pt_image, sizeof(OCTET), taille_image, f_image)) != (size_t)(taille_image))
		{
			printf("\nErreur d'ecriture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}