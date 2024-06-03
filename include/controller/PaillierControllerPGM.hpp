/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerPGM.hpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 29 mai 2024, 13:55:00
 *
 *******************************************************************************/

#ifndef PAILLIERCONTROLLER_PGM
#define PAILLIERCONTROLLER_PGM

#include <stdio.h>
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <ctype.h>

#include "../../include/controller/PaillierController.hpp"
#include "../../include/model/image/image_portable.hpp"
#include "../../include/model/image/image_pgm.hpp"
#include "../../include/model/filesystem/filesystemPGM.h"

class PaillierControllerPGM : public PaillierController
{

private:
	char *c_file;

public:
	PaillierControllerPGM();
	~PaillierControllerPGM();
	void init();

	const char *getCFile() const;

	void setCFile(char *newCFile);

	/**
	 *  \brief
	 *  \details Vérification
	 *  \param char* arg_in[]
	 *  \param bool param[]
	 *				0	bool isEncryption = false ;
	 *				1	bool useKeys = false;
	 *				2	bool distributeOnTwo = false;
	 *				3	bool recropPixels = false;
	 *				4	bool optimisationLSB = false;
	 *  \authors Katia Auxilien
	 *  \date 15/05/2024 9:00:00
	 */
	void checkParameters(char *arg_in[], int size_arg, bool param[]);

	/*********************** Chiffrement/Déchiffrement ***********************/

	/**
	 *  \brief
	 *  \details
	 *  \param OCTET ImgPixel
	 * 	\param bool recropPixels
	 *	\param Paillier<T_in, T_out> paillier
	 *  \authors Katia Auxilien
	 *  \date 03/06/2024
	 */
	template <typename T_in, typename T_out>
	uint8_t histogramExpansion(OCTET ImgPixel, bool recropPixels, Paillier<T_in, T_out> paillier);

	/************** 8bits **************/
	/**
	 *  \brief
	 *  \details
	 *  \param bool distributeOnTwo
	 *  \param bool recropPixels
	 *  \param Paillier<T_in, T_out> paillier
	 *  \authors Katia Auxilien
	 *  \date 15/05/2024
	 */
	template <typename T_in, typename T_out>
	void encrypt(bool distributeOnTwo, bool recropPixels, Paillier<T_in, T_out> paillier);

	/**
	 *  \brief
	 *  \details
	 *  \param bool distributeOnTwo
	 *  \authors Katia Auxilien
	 *  \date 15/05/2024
	 */
	template <typename T_in, typename T_out>
	void decrypt(bool distributeOnTwo, Paillier<T_in, T_out> paillier);

	/**
	 *  \brief
	 *  \details
	 *  \param bool compression
	 *	\param Paillier<T_in, T_out> paillier
	 *  \authors Katia Auxilien
	 *  \date 03/06/2024
	 */
	template <typename T_in, typename T_out>
	void encryptCompression(Paillier<T_in, T_out> paillier);

	/**
	 *  \brief
	 *  \details
	 *  \param bool compression
	 *	\param Paillier<T_in, T_out> paillier
	 *  \authors Katia Auxilien
	 *  \date 03/06/2024
	 */
	template <typename T_in, typename T_out>
	void decryptCompression(Paillier<T_in, T_out> paillier);

	/************** n > 8bits**************/

	// /**
	//  *  \brief
	//  *  \details
	//  *  \param bool distributeOnTwo
	//  *  \param bool recropPixels
	//  *  \param Paillier<T_in, T_out> paillier
	//  *  \authors Katia Auxilien
	//  *  \date 15/05/2024
	//  */
	// template <typename T_in, typename T_out>
	// void encrypt2(bool distributeOnTwo, bool recropPixels, Paillier<T_in,T_out> paillier);

