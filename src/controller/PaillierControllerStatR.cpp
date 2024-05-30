/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerStatR.cpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 29 Mai 2024, 13:57:00
 *
 *******************************************************************************/
#include "../../include/controller/PaillierControllerStatR.hpp"

void PaillierControllerStatR::init()
{
    this->model = PaillierModel::getInstance();
    this->view = commandLineInterface::getInstance();
}

PaillierControllerStatR::PaillierControllerStatR()
{
    init();
};

PaillierControllerStatR::~PaillierControllerStatR(){};

void PaillierControllerStatR::checkParameters(char *arg_in[], int size_arg, bool param[])
{
    convertToLower(arg_in, size_arg);
    /********** Initialisation de param[] à false. *************/
    for (int i = 0; i < 3; i++)
    {
        param[i] = false;
    }

    bool isFileBIN = false;

    int i = 0;
    if ((strcmp(arg_in[i], "-k") && strcmp(arg_in[i], "-key")))
    {
        p = check_p_q_arg(arg_in[1]);
        if (p == 1)
        {
            this->view.error_failure("checkParameters : p == 1");
            exit(EXIT_FAILURE);
        }
        q = check_p_q_arg(arg_in[2]);
        if (q == 1)
        {
            this->view.error_failure("checkParameters : q == 1");
            exit(EXIT_FAILURE);
        }

        n = p * q;
        Paillier<uint64_t, uint64_t> paillier;
        uint64_t pgc_pq = paillier.gcd_64t(p * q, (p - 1) * (q - 1));

        if (pgc_pq != 1)
        {
            this->view.error_failure("pgcd(p * q, (p - 1) * (q - 1))= %" PRIu64 "\np & q arguments must have a gcd = 1. Please retry with others p and q.\n", pgc_pq);
            exit(EXIT_FAILURE);
        }
        lambda = paillier.lcm_64t(p - 1, q - 1);

        i = 3;
        isFileBIN = true;
    }

    for (i = i; i < size_arg; i++)
    {
        if ((!isFileBIN && !strcmp(arg_in[i], "-k")) || !strcmp(arg_in[i], "-key") || (endsWith(arg_in[i], ".bin")))
        {
            if (!strcmp(arg_in[i], "-k") || !strcmp(arg_in[i], "-key"))
            {
                c_key_file = arg_in[i + 1];
                param[0] = true;
                i++;
            }
            if (param[0] == true)
            {
                c_key_file = arg_in[i];
            }
            /****************** Check .bin file **************************/
            string s_key_file = c_key_file;
            ifstream file(c_key_file);
            if (!file || !endsWith(s_key_file, ".bin"))
            {
                this->view.error_failure("The argument after -k or dec must be an existing .bin file.\n");
                exit(EXIT_FAILURE);
            }
            isFileBIN = true;
        }
        else if (!strcmp(arg_in[i], "-d") || !strcmp(arg_in[i], "-distr") || !strcmp(arg_in[i], "-distribution"))
        {
            param[1] = true;
        }
        else if (!strcmp(arg_in[i], "-olsbr") || !strcmp(arg_in[i], "-optlsbr"))
        {
            param[2] = true;
        }
    }

    if (param[0] == true && !isFileBIN)
    {
        this->view.error_failure("The argument after -k or dec must be a .bin file.\n");
        exit(EXIT_FAILURE);
    }
}

void PaillierControllerStatR::saveResults()
{
    FILE *file_enc_pix = NULL;
    file_enc_pix = fopen("results_pix.txt", "w+");

    if (file_enc_pix == NULL)
    {
        printf("Error!");
        exit(1);
    }

    fprintf(file_enc_pix, "%" PRIu64 "", n);
    fprintf(file_enc_pix, "\n");
    fprintf(file_enc_pix, "%ld", size_vec_r);

    for (size_t l = 0; l < size_vec_r; l++)
    {
        fprintf(file_enc_pix, "\n");
        fprintf(file_enc_pix, "%" PRIu64 "", set_ZNZStar.at(l));
        for (uint64_t i = 0; i < n; i++)
        {
            fprintf(file_enc_pix, "\n");
            fprintf(file_enc_pix, "%" PRIu16 "", t_pix_enc[l][i]);
        }
    }

    fclose(file_enc_pix);
}