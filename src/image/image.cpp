#include "../../include/image/image_portable.hpp"

void image_portable::ignorer_commentaires(FILE *f)
{
	unsigned char c;
	while ((c = fgetc(f)) == '#')
		while ((c = fgetc(f)) != '\n')
			;
	fseek(f, -sizeof(unsigned char), SEEK_CUR);
}