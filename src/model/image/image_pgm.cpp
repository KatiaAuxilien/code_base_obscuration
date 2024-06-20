/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : image_pgm.cpp
 *
 * Description :
 *   Fichier source de départ image.cpp de Bianca Jansen Van Rensburg
 * 
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024 - Mai 2024
 *
 *******************************************************************************/
#include "../../../include/model/image/image_pgm.hpp"

void image_pgm::ecrire_image_p(char nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
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
			printf("\nErreur d'écriture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}

void image_pgm::lire_nb_lignes_colonnes_image_p(char nom_image[], int *nb_lignes, int *nb_colonnes)
{
	FILE *f_image;
	int max_grey_val;

	/* cf : l'entete d'une image .pgm : P5                    */
	/*						#Commentaire					*/
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


void image_pgm::lire_image_p(char nom_image[], OCTET *pt_image, int taille_image)
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

//uint8_t
uint8_t image_pgm::lire_image_pgm_and_get_maxgrey(char nom_image[], uint8_t *pt_image, int taille_image)
{
	FILE *f_image;
	int nb_colonnes, nb_lignes;
	uint8_t max_grey_val;

	if ((f_image = fopen(nom_image, "rb")) == NULL)
	{
		printf("\nlire_image_pgm_and_get_maxgrey_8t : Pas d'acces en lecture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else
	{
		fscanf(f_image, "P5 ");
		ignorer_commentaires(f_image);
		fscanf(f_image, "%d %d %" SCNd8 "%*c",
			   &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

		if ((fread((uint8_t *)pt_image, sizeof(uint8_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nlire_image_pgm_and_get_maxgrey_8t : Erreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
	return max_grey_val;
}

void image_pgm::ecrire_image_pgm_variable_size(char nom_image[], uint8_t *pt_image, int nb_lignes, int nb_colonnes, uint8_t max_value)
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

		if ((fwrite((uint8_t *)pt_image, sizeof(uint8_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur d'écriture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}

//uint16_t
uint16_t image_pgm::lire_image_pgm_and_get_maxgrey(char nom_image[], uint16_t *pt_image, int taille_image)
{
	FILE *f_image;
	int nb_colonnes, nb_lignes;
	uint16_t max_grey_val;

	if ((f_image = fopen(nom_image, "rb")) == NULL)
	{
		printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else
	{
		fscanf(f_image, "P5 ");
		ignorer_commentaires(f_image);
		fscanf(f_image, "%d %d %" SCNd16 "%*c",
			   &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

		if ((fread((uint16_t *)pt_image, sizeof(uint16_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
	return max_grey_val;
}

void image_pgm::ecrire_image_pgm_variable_size(char nom_image[], uint16_t *pt_image, int nb_lignes, int nb_colonnes, uint16_t max_value)
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
		fprintf(f_image, "%d %d\r%" PRIu16 "\r", nb_colonnes, nb_lignes, max_value);

		if ((fwrite((uint16_t *)pt_image, sizeof(uint16_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur d'écriture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}


//Used in compression
void image_pgm::write_image_pgm_compressed_variable_size(char nom_image[], uint16_t *pt_image, int nb_lignes, int nb_colonnes, uint16_t max_value, int imgSize, int nHOriginal, int nWOriginal)
{
	FILE *f_image;
	int taille_image = imgSize;

	if ((f_image = fopen(nom_image, "wb")) == NULL)
	{
		printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(f_image, "P5\r"); /*ecriture entete*/
		fprintf(f_image, "#%d %d\r",nWOriginal, nHOriginal);
		fprintf(f_image, "%d %d\r%" PRIu16 "\r", nb_colonnes, nb_lignes, max_value);

		if ((fwrite((uint16_t *)pt_image, sizeof(uint16_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur d'écriture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);

			printf("Taille : %d\n",taille_image);
			printf("nHO : %d\n", nHOriginal);
			printf("nWO : %d\n",nWOriginal);
			printf("nHC : %d\n", nb_lignes);
			printf("nWC : %d\n",nb_colonnes);

	}
}

pair<int, int> image_pgm::read_image_pgm_compressed_and_get_originalDimension(char nom_image[], uint16_t *pt_image)
{
	FILE *f_image;
	int nb_colonnes, nb_lignes;
	uint16_t max_grey_val;
	int nHOriginal, nWOriginal;
	int taille_image;
	if ((f_image = fopen(nom_image, "rb")) == NULL)
	{
		printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else
	{
		fscanf(f_image, "P5 ");

		fscanf(f_image, "%d %d",&nWOriginal, &nHOriginal);

		ignorer_commentaires(f_image); 

		fscanf(f_image, "%d %d %" SCNd16 "%*c",&nb_colonnes, &nb_lignes, &max_grey_val);
		taille_image = nb_colonnes * nb_lignes;

		if ((fread((uint16_t *)pt_image, sizeof(uint16_t), taille_image, f_image)) != (size_t)taille_image)
		{

			printf("Taille : %d\n",taille_image);
			printf("nHO : %d\n", nHOriginal);
			printf("nWO : %d\n",nWOriginal);
			printf("nHC : %d\n", nb_lignes);
			printf("nWC : %d\n",nb_colonnes);

			printf("\nErreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);

			printf("Taille : %d\n",taille_image);
			printf("nHO : %d\n", nHOriginal);
			printf("nWO : %d\n",nWOriginal);
			printf("nHC : %d\n", nb_lignes);
			printf("nWC : %d\n",nb_colonnes);

	}

	return make_pair(nWOriginal,nHOriginal);
}


//uint32_t
uint32_t image_pgm::lire_image_pgm_and_get_maxgrey(char nom_image[], uint32_t *pt_image, int taille_image)
{
	FILE *f_image;
	int nb_colonnes, nb_lignes;
	uint32_t max_grey_val;

	if ((f_image = fopen(nom_image, "rb")) == NULL)
	{
		printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else
	{
		fscanf(f_image, "P5 ");
		ignorer_commentaires(f_image);
		fscanf(f_image, "%d %d %" SCNd32 "%*c",
			   &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

		if ((fread((uint32_t *)pt_image, sizeof(uint32_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur de lecture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
	return max_grey_val;
}

void image_pgm::ecrire_image_pgm_variable_size(char nom_image[], uint32_t *pt_image, int nb_lignes, int nb_colonnes, uint32_t max_value)
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
		fprintf(f_image, "%d %d\r%" PRIu16 "\r", nb_colonnes, nb_lignes, max_value);

		if ((fwrite((uint32_t *)pt_image, sizeof(uint32_t), taille_image, f_image)) != (size_t)taille_image)
		{
			printf("\nErreur d'écriture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}


//uint64_t
uint64_t image_pgm::lire_image_pgm_and_get_maxgrey(char nom_image[], uint64_t *pt_image, int taille_image)
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

void image_pgm::ecrire_image_pgm_variable_size(char nom_image[], uint64_t *pt_image, int nb_lignes, int nb_colonnes, uint64_t max_value)
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
			printf("\nErreur d'écriture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}

void image_pgm::lire_image_pgm_variable_size(char nom_image[], uint64_t *pt_image, int taille_image)
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

