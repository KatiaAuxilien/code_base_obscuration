/**
 * \file commandLineInterface.hpp
 * \brief This file contains the command line interface for the Paillier cryptosystem.
 * \author Katia Auxilien
 * \date  21 mai 2024, 16:37:00
 * \details 
 */

#ifndef CMD_LINE_INTERFACE
#define CMD_LINE_INTERFACE

#include <stdio.h>
#include <string>
#include "ANSI-color-codes.h"

using namespace std;

/**
 * \class commandLineInterface
 * \brief This class provides a command line interface for the Paillier cryptosystem.
 * It is a singleton class, meaning that only one instance of it can exist at a time.
 * \author Katia Auxilien
 * \date 21 mai 2024, 16:37:00
 */
class commandLineInterface
{
private:
	static commandLineInterface *instancePtr; //<! Pointer to the singleton instance of the class
	/**
	 * \brief Private constructor to ensure singleton behavior
	 * \author Katia Auxilien
	 * \date 21 mai 2024, 16:37:00
	 */
	commandLineInterface();

public:
	/**
	 * \brief Delete copy constructor to ensure singleton behavior
	 * \param obj Obj to construct.
	 * \author Katia Auxilien
	 * \date 21 mai 2024, 16:37:00
	 */
	commandLineInterface(const commandLineInterface &obj) = delete;

	/**
	 * \brief This function returns the singleton instance of the class.
	 * \return commandLineInterface* Pointer to the singleton instance of the class.
	 * \author Katia Auxilien
	 * \date 21 mai 2024, 16:37:00
	 */
	static commandLineInterface *getInstance()
	{
		if (instancePtr == NULL)
		{
			instancePtr = new commandLineInterface();
			return instancePtr;
		}
		else
		{
			return instancePtr;
		}
	};

	/**
	 * \brief Destroy the command Line Interface object
	 * \author Katia Auxilien
	 * \date 07 June 2024 16:47:00
	 */
	~commandLineInterface();

	/**
	 * \brief This function displays a help message to the user.
	 * \param msg The message to be displayed.
	 * \author Katia Auxilien
	 * \date 07 June 2024 16:47:00
	 */
	void help(string msg) const;

	/**
	 *  \brief This function displays an error message indicating a failure.
	 * 	\param msg The error message to be displayed.
	 *  \authors Katia Auxilien
	 *  \date 28 May 2024 15:33:00
	 */
	void error_failure(string msg) const;

	/**
	 *  \brief This function displays an error message indicating a warning.
	 * 	\param msg The error message to be displayed.
	 *  \authors Katia Auxilien
	 *  \date 28 May 2024 15:33:00
	 */
	void error_warning(string msg) const;

private:
	/**
	 *  \brief This function resets the color of the command line interface to the standard color.
	 *  \authors Katia Auxilien
	 *  \date 15 May 2024
	 */
	void cmd_colorStandard() const;

	/**
	 *  \brief This function sets the color of the command line interface to the error color.
	 *  \authors Katia Auxilien
	 *  \date 15 May 2024
	 */
	void cmd_colorError() const;

	/**
	 *  \brief This function sets the color of the command line interface to the warning color.
	 *  \authors Katia Auxilien
	 *  \date 28 May 2024 15:33:00
	 */
	void cmd_colorWarning() const;

	/**
	 * \brief This function sets the color of the command line interface to the helping color.
	 * \author Katia Auxilien
	 * \date 07 June 2024 16:47:00
	 */
	void cmd_colorHelping() const;
};

#endif // CMD_LINE_INTERFACE