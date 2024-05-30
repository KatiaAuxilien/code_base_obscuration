/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerStatR.hpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 30 mai 2024, 15:50:00
 *
 *******************************************************************************/

#ifndef PAILLIERCONTROLLER_Stat_R
#define PAILLIERCONTROLLER_Stat_R

#include <stdio.h>
#include "include/controller/PaillierController.hpp"

class PaillierControllerStatR : public PaillierController
{
public:
    PaillierControllerStatR();
    ~PaillierControllerStatR();
    void init();

    /**
     *  @brief
     *  @details Vérification pour le programme effectuant des calculs statistiques sur r.
     *  @param char* arg_in[]
     *  @param int size_arg
     *  @param bool param[]
     *				0	bool useKeys = false;
     *				1	bool distributeOnTwo = false;
     *				2	bool optimisationLSB = false;
     *  @authors Katia Auxilien
     *  @date 27/05/2024 11:52:00
     */
    void checkParameters(char *arg_in[], int size_arg, bool param[]);

    /************** 8bits **************/
    /**
     *  \brief
     *  \details
     *  \param
     *  \authors Katia Auxilien
     *  \date 30/05/2024
     */
    template <typename T_in, typename T_out>
    void calc_encrypt(in PaillierPublicKey pubk, Paillier<T_in, T_out> paillier);

    void saveResults();
};
#endif // PAILLIERCONTROLLER_Stat_R

template <typename T_in, typename T_out>
void calc_encrypt(in PaillierPublicKey pubk, Paillier<T_in, T_out> paillier)
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