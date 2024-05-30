/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerStatG.hpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 30 mai 2024, 15:50
 *
 *******************************************************************************/

#ifndef PAILLIERCONTROLLER_Stat_G
#define PAILLIERCONTROLLER_Stat_G

#include <stdio.h>
#include "include/controller/PaillierController.hpp"

class PaillierControllerStatG : public PaillierController
{
public:
    PaillierControllerStatG();
    ~PaillierControllerStatG();
	void init();

    /**
     *  @brief
     *  @details Vérification pour le programme effectuant des calculs statistiques sur g.
     *  @param char* arg_in[]
     *  @param bool param[]
     *				0	bool distributeOnTwo = false;
     *				1	bool optimisationLSB = false;
     *  @authors Katia Auxilien
     *  @date 27/05/2024 11:52:00
     */
    void checkParameters(char *arg_in[], int size_arg, bool param[]);


    void saveResults();
	
/*********************** Chiffrement/Déchiffrement ***********************/

    /************** 8bits **************/
    /**
     *  \brief
     *  \details
     *  \param 
     *  \authors Katia Auxilien
     *  \date 30/05/2024
     */
    template <typename T_in, typename T_out>
    void calc_encrypt(in uint64_t p, in uint64_t q, Paillier<T_in,T_out> paillier);

};
#endif // PAILLIERCONTROLLER_Stat_G

template <typename T_in, typename T_out>
void calc_encrypt()
{
	PaillierPrivateKey pk;
	PaillierPublicKey pubk;

	Paillier<uint64_t, uint64_t> paillier;
	controller.getModel()->setPaillierGenerationKey(paillier);

	uint64_t mu = 0;
	std::vector<uint64_t> set_ZN2ZStar = paillier.get_set_ZN2ZStar(n, lambda);

	for (size_t g = 0; g < set_ZN2ZStar.size(); g++)
	{

		paillier.generatePrivateKey_64t(lambda, mu, p, q, n, g);

		if (mu == 0)
		{
			cmd_colorError();
			fprintf(stderr, "ERROR with g, no value found for g where mu exist.\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}

		pk = PaillierPrivateKey(lambda, mu, n);
		pubk = PaillierPublicKey(n, g);
		if (lambda == 0 || mu == 0 || p == 0 || q == 0 || n == 0 || g == 0)
		{
			cmd_colorError();
			fprintf(stderr, "Error in generation of private key.\n");
			printf("p = %" PRIu64 "\n", p);
			printf("q = %" PRIu64 "\n", q);
			printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
			printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
			printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
			printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}

		/*********************** Instanciations de Paillier en fonction de n ***********************/

		/*********************** Chiffrement ***********************/
		if (n <= 256)
		{
			Paillier<uint8_t, uint16_t> paillier;
			uint64_t n = pubk.getN();
			uint64_t g = pubk.getG();
			std::vector<uint64_t> set_ZNZStar = paillier.get_set_ZNZStar(n);

			size_t size_vec_r = set_ZNZStar.size();

			uint16_t t_pix_enc[size_vec_r][n];

			for (size_t l = 0; l < size_vec_r; l++)
			{
				for (uint64_t i = 0; i < n; i++)
				{

					unsigned char msg = i;
					uint16_t pixel_enc = paillier.paillierEncryption(n, g, msg, set_ZNZStar.at(l));
					t_pix_enc[l][i] = pixel_enc;
					if (i == 0)
					{
						fprintf(stdout, "Enc (0) : %" PRIu16 "\n", pixel_enc);
					}
				}
			}
		}
	}
	else
	{
		cmd_colorError();
		fprintf(stderr, "n value not supported.");
		cmd_colorStandard();
		exit(EXIT_FAILURE);
	}
   
}