	// /**
	//  *  \brief
	//  *  \details
	//  *  \param bool distributeOnTwo
	//  *  \param bool recropPixels
	//  *  \param Paillier<T_in, T_out> paillier
	//  *  \authors Katia Auxilien
	//  *  \date 15/05/2024
	//  */
	// template <typename T_in, typename T_out>
	// void decrypt2(bool distributeOnTwo, Paillier<T_in,T_out> paillier);
};

/************** 8bits **************/

template <typename T_in, typename T_out>
uint8_t histogramExpansion(OCTET ImgPixel, bool recropPixels, Paillier<T_in, T_out> paillier)
{
	uint8_t pixel;
	if (recropPixels)
	{
		pixel = (ImgPixel * this->model->getInstance()->getPublicKey().getN()) / 256;
	}
	else
	{
		pixel = ImgPixel;
	}
	return pixel;
}

template <typename T_in, typename T_out>
void PaillierControllerPGM::encrypt(bool distributeOnTwo, bool recropPixels, Paillier<T_in, T_out> paillier)
{
	string s_file = this->getCFile();

	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_E.pgm";
	char cNomImgEcriteEnc[250];
	strcpy(cNomImgEcriteEnc, s_fileNew.c_str());

	int nH, nW, nTaille;
	uint64_t n = this->model->getInstance()->getPublicKey().getN();
	uint64_t g = this->model->getInstance()->getPublicKey().getG();

	OCTET *ImgIn;
	image_pgm::lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);

	if (distributeOnTwo)
	{
		uint8_t *ImgOutEnc;
		// T_in *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		image_pgm::lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, OCTET, nH * (2 * nW));
		uint64_t x = 0, y = 1;
		for (int i = 0; i < nTaille; i++)
		{
			uint8_t pixel = encrypt_pixel(recropPixels, ImgIn[i], paillier);

			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);
			uint8_t pixel_enc_dec_x = pixel_enc / n;
			uint8_t pixel_enc_dec_y = pixel_enc % n;
			ImgOutEnc[x] = pixel_enc_dec_x;
			ImgOutEnc[y] = pixel_enc_dec_y;
			x = x + 2;
			y = y + 2;
		}

		image_pgm::ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW * 2, n);

		free(ImgIn);
		free(ImgOutEnc);
	}
	else
	{
		uint16_t *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		image_pgm::lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, uint16_t, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint8_t pixel = encrypt_pixel(recropPixels, ImgIn[i], paillier);
			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);
			ImgOutEnc[i] = pixel_enc;
		}

		image_pgm::ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n);

		free(ImgIn);
		free(ImgOutEnc);
		nTaille = nH * nW;
	}
}

template <typename T_in, typename T_out>
void PaillierControllerPGM::decrypt(bool distributeOnTwo, Paillier<T_in, T_out> paillier)
{
	string s_file = this->getCFile();
	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_D.pgm";
	char cNomImgEcriteDec[250];
	strcpy(cNomImgEcriteDec, s_fileNew.c_str());

	int nH, nW, nTaille;
	uint64_t n, lambda, mu;
	lambda = this->model->getInstance()->getPrivateKey().getLambda();
	mu = this->model->getInstance()->getPrivateKey().getMu();
	n = this->model->getInstance()->getPrivateKey().getN();

	OCTET *ImgOutDec;
	image_pgm::lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	if (distributeOnTwo)
	{
		uint8_t *ImgIn;

		allocation_tableau(ImgIn, uint8_t, nTaille);
		image_pgm::lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille); // TODO : Retirer and_get_maxgrey
		allocation_tableau(ImgOutDec, OCTET, nH * (nW / 2));

		int x = 0, y = 1;
		for (int i = 0; i < nH * (nW / 2); i++)
		{
			uint16_t pixel;
			uint8_t pixel_enc_dec_x = ImgIn[x];
			uint8_t pixel_enc_dec_y = ImgIn[y];
			pixel = (pixel_enc_dec_x * n) + pixel_enc_dec_y;
			x = x + 2;
			y = y + 2;
			uint8_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		image_pgm::ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW / 2);
		free(ImgIn);
		free(ImgOutDec);
	}
	else
	{
		uint16_t *ImgIn;
		allocation_tableau(ImgIn, uint16_t, nTaille);
		image_pgm::lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutDec, OCTET, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint16_t pixel = ImgIn[i];
			uint8_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		image_pgm::ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW);
		free(ImgIn);
		free(ImgOutDec);
	}
}

