/******************************************************************************
 * ICAR_Library
 *
 * Fichier : image_pgm.cpp
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
#include "../include/image.h"
#include "../include/image_pgm.h"

void ecrire_image_pgm(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
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

		if ((fwrite((OCTET *)pt_image, sizeof(OCTET), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}

void lire_nb_lignes_colonnes_image_pgm(char nom_image[], int *nb_lignes, int *nb_colonnes)
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

void lire_image_pgm(char nom_image[], OCTET *pt_image, int taille_image)
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

uint64_t lire_image_pgm_and_get_maxgrey(char nom_image[], uint64_t *pt_image, int taille_image)
{
	FILE *f_image;
	int nb_colonnes, nb_lignes;
	uint64_t max_grey_val;

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

		if ((fread((uint64_t *)pt_image, sizeof(uint64_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
	return max_grey_val;
}

void lire_image_pgm_variable_size(char nom_image[], uint64_t *pt_image, int taille_image)
{
	FILE *f_image;
	int nb_colonnes, nb_lignes;
	uint64_t max_grey_val;

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

		if ((fread((uint64_t *)pt_image, sizeof(uint64_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}

void ecrire_image_pgm_variable_size(char nom_image[], uint64_t *pt_image, int nb_lignes, int nb_colonnes, uint64_t max_value)
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
		fprintf(f_image, "%d %d\r%" PRIu64 "\r", nb_colonnes, nb_lignes, max_value);

		if ((fwrite((uint64_t *)pt_image, sizeof(uint64_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}