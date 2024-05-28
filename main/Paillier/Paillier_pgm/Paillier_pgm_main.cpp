/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_pgm_main.cpp
 *
 * Description :
 *   Fichier source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024 - Mai 2024
 *
 *******************************************************************************/
#include "../../../include/model/encryption/Paillier/Paillier.hpp"
#include "../../../include/model/encryption/Paillier/keys/Paillier_private_key.hpp"
#include "../../../include/model/encryption/Paillier/keys/Paillier_public_key.hpp"
#include "../../../include/model/filesystem/filesystemCommon.h" //Navigation dans le système de fichier
#include "../../../include/model/filesystem/filesystemPGM.h" 
#include "../../../include/model/image/image_pgm.hpp" 

#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <ctype.h>
#include <errno.h> /* errno */ //TODO : Gestion des erreurs + propre.

using namespace std;

/** Manuel
	 encryption
		enc
		e
		-k utilisation de clé
			[public_key.bin]

		de base on a p et q après enc si on a pas -k

		decryption
		dec
		d
		-k -key utilisation de clé déjà de base.
			[public_key.bin]
		[public_key.bin]

	-d -distr -distribution distribution sur deux pixels.
	-hexp -histogramexpansion recrop de pixel.
	-oLSBr -optlsbr optimisation LSB de r.

	[img.pgm] placée au début ou à la fin
*/

/*********************** Chiffrement/Déchiffrement ***********************/
/************** 8bits **************/
/**
 *  @brief
 *  @details
 *  @param string s_file
 *  @param PaillierPublicKey pubk
 *  @param bool distributeOnTwo
 *  @param bool recropPixels
 *  @authors Katia Auxilien
 *  @date 15/05/2024
 */
template <typename T_in, typename T_out>
void encrypt(string s_file, PaillierPublicKey pubk, bool distributeOnTwo, bool recropPixels, Paillier<T_in, T_out> paillier)
{
	image_pgm img_pgm;

	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_E.pgm";
	char cNomImgEcriteEnc[250];
	strcpy(cNomImgEcriteEnc, s_fileNew.c_str());

	int nH, nW, nTaille;
	uint64_t n = pubk.getN();
	uint64_t g = pubk.getG();

	OCTET *ImgIn;
	img_pgm.lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);

	if (distributeOnTwo)
	{
		uint8_t *ImgOutEnc;
		// T_in *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, OCTET, nH * (2 * nW));
		uint64_t x = 0, y = 1;
		for (int i = 0; i < nTaille; i++)
		{
			// T_in pixel;
			uint8_t pixel;
			if (recropPixels)
			{
				pixel = (ImgIn[i] * n) / 256;
			}
			else
			{
				pixel = ImgIn[i];
			}

			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);
			uint8_t pixel_enc_dec_x = pixel_enc / n;
			uint8_t pixel_enc_dec_y = pixel_enc % n;
			ImgOutEnc[x] = pixel_enc_dec_x;
			ImgOutEnc[y] = pixel_enc_dec_y;
			x = x + 2;
			y = y + 2;
		}

		img_pgm.ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW * 2, n);

		free(ImgIn);
		free(ImgOutEnc);
	}
	else
	{
		uint16_t *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, uint16_t, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint8_t pixel;
			if (recropPixels)
			{

				pixel = (ImgIn[i] * n) / 256;
			}
			else
			{
				pixel = ImgIn[i];
			}

			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);

			ImgOutEnc[i] = pixel_enc;
		}

		img_pgm.ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n);

		free(ImgIn);
		free(ImgOutEnc);
		nTaille = nH * nW;
	}
}

/**
 *  @brief
 *  @details
 *  @param string s_file
 *  @param PaillierPrivateKey pk
 *  @param bool distributeOnTwo
 *  @authors Katia Auxilien
 *  @date 15/05/2024
 */
template <typename T_in, typename T_out>
void decrypt(string s_file, PaillierPrivateKey pk, bool distributeOnTwo, Paillier<T_in, T_out> paillier)
{
	image_pgm img_pgm;

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
	lambda = pk.getLambda();
	mu = pk.getMu();

	OCTET *ImgOutDec;
	img_pgm.lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	if (distributeOnTwo)
	{
		uint8_t *ImgIn;

		allocation_tableau(ImgIn, uint8_t, nTaille);
		n = img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille); // TODO : Retirer and_get_maxgrey
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
		img_pgm.ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW / 2);
		free(ImgIn);
		free(ImgOutDec);
	}
	else
	{
		uint16_t *ImgIn;
		allocation_tableau(ImgIn, uint16_t, nTaille);
		n = img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutDec, OCTET, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint16_t pixel = ImgIn[i];
			uint8_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		img_pgm.ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW);
		free(ImgIn);
		free(ImgOutDec);
	}
}


