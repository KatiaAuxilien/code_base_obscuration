/**
 * @file PaillierController.hpp
 * @brief Superclass, of Paillier main, that contain common methods between subclasses.
 * @author Katia Auxilien
 * @date 28 May 2024, 13:48:00
 * @details 
 */

#ifndef PAILLIERCONTROLLER
#define PAILLIERCONTROLLER

#include <stdio.h>
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <ctype.h>
#include <cinttypes>
#include <cstring>

#include "../../include/model/Paillier_model.hpp"
#include "../../include/view/commandLineInterface.hpp"

/**
 * \class PaillierController
 * \brief Superclass of Paillier main that contains common methods between subclasses.
 * \author Katia Auxilien
 * \date 28 May 2024, 13:48:00
 */
class PaillierController
{
protected:
    char *c_key_file; //!< Pointer to the key file.

    PaillierModel *model = PaillierModel::getInstance();              //!< Instance of PaillierModel.
    commandLineInterface *view = commandLineInterface::getInstance(); //!< Instance of commandLineInterface.

    /**
     * \brief Checks if the given string ends with the specified suffix.
     * \details Verification of the argument in parameter, to see if it is indeed a file name ending with .?.
     * \param const std::string &str The string to check.
     * \param const std::string &suffix The suffix to check for.
     * \author Katia Auxilien
     * \date 30 April 2024
     * \return bool True if the string ends with the suffix, false otherwise.
     */
    bool endsWith(const std::string &str, const std::string &suffix);

    /**
     * \brief Converts the given arguments to lower case.
     * \details
     * \param char *arg_in[] The arguments to convert.
     * \param int size_arg_in The size of the arguments array.
     * \author Katia Auxilien
     * \date 15 May 2024
     */
    void convertToLower(char *arg_in[], int size_arg_in);
    /**
     * \brief Checks if the given number is prime.
     * \details
     * \param uint64_t n The number to check.
     * \param uint64_t i The starting index for the check.
     * \author Katia Auxilien
     * \date 30 April 2024
     * \return bool True if the number is prime, false otherwise.
     */
    bool isPrime(uint64_t n, uint64_t i = 2);

    /**
     * \brief Checks if the given argument is a prime number.
     * \details Verification of the argument in parameter, to see if it is indeed a number and if it is prime.
     * \param char *arg The argument to check.
     * \author Katia Auxilien
     * \date 30 April 2024
     * \return uint64_t The prime number if the argument is a prime number, 0 otherwise.
     */
    uint64_t check_p_q_arg(char *arg);

    /**
     * \brief Initializes the controller.
     * \details This is a virtual function that can be overridden in derived classes to perform specific initialization tasks.
     * \author Katia Auxilien
     * \date 30 April 2024
     */
    virtual void init() {}

    /**
     * \brief Constructor for PaillierController.
     * \details This is the default constructor for PaillierController. It initializes the controller and its associated model and view.
     * \author Katia Auxilien
     * \date 30 April 2024
     */
    PaillierController();

    /**
     * \brief Destructor for PaillierController.
     * \details This is the destructor for PaillierController. It cleans up any resources allocated by the controller and its associated model and view.
     * \author Katia Auxilien
     * \date 30 April 2024
     */
    ~PaillierController();

public:
    /**
     * \brief Gets the model.
     * \details This function returns a pointer to the PaillierModel associated with this controller.
     * \author Katia Auxilien
     * \date 30 April 2024
     * \return PaillierModel* The model.
     */
    PaillierModel *getModel()
    {
        // model = PaillierModel::getInstance();
        return model;
    }

    /**
     * \brief Gets the view.
     * \details This function returns a pointer to the commandLineInterface associated with this controller.
     * \author Katia Auxilien
     * \date 30 April 2024
     * \return commandLineInterface* The view.
     */
    commandLineInterface *getView()
    {
        // view = commandLineInterface::getInstance();
        return view;
    }

    /**
     * \brief Gets the key file.
     * \details This function returns the key file associated with this controller.
     * \author Katia Auxilien
     * \date 30 April 2024
     * \return const char* The key file.
     */
    const char *getCKeyFile() const;

    /**
     * \brief Sets the key file.
     * \details This function sets the key file associated with this controller.
     * \author Katia Auxilien
     * \date 30 April 2024
     * \param char* newCKeyFile The new key file.
     */
    void setCKeyFile(char *newCKeyFile);

    /**
     * \brief Generates and saves the key pair.
     * \details This function generates a new key pair and saves it to the key file associated with this controller.
     * \author Katia Auxilien
     * \date 30 April 2024
     */
    void generateAndSaveKeyPair();

    /**
     * \brief Reads the key file.
     * \details This function reads the key file associated with this controller and sets the model's public and private keys accordingly.
     * \author Katia Auxilien
     * \date 30 April 2024
     * \param bool isEncryption True if the key is for encryption, false otherwise.
     */
    void readKeyFile(bool isEncryption);
};

#endif // PAILLIERCONTROLLER