template <typename T_in, typename T_out>
void encryptCompression(Paillier<T_in, T_out> paillier)
{
	string s_file = this->getCFile();

	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_E.pgm";
	char cNomImgEcriteEnc[250];
	strcpy(cNomImgEcriteEnc, s_fileNew.c_str());

	int nH, nW, nTaille;
	uint64_t n = this->model->getInstance()->getPublicKey().getN();
	uint64_t g = this->model->getInstance()->getPublicKey().getG();

	OCTET *ImgIn;
	image_pgm::lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);

	if (distributeOnTwo)
	{
		uint8_t *ImgOutEnc;
		// T_in *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		image_pgm::lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, OCTET, nH * (2 * nW));
		uint64_t x = 0, y = 1;
		for (int i = 0; i < nTaille; i++)
		{
			uint8_t pixel = encrypt_pixel(recropPixels, ImgIn[i], paillier);

			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);
			uint8_t pixel_enc_dec_x = pixel_enc / n;
			uint8_t pixel_enc_dec_y = pixel_enc % n;
			ImgOutEnc[x] = pixel_enc_dec_x;
			ImgOutEnc[y] = pixel_enc_dec_y;
			x = x + 2;
			y = y + 2;
		}

		image_pgm::ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW * 2, n);

		free(ImgIn);
		free(ImgOutEnc);
	}
	else
	{
		uint16_t *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		image_pgm::lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, uint16_t, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint8_t pixel = encrypt_pixel(recropPixels, ImgIn[i], paillier);
			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);
			ImgOutEnc[i] = pixel_enc;
		}

		image_pgm::ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n);

		free(ImgIn);
		free(ImgOutEnc);
		nTaille = nH * nW;
	}
}

template <typename T_in, typename T_out>
void decryptCompression(Paillier<T_in, T_out> paillier)
{
	
	string s_file = this->getCFile();
	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_D.pgm";
	char cNomImgEcriteDec[250];
	strcpy(cNomImgEcriteDec, s_fileNew.c_str());

	int nH, nW, nTaille;
	uint64_t n, lambda, mu;
	lambda = this->model->getInstance()->getPrivateKey().getLambda();
	mu = this->model->getInstance()->getPrivateKey().getMu();
	n = this->model->getInstance()->getPrivateKey().getN();

	OCTET *ImgOutDec;
	image_pgm::lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	if (distributeOnTwo)
	{
		uint8_t *ImgIn;

		allocation_tableau(ImgIn, uint8_t, nTaille);
		image_pgm::lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille); // TODO : Retirer and_get_maxgrey
		allocation_tableau(ImgOutDec, OCTET, nH * (nW / 2));

		int x = 0, y = 1;
		for (int i = 0; i < nH * (nW / 2); i++)
		{
			uint16_t pixel;
			uint8_t pixel_enc_dec_x = ImgIn[x];
			uint8_t pixel_enc_dec_y = ImgIn[y];
			pixel = (pixel_enc_dec_x * n) + pixel_enc_dec_y;
			x = x + 2;
			y = y + 2;
			uint8_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		image_pgm::ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW / 2);
		free(ImgIn);
		free(ImgOutDec);
	}
	else
	{
		uint16_t *ImgIn;
		allocation_tableau(ImgIn, uint16_t, nTaille);
		image_pgm::lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutDec, OCTET, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint16_t pixel = ImgIn[i];
			uint8_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		image_pgm::ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW);
		free(ImgIn);
		free(ImgOutDec);
	}

}

#endif // PAILLIERCONTROLLER_PGM