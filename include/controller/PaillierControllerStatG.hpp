/**
 * \file PaillierControllerStatG.hpp
 * \brief This file contains the declaration of the PaillierControllerStatG class,
 * which is a derivative of the PaillierController class. This class is used
 * to perform statistical calculations on g in a Paillier cryptosystem.
 * \author Katia Auxilien
 * \date 30 May 2024, 15:50:00
 * \details 
 */

#ifndef PAILLIERCONTROLLER_Stat_G
#define PAILLIERCONTROLLER_Stat_G

#include <stdio.h>
#include "../../include/controller/PaillierController.hpp"

/**
 * \class PaillierControllerStatG
 * \brief This class is used to perform statistical calculations on g in a Paillier cryptosystem.
 * \details This class is a derivative of the PaillierController class.
 * \author Katia Auxilien
 * \date 30 May 2024, 15:50:00
 */
class PaillierControllerStatG : public PaillierController
{
public:
	/**
	 * \brief Construct a new Paillier Controller Stat G object
	 */
	PaillierControllerStatG();

	/**
	 * \brief Destroy the Paillier Controller Stat G object
	 */
	~PaillierControllerStatG();

	/**
	 * \brief Initialize the PaillierControllerStatG object
	 */
	void init();

	/**
	 * \brief Check the parameters for the program performing statistical calculations on g.
	 * \param char* arg_in[] - The array of input arguments.
	 * \param int size_arg - The size of the input arguments array.
	 * \param bool param[] - The array of parameters to be checked.
	 *				0	bool distributeOnTwo = false;
	 *				1	bool optimisationLSB = false;
	 * \authors Katia Auxilien
	 * \date 27 May 2024 11:52:00
	 * \details The function checks the input arguments and sets the parameters accordingly.
	 */
	void checkParameters(char *arg_in[], int size_arg, bool param[]);

	/**
	 * \brief Print the manual of the program.
	 * \author Katia Auxilien
	 * \date 07 June 2024 16:41:00
	 */
	void printHelp();

	/*********************** Chiffrement ***********************/

	/************** 8bits **************/
	/**
	 *  \brief Calculate the encryption of all g.
	 *  \details
	 *  \param
	 *  \authors Katia Auxilien
	 *  \date 30 may 2024
	 */
	void calc_encrypt_all_g();

	/**
	 * \brief Calculate the encryption of 10 g.
	 * \details
	 * \authors Katia Auxilien
	 * \date 30 may 2024
	 */
	void calc_encrypt_10_g();
};
#endif // PAILLIERCONTROLLER_Stat_G