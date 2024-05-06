#include "../include/image.h"

void ignorer_commentaires(FILE *f)
{
	unsigned char c;
	while ((c = fgetc(f)) == '#')
		while ((c = fgetc(f)) != '\n')
			;
	fseek(f, -sizeof(unsigned char), SEEK_CUR);
}