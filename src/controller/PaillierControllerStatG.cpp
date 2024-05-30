/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerStatG.cpp
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
#include "../../include/controller/PaillierControllerStatG.hpp"

void PaillierControllerStatG::init(){
	this->model = PaillierModel::getInstance();
    this->view = commandLineInterface::getInstance();
}

PaillierControllerStatG::PaillierControllerStatG(){
    init();
};

PaillierControllerStatG::~PaillierControllerStatG(){};

void PaillierControllerStatG::checkParameters(char *arg_in[], int size_arg, bool param[])
{
    convertToLower(arg_in, size_arg);
    
    /********** Initialisation de param[] à false. *************/
    for (int i = 0; i < 5; i++)
    {
        param[i] = false;
    }

    int i;

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

    for (i = i; i < size_arg; i++)
    {
        if (!strcmp(arg_in[i], "-d") || !strcmp(arg_in[i], "-distr") || !strcmp(arg_in[i], "-distribution"))
        {
            param[0] = true;
        }
        else if (!strcmp(arg_in[i], "-olsbr") || !strcmp(arg_in[i], "-optlsbr"))
        {
            param[1] = true;
        }
    }
}

void PaillierControllerStatG::saveResults(){
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