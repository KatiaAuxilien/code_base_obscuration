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
#include <ctype.h> //uintN_t
#include <bitset> //Bitwise operators

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

	/**
	 * \brief Afficher le manuel du programme.
	 * \author Katia Auxilien
	 * \date 07/06/2024 16:41:00
	 */
	void printHelp();

	/*********************** Chiffrement/Déchiffrement ***********************/
	/**
	 *  \brief
	 *  \details
	 *  \param OCTET ImgPixel
	 * 	\param bool recropPixels
	 *  \authors Katia Auxilien
	 *  \date 03/06/2024
	 */
	uint8_t histogramExpansion(OCTET ImgPixel, bool recropPixels);

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
	void encryptCompression(bool distributeOnTwo,bool recropPixels,Paillier<T_in, T_out> paillier);

	/**
	 *  \brief
	 *  \details
	 *  \param uint16_t *pt_image
	 *	\param int nb_lignes
	 	\param int nb_colonnes
	 *  \authors Katia Auxilien
	 *  \date 07/07/2024
	 */
	uint16_t * compressBits(uint16_t *ImgInEnc, int nb_lignes, int nb_colonnes);

	/**
	 *  \brief
	 *  \details
	 *  \param uint16_t *pt_image
	 *	\param int nb_lignes
	 	\param int nb_colonnes
	 *  \authors Katia Auxilien
	 *  \date 07/07/2024
	 */
	uint16_t * decompressBits(uint16_t *ImgInEnc, int nb_lignes, int nb_colonnes, int nTailleOriginale));


	/**
	 *  \brief
	 *  \details
	 *  \param bool compression
	 *	\param Paillier<T_in, T_out> paillier
	 *  \authors Katia Auxilien
	 *  \date 03/06/2024
	 */
	template <typename T_in, typename T_out>
	void decryptCompression(bool distributeOnTwo, Paillier<T_in, T_out> paillier);

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
void PaillierControllerPGM::encrypt(bool distributeOnTwo, bool recropPixels, Paillier<T_in, T_out> paillier)
{
	string s_file = getCFile();

	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_E.pgm";
	char cNomImgEcriteEnc[250];
	strcpy(cNomImgEcriteEnc, s_fileNew.c_str());

	int nH, nW, nTaille;
	uint64_t n = model->getInstance()->getPublicKey().getN();
	uint64_t g = model->getInstance()->getPublicKey().getG();

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
			uint8_t pixel = histogramExpansion(ImgIn[i],recropPixels);

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
			uint8_t pixel = histogramExpansion(ImgIn[i],recropPixels);
			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);
			ImgOutEnc[i] = pixel_enc;
		}

		image_pgm::ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n*n);

		free(ImgIn);
		free(ImgOutEnc);
		nTaille = nH * nW;
	}
}

template <typename T_in, typename T_out>
void PaillierControllerPGM::decrypt(bool distributeOnTwo, Paillier<T_in, T_out> paillier)
{
	string s_file = getCFile();
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
	lambda = model->getInstance()->getPrivateKey().getLambda();
	mu = model->getInstance()->getPrivateKey().getMu();
	n = model->getInstance()->getPrivateKey().getN();

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
void PaillierControllerPGM::encryptCompression(bool distributeOnTwo,bool recropPixels,Paillier<T_in, T_out> paillier)
{
	string s_file = getCFile();

	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_E.pgm";
	char cNomImgEcriteEnc[250];
	strcpy(cNomImgEcriteEnc, s_fileNew.c_str());

	int nH, nW, nTaille;
	uint64_t n = model->getInstance()->getPublicKey().getN();
	uint64_t g = model->getInstance()->getPublicKey().getG();

	OCTET *ImgIn;
	image_pgm::lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);

		uint16_t *ImgOutEnc;

		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		image_pgm::lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, uint16_t, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint8_t pixel = histogramExpansion(ImgIn[i],recropPixels);
			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);

			while(pixel_enc % 32 != 0){
				pixel_enc = paillier.paillierEncryption(n, g, pixel);
	
			}
			
			ImgOutEnc[i] = pixel_enc;
		}


		uint16_t *ImgOutEncComp = compressBits(ImgOutEnc,nH,nW);
		int nbPixelsComp = ceil((double)(nH * nW * 11)/16);

		//TODO : Ajouter étape de décomposition nbPixel

		int nHComp = 256;
		int nWComp = 704;
		/*
		 
		 */


		image_pgm::ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEncComp, nHComp, nWComp, n*n);

		free(ImgIn);
		free(ImgOutEnc);
		delete[] ImgOutEncComp;

}

template <typename T_in, typename T_out>
void PaillierControllerPGM::decryptCompression(bool distributeOnTwo, Paillier<T_in, T_out> paillier)
{
	string s_file = getCFile();
	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_D.pgm";
	char cNomImgEcriteDec[250];
	strcpy(cNomImgEcriteDec, s_fileNew.c_str());

	int nH, nW, nTaille, nHComp, nWComp, nTailleComp;
	uint64_t n, lambda, mu;
	lambda = model->getInstance()->getPrivateKey().getLambda();
	mu = model->getInstance()->getPrivateKey().getMu();
	n = model->getInstance()->getPrivateKey().getN();

	OCTET *ImgOutDec;
	image_pgm::lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);
	nTailleComp = nHComp * nWComp;

		uint16_t *ImgInComp;
		allocation_tableau(ImgInComp, uint16_t, nTailleComp);
		image_pgm::lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgInComp, nTailleComp);

		//TODO : Ajouter une étape pour retrouver la taille originale.

		/*
		On sait que nH ou nW est la dimension originale.
		*/

		nTaille = 512*512;

		allocation_tableau(ImgOutDec, OCTET, nTaille);

		uint16_t *ImgInEnc = decompressBits(ImgInComp,nH,nW, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint16_t pixel = ImgInEnc[i];
			uint8_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		image_pgm::ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW);
		free(ImgInComp);
		free(ImgOutDec);
}

#endif // PAILLIERCONTROLLER_PGM