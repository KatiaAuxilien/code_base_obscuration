/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : image.cpp
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
#include "../../include/image/image_portable.hpp"

void image_portable::ignorer_commentaires(FILE *f)
{
	unsigned char c;
	while ((c = fgetc(f)) == '#')
		while ((c = fgetc(f)) != '\n')
			;
	fseek(f, -sizeof(unsigned char), SEEK_CUR);
}