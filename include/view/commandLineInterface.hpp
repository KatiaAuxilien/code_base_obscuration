/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : commandLineInterface.hpp
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
#ifndef CMD_LINE_INTERFACE
#define CMD_LINE_INTERFACE

#include <stdio.h>
#include <string>
#include "ANSI-color-codes.h"

class commandLineInterface
{
public:
	commandLineInterface();

	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 28/05/2024 15:33:00
	 */
	void error_failure(string msg);

	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 28/05/2024 15:33:00
	 */
	void error_warning(string msg);
private:
	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 15/05/2024
	 */
	void cmd_colorStandard();

	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 15/05/2024
	 */
	void cmd_colorError();

	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 28/05/2024 15:33:00
	 */
	void cmd_colorWarning();
}

#endif // CMD_LINE_INTERFACE