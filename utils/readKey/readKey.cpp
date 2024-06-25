/**
 * \file read_key.cpp
 * \brief Read a public or private key from a binary file.
 *
 * This file contains main for reading a public or private key from a binary
 * file.
 *
 * \author Katia Auxilien
 * \date 24 june 2024 14:30:00
 */

#include <fstream>
#include "../../include/model/encryption/Paillier/keys/Paillier_private_key.hpp"
#include "../../include/model/encryption/Paillier/keys/Paillier_public_key.hpp"

#include "../../include/controller/PaillierControllerPGM.hpp"

/**
 * \brief Main function.
 *
 * This function checks that the command line arguments are correct and calls the
 * appropriate function to read the key from the file. It then uses the key to
 * perform encryption or decryption operations.
 *
 * \param argc The number of command line arguments.
 * \param argv The command line arguments.
 * \return int The exit code.
 *
 * \author Katia Auxilien
 * \date 24 june 2024 14:30:00
 */
int main(int argc, char** argv) {
    PaillierControllerPGM *controller = new PaillierControllerPGM();

    if (argc != 3) {
        controller->getView()->error_failure("Usage: "+ std::string(argv[0]) + " {public|private} <keyfile>");
        exit(EXIT_FAILURE);
    }

    std::string keytype(argv[1]);
    std::string filename(argv[2]);

    controller->setCKeyFile(argv[2]);

    if (keytype == "public" || keytype == "pub") {
	    controller->readKeyFile(true);
        printf("Public key :\n");
        printf(" \tN = %"PRIu64"\n",controller->getModel()->getN());
        printf(" \tG = %"PRIu64"\n",controller->getModel()->getG());
    } else if (keytype == "private" || keytype == "priv") {
       	controller->readKeyFile(false);
        printf("Private key :\n");
        printf(" \tMu = %"PRIu64"\n",controller->getModel()->getMu());
        printf(" \tLambda = %"PRIu64"\n",controller->getModel()->getLambda());
    } else {
        controller->getView()->error_failure("Incorrect key type");
        exit(EXIT_FAILURE);
    }

    return 0;
}
