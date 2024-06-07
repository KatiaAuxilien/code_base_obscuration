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

commandLineInterface::~commandLineInterface(){};

commandLineInterface *commandLineInterface ::instancePtr = NULL;

void commandLineInterface::error_failure(string msg) const{
    cmd_colorError();
    fprintf(stderr,"%s",msg.c_str());
    cmd_colorStandard();
}
void commandLineInterface::error_warning(std::string msg) const{
    cmd_colorWarning();
    fprintf(stderr,"%s",msg.c_str());
    cmd_colorStandard();
}

void commandLineInterface::cmd_colorStandard() const
{
    printf(COLOR_RESET);
}

void commandLineInterface::cmd_colorError() const
{
    fprintf(stderr,BRED);
}

void commandLineInterface::cmd_colorWarning() const
{
    fprintf(stderr, BYEL);
}

void commandLineInterface::cmd_colorHelping() const{
    fprintf(stderr, BHCYN);
}


void commandLineInterface::help(string msg) const {
    cmd_colorHelping();
    printf("%s",msg.c_str());
    cmd_colorStandard();
}
