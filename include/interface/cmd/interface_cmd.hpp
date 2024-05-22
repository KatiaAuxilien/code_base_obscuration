/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : interface_cmd.hpp
 *
 * Description :
 * 
 * 
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 21 mai 2024, 16:37:00
 *
 *******************************************************************************/
#ifndef INTERFACE_CMD
#define INTERFACE_CMD

#include <stdio.h>
/**
 *  @brief
 *  @details
 *  @authors Katia Auxilien
 *  @date 15/05/2024
 */
void cmd_colorStandard()
{
	printf("\e[0;36m");
}

/**
 *  @brief
 *  @details
 *  @authors Katia Auxilien
 *  @date 15/05/2024
 */
void cmd_colorError()
{
	printf("\e[1;31m");
	fprintf(stderr, "\e[1;31m");
}


#endif // INTERFACE_CMD