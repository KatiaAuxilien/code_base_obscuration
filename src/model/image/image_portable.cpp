/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : image_portable.cpp
 *
 * Description :
 *   This file contains the implementation of the image_portable class, which
 * provides an interface for reading and writing portable image formats, such
 * as PGM and PPM. The class defines pure virtual methods for reading the
 * number of lines and columns of an image, reading an image into a buffer,
 * and writing an image from a buffer. Derived classes must implement these
 * methods to provide support for a specific image format.
 *
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : April 2024 - May 2024
 *
 *******************************************************************************/
#include "../../../include/model/image/image_portable.hpp"

void image_portable::ignorer_commentaires(FILE *f)
{
	unsigned char c;
	while ((c = fgetc(f)) == '#')
		while ((c = fgetc(f)) != '\n')
			;
	fseek(f, -sizeof(unsigned char), SEEK_CUR);
}