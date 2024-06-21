/******************************************************************************
 * ICAR_Interns_Library
 *
 * File : PaillierControllerStatR.hpp
 *
 * Description : This file contains the declaration of the PaillierControllerStatR
 * class, which is derived from the PaillierController class. This class is used
 * to perform statistical calculations on r in the Paillier cryptosystem.
 *
 *
 * Author : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 30 mai 2024, 15:50:00
 *
 *******************************************************************************/

#ifndef PAILLIERCONTROLLER_Stat_R
#define PAILLIERCONTROLLER_Stat_R

#include <stdio.h>
#include "../../include/controller/PaillierController.hpp"

/**
 * \class PaillierControllerStatR
 * \brief This class is used to perform statistical calculations on r in the Paillier cryptosystem.
 * \details This class is derived from the PaillierController class.
 * \author Katia Auxilien
 * \date 30 mai 2024, 15:50:00
 */
class PaillierControllerStatR : public PaillierController
{
public:
    /**
     * \brief Constructor of the PaillierControllerStatR class.
     * \details This constructor initializes the PaillierControllerStatR object.
     * \author Katia Auxilien
     * \date 30 mai 2024, 15:50:00
     */
    PaillierControllerStatR();

    /**
     * \brief Destructor of the PaillierControllerStatR class.
     * \details This destructor frees the memory allocated by the PaillierControllerStatR object.
     * \author Katia Auxilien
     * \date 30 mai 2024, 15:50:00
     */
    ~PaillierControllerStatR();

    /**
     * \brief Initialize the PaillierControllerStatR object.
     * \details This function initializes the PaillierControllerStatR object.
     * \author Katia Auxilien
     * \date 30 May 2024, 15:50:00
     *
     */
    void init();

    /**
     * \brief Check parameters for the program performing statistical calculations on r.
     * \param char* arg_in[] - The array of input arguments.
     * \param int size_arg - The size of the input arguments array.
     * \param bool param[]
     *				0	bool useKeys = false;
     *				1	bool distributeOnTwo = false;
     *				2	bool optimisationLSB = false;
     * \details This function checks the parameters for the program performing statistical calculations on r.
     * \author Katia Auxilien
     * \date 27/05/2024 11:52:00
     */
    void checkParameters(char *arg_in[], int size_arg, bool param[]);

    /**
     * \brief Afficher le manuel du programme.
     * \author Katia Auxilien
     * \date 07/06/2024 16:41:00
     */
    void printHelp();

    /************** 8bits **************/
    /**
     * \brief Perform encryption calculations.
     * \details This function performs encryption calculations.
     * \author Katia Auxilien
     * \date 30/05/2024
     */
    void calc_encrypt();
};
#endif // PAILLIERCONTROLLER_Stat_R