/************** n > 8bits**************/
template <typename T_in, typename T_out>
void encrypt2(string s_file, PaillierPublicKey pubk, bool distributeOnTwo, bool recropPixels, Paillier<T_in, T_out> paillier)
{
	image_pgm img_pgm;

	char cNomImgLue[250];
	strcpy(cNomImgLue, s_file.c_str());

	string toErase = ".pgm";
	size_t pos = s_file.find(".pgm");
	s_file.erase(pos, toErase.length());
	string s_fileNew = s_file + "_E.pgm";
	char cNomImgEcriteEnc[250];
	strcpy(cNomImgEcriteEnc, s_fileNew.c_str());

	int nH, nW, nTaille;
	uint64_t n = pubk.getN();
	uint64_t g = pubk.getG();

	OCTET *ImgIn;
	img_pgm.lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);

	if (distributeOnTwo)
	{
		uint16_t *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, uint16_t, nH * (2 * nW));
		uint64_t x = 0, y = 1;
		for (int i = 0; i < nTaille; i++)
		{
			// T_in pixel;
			uint16_t pixel;
			if (recropPixels)
			{
				pixel = (ImgIn[i] * n) / 256;
			}
			else
			{
				pixel = ImgIn[i];
			}

			uint32_t pixel_enc = paillier.paillierEncryption(n, g, pixel);
			uint16_t pixel_enc_dec_x = pixel_enc / n;
			uint16_t pixel_enc_dec_y = pixel_enc % n;
			ImgOutEnc[x] = pixel_enc_dec_x;
			ImgOutEnc[y] = pixel_enc_dec_y;
			x = x + 2;
			y = y + 2;
		}

		img_pgm.ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW * 2, n);

		free(ImgIn);
		free(ImgOutEnc);
	}
	else
	{
		uint32_t *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, uint32_t, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint16_t pixel;
			if (recropPixels)
			{

				pixel = (ImgIn[i] * n) / 256;
			}
			else
			{
				pixel = ImgIn[i];
			}

			uint32_t pixel_enc = paillier.paillierEncryption(n, g, pixel);

			ImgOutEnc[i] = pixel_enc;
		}

		img_pgm.ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n);

		free(ImgIn);
		free(ImgOutEnc);
		nTaille = nH * nW;
	}
}

template <typename T_in, typename T_out>
void decrypt2(string s_file, PaillierPrivateKey pk, bool distributeOnTwo, Paillier<T_in, T_out> paillier)
{
	image_pgm img_pgm;

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
	lambda = pk.getLambda();
	mu = pk.getMu();

	OCTET *ImgOutDec;
	img_pgm.lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	if (distributeOnTwo)
	{
		uint16_t *ImgIn;

		allocation_tableau(ImgIn, uint16_t, nTaille);
		n = img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille); // TODO : Retirer and_get_maxgrey
		allocation_tableau(ImgOutDec, OCTET, nH * (nW / 2));

		int x = 0, y = 1;
		for (int i = 0; i < nH * (nW / 2); i++)
		{
			uint32_t pixel;
			uint16_t pixel_enc_dec_x = ImgIn[x];
			uint16_t pixel_enc_dec_y = ImgIn[y];
			pixel = (pixel_enc_dec_x * n) + pixel_enc_dec_y;
			x = x + 2;
			y = y + 2;
			uint16_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		img_pgm.ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW / 2);
		free(ImgIn);
		free(ImgOutDec);
	}
	else
	{
		uint32_t *ImgIn;
		allocation_tableau(ImgIn, uint32_t, nTaille);
		n = img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutDec, OCTET, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint32_t pixel = ImgIn[i];
			uint16_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		img_pgm.ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW);
		free(ImgIn);
		free(ImgOutDec);
	}
}


