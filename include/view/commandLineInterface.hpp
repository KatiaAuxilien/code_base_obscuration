/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : commandLineInterface.hpp
 *
 * Description :
 *
 *
 * Author : Katia Auxilien
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

using namespace std;

//TODO : Documentation

class commandLineInterface
{
private :
	static commandLineInterface *instancePtr;
	commandLineInterface();

public:
	commandLineInterface(const commandLineInterface &obj) = delete;
	
	static commandLineInterface *getInstance(){
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
	
	~commandLineInterface();

	/**
	 * @brief 
	 * @author Katia Auxilien
	 * @date 07/06/2024 16:47:00
	 */
	void help(string msg) const;

	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 28/05/2024 15:33:00
	 */
	void error_failure(string msg) const;

	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 28/05/2024 15:33:00
	 */
	void error_warning(string msg) const;
private:
	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 15/05/2024
	 */
	void cmd_colorStandard() const;

	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 15/05/2024
	 */
	void cmd_colorError() const;

	/**
	 *  @brief
	 *  @details
	 *  @authors Katia Auxilien
	 *  @date 28/05/2024 15:33:00
	 */
	void cmd_colorWarning() const;

	/**
	 * @brief 
	 * @author Katia Auxilien
	 * @date 07/06/2024 16:47:00
	 */
	void cmd_colorHelping() const;
};

#endif // CMD_LINE_INTERFACE