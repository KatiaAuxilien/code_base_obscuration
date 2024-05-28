/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : commandLineInterface.cpp
 *
 * Description :
 * 
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 28 Mai 2024, 15:15:00
 *
 *******************************************************************************/
#include "../../include/view/commandLineInterface.hpp"

commandLineInterface::commandLineInterface(){};

void commandLineInterface::error_failure(string msg){
    this->cmd_colorError();
    fprintf(stderr,msg);
    this->cmd_colorStandard();
}
void commandLineInterface::error_warning(string msg){
    this->cmd_colorWarning();
    fprintf(stderr,msg);
    this->cmd_colorStandard();
}

void commandLineInterface::cmd_colorStandard()
{
    printf(COLOR_RESET);
}

void commandLineInterface::cmd_colorError()
{
    fprintf(stderr,BRED);
}

void commandLineInterface::cmd_colorWarning()
{
    fprintf(stderr, BYEL);
}