int main(int argc, char **argv)
{
	/*********************** Traitement d'arguments ***********************/

	if (argc < 3)
	{
		printf("Usage : [e or ek or dk] [params] image_file.pgm\n e p q file.pgm\n ek public_key.bin image_file.pgm\n dk private_key.bin image_file_encrypted.pgm\n");
		return 1;
	}

	bool parameters[5];
	char *c_file;
	char *c_key_file;
	uint64_t lambda, n, mu, g, p, q;

	convertToLower(argv, argc);
	checkParameters(argv, argc, parameters, c_key_file, c_file, p, q, n, lambda);

	bool isEncryption = parameters[0];
	bool useKeys = parameters[1];
	bool distributeOnTwo = parameters[2];
	bool recropPixels = parameters[3];
	bool optimisationLSB = parameters[4];

	string s_file = c_file;
	string s_key_file;
	if (isEncryption && useKeys)
	{
		s_key_file = c_key_file;
	}

	/********************************************************************/

	/*********************** Traitement de clé ***********************/

	PaillierPrivateKey pk;
	PaillierPublicKey pubk;

	if (!useKeys && isEncryption)
	{
		Paillier<uint64_t, uint64_t> paillier;
		mu = 0;
		g = paillier.generate_g_64t(n,lambda);
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
		if(lambda == 0 || mu == 0 || p == 0 || q == 0 || n == 0 || g == 0){
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

		FILE *f_private_key = NULL;

		f_private_key = fopen("Paillier_private_key.bin", "w+b");

		if (f_private_key == NULL)
		{
			cmd_colorError();			
			fprintf(stderr, "Error ! Opening Paillier_private_key.bin\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}

		fwrite(&pk, sizeof(PaillierPrivateKey), 1, f_private_key);

		fclose(f_private_key);

		FILE *f_public_key = NULL;
		f_public_key = fopen("Paillier_public_key.bin", "w+b");

		if (f_public_key == NULL)
		{
			cmd_colorError();			
			fprintf(stderr, "Error ! Opening Paillier_public_key.bin\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
		fwrite(&pubk, sizeof(PaillierPublicKey), 1, f_public_key);

		fclose(f_public_key);
	}
	else
	{
		if (!isEncryption)
		{
			size_t size;
			FILE *f_private_key = NULL;

			f_private_key = fopen(c_key_file, "rb");

			if (f_private_key == NULL)
			{
				cmd_colorError();			
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				cmd_colorStandard();
				exit(EXIT_FAILURE);
			}

			size = sizeof(PaillierPrivateKey);
			fread(&pk, size, 1, f_private_key);
			// if (result != size) {fputs ("Reading error",stderr); return 1;}

			fclose(f_private_key);
		}
		if (isEncryption)
		{
			size_t size;
			FILE *f_public_key = NULL;
			f_public_key = fopen(c_key_file, "rb");

			if (f_public_key == NULL)
			{
				cmd_colorError();
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				cmd_colorStandard();
				exit(EXIT_FAILURE);
			}
			size = sizeof(PaillierPublicKey);
			fread(&pubk, size, 1, f_public_key);
			// if (result != size) {fputs ("Reading error",stderr); return 1;}

			fclose(f_public_key);
		}
	}

	/*********************** Instanciations de Paillier en fonction de n ***********************/

	/*********************** Chiffrement ***********************/
	if (isEncryption)
	{
		n = pubk.getN();
		if (n <= 256)
		{
			printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
			printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
			Paillier<uint8_t, uint16_t> paillier;
			encrypt(s_file, pubk, distributeOnTwo, recropPixels, paillier);
		}
		else if (n > 256 && n <= 65535)
		{

			Paillier<uint16_t, uint32_t> paillier;
			encrypt2(s_file, pubk, distributeOnTwo, recropPixels, paillier);
		}
		else
		{
			cmd_colorError();
			fprintf(stderr, "n value not supported.");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
	}
	/*********************** Déchiffrement ***********************/
	else
	{
		n = pk.getN();
		if (n <= 256)
		{
			printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
			printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
			Paillier<uint8_t, uint16_t> paillier;
			decrypt(s_file, pk, distributeOnTwo,paillier);
		}
		else if (n > 256 && n <= 65535)
		{
			Paillier<uint16_t, uint32_t> paillier;
			decrypt2(s_file, pk, distributeOnTwo,paillier);
		}
		else
		{
			cmd_colorError();
			fprintf(stderr, "n value not supported.");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
	}
}