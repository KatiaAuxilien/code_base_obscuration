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

void PaillierControllerStatG::init()
{
    this->model = PaillierModel::getInstance();
    this->view = commandLineInterface::getInstance();
}

PaillierControllerStatG::PaillierControllerStatG()
{
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

    uint64_t p = check_p_q_arg(arg_in[1]);
    if (p == 1)
    {
        getView()->error_failure("checkParameters : p == 1");
        exit(EXIT_FAILURE);
    }
    getModel()->setP(p);

    uint64_t q = check_p_q_arg(arg_in[2]);
    if (q == 1)
    {
        getView()->error_failure("checkParameters : q == 1");
        exit(EXIT_FAILURE);
    }
    getModel()->setQ(q);

    Paillier<uint64_t, uint64_t> paillier;
    uint64_t pgc_pq = paillier.gcd_64t(p * q, (p - 1) * (q - 1));

    if (pgc_pq != 1)
    {
        string msg = "pgcd(p * q, (p - 1) * (q - 1))= " + to_string(pgc_pq) + "\np & q arguments must have a gcd = 1. Please retry with others p and q.\n";
        this->getView()->error_failure(msg);
        exit(EXIT_FAILURE);
    }
    getModel()->setN(p * q);
    getModel()->setPaillierGenerationKey(paillier);
    uint64_t lambda = paillier.lcm_64t(p - 1, q - 1);

    getModel()->setLambda(lambda);

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

void PaillierControllerStatG::calc_encrypt_all_g()
{
    PaillierPrivateKey pk;
    PaillierPublicKey pubk;

    Paillier<uint64_t, uint64_t> paillier = getModel()->getPaillierGenerationKey();

    uint64_t mu, lambda;
    std::vector<uint64_t> set_ZN2ZStar = paillier.get_set_ZN2ZStar(getModel()->getN(), getModel()->getLambda());
    // Faire que 4 5 valeurs.
    if (getModel()->getN() <= 256)
    {
        Paillier<uint8_t, uint16_t> paillier8Bit;

        std::vector<uint64_t> set_ZNZStar = paillier8Bit.get_set_ZNZStar(getModel()->getN());
        size_t size_vec_r = set_ZNZStar.size();
        size_t size_vec_g = set_ZN2ZStar.size();

        printf("sizevecg = %zu\n", size_vec_g);

        std::vector<std::vector<std::vector<uint16_t>>> t_pix_enc_r_g(size_vec_g,
                                                                      std::vector<std::vector<uint16_t>>(size_vec_r,
                                                                                                         std::vector<uint16_t>(getModel()->getN())));

        // uint16_t t_pix_enc_r_g[size_vec_g][size_vec_r][getModel()->getN()];

        for (size_t j = 1; j < size_vec_g; j++)
        {
            getModel()->setG(set_ZN2ZStar.at(j));
            mu = 0;
            lambda = 0;
            paillier.generatePrivateKey_64t(lambda,
                                            mu,
                                            getModel()->getP(),
                                            getModel()->getQ(),
                                            getModel()->getN(),
                                            set_ZN2ZStar.at(j));

            printf("p = %" PRIu64 "\n", getModel()->getP());
            printf("q = %" PRIu64 "\n", getModel()->getQ());
            printf("Pub Key G = %" PRIu64 "\n", getModel()->getG());
            printf("Pub Key N = %" PRIu64 "\n", getModel()->getN());
            printf("Priv Key lambda = %" PRIu64 "\n", getModel()->getLambda());
            printf("Priv Key mu = %" PRIu64 "\n", getModel()->getMu());

            if (mu == 0)
            {
                getView()->error_failure("ERROR with g, no value found for g where mu exist.\n");
                exit(EXIT_FAILURE);
            }

            getModel()->setLambda(lambda);
            getModel()->setMu(mu);

            getModel()->setPrivateKey(PaillierPrivateKey(getModel()->getLambda(),
                                                         getModel()->getMu(),
                                                         getModel()->getN()));
            getModel()->setPublicKey(PaillierPublicKey(getModel()->getN(),
                                                       getModel()->getG()));

            if (getModel()->getPrivateKey().getLambda() == 0 ||
                getModel()->getPrivateKey().getMu() == 0 ||
                getModel()->getP() == 0 ||
                getModel()->getQ() == 0 ||
                getModel()->getPublicKey().getN() == 0 ||
                getModel()->getPublicKey().getG() == 0)
            {
                getView()->error_failure("Error in generation of private key.\n");

                printf("p = %" PRIu64 "\n", getModel()->getP());
                printf("q = %" PRIu64 "\n", getModel()->getQ());
                printf("Pub Key G = %" PRIu64 "\n", getModel()->getPublicKey().getG());
                printf("Pub Key N = %" PRIu64 "\n", getModel()->getPublicKey().getN());
                printf("Priv Key lambda = %" PRIu64 "\n", getModel()->getPrivateKey().getLambda());
                printf("Priv Key mu = %" PRIu64 "\n", getModel()->getPrivateKey().getMu());

                exit(EXIT_FAILURE);
            }

            /*********************** Instanciations de Paillier en fonction de n ***********************/

            /*********************** Chiffrement ***********************/

            for (size_t k = 0; k < size_vec_r; k++)
            {
                for (uint64_t i = 0; i < getModel()->getPublicKey().getN(); i++)
                {
                    unsigned char msg = i;
                    uint16_t pixel_enc = paillier8Bit.paillierEncryption(getModel()->getPublicKey().getN(),
                                                                         getModel()->getPublicKey().getG(),
                                                                         msg,
                                                                         set_ZNZStar.at(k));
                    t_pix_enc_r_g[j][k][i] = pixel_enc;
                }
            }
        }

        FILE *file_enc_pix = NULL;
        file_enc_pix = fopen("results_pix.txt", "w+");

        if (file_enc_pix == NULL)
        {
            getView()->error_failure("Error during saving results.");
            exit(EXIT_FAILURE);
        }

        fprintf(file_enc_pix, "%" PRIu64 "", getModel()->getN());
        fprintf(file_enc_pix, "\n");
        fprintf(file_enc_pix, "%" PRIu64 "", size_vec_g);
        fprintf(file_enc_pix, "\n");
        fprintf(file_enc_pix, "%ld", size_vec_r);

        for (size_t j = 0; j < size_vec_g; j++)
        {
            fprintf(file_enc_pix, "\n");
            fprintf(file_enc_pix, "%" PRIu64 "", set_ZN2ZStar.at(j));
            for (size_t k = 0; k < size_vec_r; k++)
            {
                fprintf(file_enc_pix, "\n");
                fprintf(file_enc_pix, "%" PRIu64 "", set_ZNZStar.at(k));
                for (uint64_t i = 0; i < getModel()->getN(); i++)
                {
                    fprintf(file_enc_pix, "\n");
                    fprintf(file_enc_pix, "%" PRIu16 "", t_pix_enc_r_g[j][k][i]);
                }
            }
        }

        fclose(file_enc_pix);

        t_pix_enc_r_g.clear();
    }
    else
    {
        getView()->error_failure("n value not supported.");
        exit(EXIT_FAILURE);
    }
}

void PaillierControllerStatG::calc_encrypt_10_g()
{
    PaillierPrivateKey pk;
    PaillierPublicKey pubk;

    Paillier<uint64_t, uint64_t> paillier = getModel()->getPaillierGenerationKey();

    uint64_t mu, lambda;

    if (getModel()->getN() <= 256)
    {
        Paillier<uint8_t, uint16_t> paillier8Bit;

        std::vector<uint64_t> set_ZNZStar = paillier8Bit.get_set_ZNZStar(getModel()->getN());
        size_t size_vec_r = set_ZNZStar.size();
        size_t size_vec_g = 10;

        printf("sizevecg = %zu\n", size_vec_g);


        for (size_t j = 0; j < size_vec_g; j++)
        {

            uint64_t g = paillier.generate_g_64t(getModel()->getN(), getModel()->getLambda());

            getModel()->setG(g);
            mu = 0;
            lambda = 0;
            paillier.generatePrivateKey_64t(lambda,
                                            mu,
                                            getModel()->getP(),
                                            getModel()->getQ(),
                                            getModel()->getN(),
                                            getModel()->getG());


            if (mu == 0)
            {
                getView()->error_failure("ERROR with g, no value found for g where mu exist.\n");
                exit(EXIT_FAILURE);
            }

            getModel()->setLambda(lambda);
            getModel()->setMu(mu);

            getModel()->setPrivateKey(PaillierPrivateKey(getModel()->getLambda(),
                                                         getModel()->getMu(),
                                                         getModel()->getN()));
            getModel()->setPublicKey(PaillierPublicKey(getModel()->getN(),
                                                       getModel()->getG()));

            if (getModel()->getPrivateKey().getLambda() == 0 ||
                getModel()->getPrivateKey().getMu() == 0 ||
                getModel()->getP() == 0 ||
                getModel()->getQ() == 0 ||
                getModel()->getPublicKey().getN() == 0 ||
                getModel()->getPublicKey().getG() == 0)
            {
                getView()->error_failure("Error in generation of private key.\n");

                printf("p = %" PRIu64 "\n", getModel()->getP());
                printf("q = %" PRIu64 "\n", getModel()->getQ());
                printf("Pub Key G = %" PRIu64 "\n", getModel()->getPublicKey().getG());
                printf("Pub Key N = %" PRIu64 "\n", getModel()->getPublicKey().getN());
                printf("Priv Key lambda = %" PRIu64 "\n", getModel()->getPrivateKey().getLambda());
                printf("Priv Key mu = %" PRIu64 "\n", getModel()->getPrivateKey().getMu());

                exit(EXIT_FAILURE);
            }

            /*********************** Instanciations de Paillier en fonction de n ***********************/
            uint16_t t_pix_enc[size_vec_r][getModel()->getN()];

            /*********************** Chiffrement ***********************/

            for (size_t k = 0; k < size_vec_r; k++)
            {
                for (uint64_t i = 0; i < getModel()->getPublicKey().getN(); i++)
                {
                    unsigned char msg = i;
                    uint16_t pixel_enc = paillier8Bit.paillierEncryption(getModel()->getPublicKey().getN(),
                                                                         getModel()->getPublicKey().getG(),
                                                                         msg,
                                                                         set_ZNZStar.at(k));
                    t_pix_enc[k][i] = pixel_enc;
                }
            }

            FILE *file_enc_pix = NULL;
            string titre = "results_pix_"+std::to_string(getModel()->getPublicKey().getG())+".txt";
            file_enc_pix = fopen(titre.c_str(), "w+");

            if (file_enc_pix == NULL)
            {
                printf("Error!");
                exit(1);
            }

            fprintf(file_enc_pix, "%" PRIu64 "", getModel()->getPublicKey().getN());
            fprintf(file_enc_pix, "\n");
            fprintf(file_enc_pix, "%ld", set_ZNZStar.size());

            for (size_t l = 0; l < set_ZNZStar.size(); l++)
            {
                fprintf(file_enc_pix, "\n");
                fprintf(file_enc_pix, "%" PRIu64 "", set_ZNZStar.at(l));
                for (uint64_t i = 0; i < getModel()->getPublicKey().getN(); i++)
                {
                    fprintf(file_enc_pix, "\n");
                    fprintf(file_enc_pix, "%" PRIu16 "", t_pix_enc[l][i]);
                }
            }

            fclose(file_enc_pix);
            delete[] t_pix_enc;
        }
    }
    else
    {
        getView()->error_failure("n value not supported.");
        exit(EXIT_FAILURE);
    }
}
