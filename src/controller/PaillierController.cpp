/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierController.cpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 28 Mai 2024, 15:10:00
 *
 *******************************************************************************/
#include "../../include/controller/PaillierController.hpp"

PaillierController::PaillierController(){};
PaillierController::~PaillierController(){};

const char *PaillierController::getCKeyFile() const
{
    return c_key_file;
}

void PaillierController::setCKeyFile(char *newCKeyFile)
{
    delete[] c_key_file;
    c_key_file = new char[strlen(newCKeyFile) + 1];
    strcpy(c_key_file, newCKeyFile);
}

bool PaillierController::endsWith(const std::string &str, const std::string &suffix)
{
    if (str.empty() || suffix.empty()) // Sécurité pointeurs.
    {

        this->view->getInstance()->error_failure("endsWith : arguments null or empty.");
        return false;
    }
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

void PaillierController::convertToLower(char *arg_in[], int size_arg_in)
{
    for (int j = 1; j < size_arg_in; j++)
    {
        if (!endsWith(arg_in[j], ".pgm") && !endsWith(arg_in[j], ".bin"))
        {
            for (int i = 0; arg_in[j][i] != '\0'; i++)
            {
                arg_in[j][i] = tolower(arg_in[j][i]);
            }
        }
    }
}

bool PaillierController::isPrime(uint64_t n, uint64_t i)
{
    if (n <= 2)
        return (n == 2) ? true : false;
    if (n % i == 0)
        return false;
    if (i * i > n)
        return true;

    return isPrime(n, i + 1);
}

uint64_t PaillierController::check_p_q_arg(char *arg)
{
    if (arg == NULL) // Sécurité pointeurs.
    {
        this->view->getInstance()->error_failure("check_p_q_arg : arguments null or empty.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < strlen(arg); i++)
    {
        if (!isdigit(arg[i]))
        {
            this->view->getInstance()->error_failure("The argument after the first argument must be an int.\n");
            exit(EXIT_FAILURE);
        }
    }
    uint64_t p = atoi(arg);
    if (!isPrime(p, 2))
    {
        this->view->getInstance()->error_failure("The argument after the first argument must be a prime number.\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

void PaillierController::generateAndSaveKeyPair()
{
    uint64_t mu = 0;
    uint64_t g = this->model->getInstance()->getPaillierGenerationKey().generate_g_64t(this->model->getInstance()->getN(), this->model->getInstance()->getLambda());


    uint64_t lambda = this->model->getInstance()->getLambda();
    this->model->getInstance()->getPaillierGenerationKey().generatePrivateKey_64t(lambda,
                                                     mu,
                                                      this->model->getInstance()->getP(),
                                                      this->model->getInstance()->getQ(),
                                                     this->model->getInstance()->getN(),
                                                     g);

    this->model->getInstance()->setLambda(lambda);

    if (mu == 0)
    {
        this->view->getInstance()->error_failure("ERROR with g, no value found for g where mu exist.\n");
        exit(EXIT_FAILURE);
    }
    this->model->getInstance()->setMu(mu);
    this->model->getInstance()->setG(g);

    PaillierPrivateKey tempPK = PaillierPrivateKey(this->model->getInstance()->getLambda(), 
                                                this->model->getInstance()->getMu());
    PaillierPublicKey tempPubK = PaillierPublicKey(this->model->getInstance()->getN(),
                                                                this->model->getInstance()->getG());

    this->model->getInstance()->setPrivateKey(tempPK);
    this->model->getInstance()->setPublicKey(tempPubK);

    if (this->model->getInstance()->getLambda() == 0 ||
        this->model->getInstance()->getMu() == 0 ||
        this->model->getInstance()->getP() == 0 ||
        this->model->getInstance()->getQ() == 0 ||
        this->model->getInstance()->getN() == 0 ||
        this->model->getInstance()->getG() == 0)
    {
        this->view->getInstance()->error_failure("Error in generation of private key.\n");
        printf("p = %" PRIu64 "\n", this->model->getInstance()->getP());
        printf("q = %" PRIu64 "\n", this->model->getInstance()->getQ());
        printf("Pub Key G = %" PRIu64 "\n", this->model->getInstance()->getPublicKey().getG());
        printf("Pub Key N = %" PRIu64 "\n", this->model->getInstance()->getPublicKey().getN());
        printf("Priv Key lambda = %" PRIu64 "\n", this->model->getInstance()->getPrivateKey().getLambda());
        printf("Priv Key mu = %" PRIu64 "\n", this->model->getInstance()->getPrivateKey().getMu());
        exit(EXIT_FAILURE);
    }

    FILE *f_private_key = NULL;

    f_private_key = fopen("Paillier_private_key.bin", "w+b");

    if (f_private_key == NULL)
    {
        this->view->getInstance()->error_failure( "Error ! Opening Paillier_private_key.bin\n");
        exit(EXIT_FAILURE);
    }
    PaillierPublicKey pk = this->model->getInstance()->getPublicKey();
    fwrite(&pk, sizeof(PaillierPrivateKey), 1, f_private_key);

    fclose(f_private_key);

    FILE *f_public_key = NULL;
    f_public_key = fopen("Paillier_public_key.bin", "w+b");

    if (f_public_key == NULL)
    {
        this->view->getInstance()->error_failure("Error ! Opening Paillier_public_key.bin\n");
        exit(EXIT_FAILURE);
    }

    PaillierPrivateKey pubk = this->model->getInstance()->getPrivateKey();
    fwrite(&pubk, sizeof(PaillierPublicKey), 1, f_public_key);

    fclose(f_public_key);
}

void PaillierController::readKeyFile(bool isEncryption)
{

    if (this->getCKeyFile() == NULL)
    {
        this->view->getInstance()->error_failure("readKeyFile : error failure, c_key_file is not declared.");
        exit(EXIT_FAILURE);
    }

    if (!isEncryption)
    {
        PaillierPrivateKey privKey;
        size_t size;
        FILE *f_private_key = NULL;

        f_private_key = fopen(this->getCKeyFile(), "rb");

        if (f_private_key == NULL)
        {
            string msg = "Error ! Opening "+std::string (this->getCKeyFile())+" \n";
            this->view->getInstance()->error_failure(msg);
            exit(EXIT_FAILURE);
        }

        size = sizeof(PaillierPrivateKey);
        fread(&privKey, size, 1, f_private_key);
        // if (result != size) {fputs ("Reading error",stderr); return 1;}

        fclose(f_private_key);

        this->model->getInstance()->setPrivateKey(privKey);
    }
    if (isEncryption)
    {
        PaillierPublicKey pubkey;
        size_t size;
        FILE *f_public_key = NULL;
        f_public_key = fopen(this->getCKeyFile(), "rb");

        if (f_public_key == NULL)
        {
            string msg = "Error ! Opening "+std::string (this->getCKeyFile())+" \n";
            this->view->getInstance()->error_failure(msg);
            exit(EXIT_FAILURE);
        }
        size = sizeof(PaillierPublicKey);
        fread(&pubkey, size, 1, f_public_key);
        // if (result != size) {fputs ("Reading error",stderr); return 1;}

        fclose(f_public_key);

        this->model->getInstance()->setPublicKey(pubkey);
    }
}