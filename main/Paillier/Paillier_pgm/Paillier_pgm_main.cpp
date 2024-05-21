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
#include "../../../include/encryption/Paillier/Paillier.hpp"
#include "../../../include/encryption/Paillier/keys/Paillier_private_key.hpp"
#include "../../../include/encryption/Paillier/keys/Paillier_public_key.hpp"
#include "../../../include/filesystem/filesystemCommon.h"
#include "../../../include/filesystem/filesystemPGM.h"
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

/**
 *  @brief
 *  @details
 *  @authors Katia Auxilien
 *  @date 15/05/2024
 */
void cmd_colorStandard()
{
	printf("\e[0;36m");
}

/**
 *  @brief
 *  @details
 *  @authors Katia Auxilien
 *  @date 15/05/2024
 */
void cmd_colorError()
{
	printf("\e[1;36m");
	fprintf(stderr, "\e[1;35m");
}

/*********************** Méthodes de traitement d'arguments ***********************/

/**
 *  @brief
 *  @details Vérification de l'argument en paramètre, afin de voir si c'est bel et bien un nom de fichier terminant par .pgm.
 *  @param const std::string &str
 * 	@param const std::string &suffix
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 */
bool endsWith(const std::string &str, const std::string &suffix)
{
	if (str.empty() || suffix.empty()) // Sécurité pointeurs.
	{
		cmd_colorError();
		fprintf(stderr, "endsWith : arguments null or empty.");
		cmd_colorStandard();
		return false;
	}
	return str.size() >= suffix.size() &&
		   str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/**
 *  @brief
 *  @details
 *  @param char *arg_in[]
 *  @param int size_arg_in
 *  @authors Katia Auxilien
 *  @date 15/05/2024
 */
void convertToLower(char *arg_in[], int size_arg_in)
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

/**
 *  @brief Vérifier si n est un nombre premier.
 *  @details
 *  @param int n
 *  @param int i
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 */
bool isPrime(int n, int i = 2)
{
	if (n <= 2)
		return (n == 2) ? true : false;
	if (n % i == 0)
		return false;
	if (i * i > n)
		return true;

	return isPrime(n, i + 1);
}

/**
 *  @brief
 *  @details Vérification de l'argument en paramètre, afin de voir si c'est bel et bien un nombre et qu'il est premier.
 * 	@param char *arg
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 */
uint8_t check_p_q_arg(char *arg)
{
	if (arg == NULL) // Sécurité pointeurs.
	{
		cmd_colorError();
		fprintf(stderr, "check_p_q_arg : arguments null or empty.");
		cmd_colorStandard();
		return EXIT_FAILURE;
	}

	for (size_t i = 0; i < strlen(arg); i++)
	{
		if (!isdigit(arg[i]))
		{
			cmd_colorError();
			fprintf(stderr, "The argument after the first argument must be an int.\n");
			cmd_colorStandard();
			return EXIT_FAILURE;
		}
	}
	int p = atoi(arg);
	if (!isPrime(p, 2))
	{
		cmd_colorError();
		fprintf(stderr, "The argument after the first argument must be a prime number.\n");
		cmd_colorStandard();
		return EXIT_FAILURE;
	}

	return p;
}

/**
 *  @brief
 *  @details Vérification
 *  @param char* arg_in[]
 *  @param bool param[]
 *				0	bool isEncryption = false ;
 *				1	bool useKeys = false;
 *				2	bool distributeOnTwo = false;
 *				3	bool recropPixels = false;
 *				4	bool optimisationLSB = false;
 *  @authors Katia Auxilien
 *  @date 15/05/2024 9:00:00
 */
void checkParameters(char *arg_in[], int size_arg, bool param[], char *&c_key_file, char *&c_file, uint64_t &p, uint64_t &q, uint64_t &n, uint64_t &lambda, uint64_t &g)
{
	// if (arg_in == NULL || param == NULL) // Sécurité pointeurs.
	// {
	// 	cmd_colorError();
	// 	fprintf(stderr, "checkParameters : arguments null.");
	// 	cmd_colorStandard();
	// 	exit(EXIT_FAILURE);
	// }

	/********** Initialisation de param[] à false. *************/
	for (int i = 0; i < 5; i++)
	{
		param[i] = false;
	}

	/**************** First param ******************/
	if (!strcmp(arg_in[1], "e") || !strcmp(arg_in[1], "enc") || !strcmp(arg_in[1], "encrypt") || !strcmp(arg_in[1], "encryption"))
	{
		param[0] = true;
	}
	else if (!strcmp(arg_in[1], "d") || !strcmp(arg_in[1], "dec") || !strcmp(arg_in[1], "decrypt") || !strcmp(arg_in[1], "decryption"))
	{
		param[0] = false;
		param[1] = true;
	}
	else
	{
		cmd_colorError();
		fprintf(stderr, "The first argument must be e, enc, encrypt, encryption or d, dec, decrypt, decryption (the case don't matter)\n");
		cmd_colorStandard();
		exit(EXIT_FAILURE);
	}
	/**************** ... param ******************/

	bool isFilePGM = false;
	bool isFileBIN = false;

	int i = 2;
	if (param[0] == true && (strcmp(arg_in[i], "-k") && strcmp(arg_in[i], "-key")))
	{
		p = check_p_q_arg(arg_in[2]);
		if (p == 1)
		{
			exit(EXIT_FAILURE);
		}
		q = check_p_q_arg(arg_in[3]);
		if (q == 1)
		{
			exit(EXIT_FAILURE);
		}

		n = p * q;
		Paillier<uint64_t, uint64_t> paillier;
		uint64_t pgc_pq = paillier.gcd_64t(p * q, (p - 1) * (q - 1));

		if (pgc_pq != 1)
		{
			cmd_colorError();
			printf("pgcd(p * q, (p - 1) * (q - 1))= %" PRIu64 "\n", pgc_pq);
			fprintf(stderr, "p & q arguments must have a gcd = 1. Please retry with others p and q.\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
		lambda = paillier.lcm_64t(p - 1, q - 1);
		vector<uint64_t> set = paillier.calc_set_same_remainder_divide_euclide_64t(n * n);
		g = paillier.choose_g_in_vec_64t(set, n, lambda);
		if (g == 0)
		{
			cmd_colorError();
			printf("pgcd(p * q, (p - 1) * (q - 1))= %" PRIu64 "\n", pgc_pq);
			fprintf(stderr, "ERROR with g.\n");
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}

		i = 4;
		isFileBIN = true;
	}

	for (i; i < size_arg; i++)
	{
		printf("%d %s\n", i, arg_in[i]);

		// TODO : Gérer les cas où il y a deux fois -k ou -? ... dans la ligne de commande. pour éviter les erreurs.

		if ((!isFileBIN && !strcmp(arg_in[i], "-k")) || !strcmp(arg_in[i], "-key") || (param[1] == true && endsWith(arg_in[i], ".bin")))
		{ // TODO : 2 cas où on veut check si il y a un argument .bin après le -k OU après le premier argument d

			if (!strcmp(arg_in[i], "-k") || !strcmp(arg_in[i], "-key"))
			{
				c_key_file = arg_in[i + 1];
				param[1] = true;
				i++;
			}
			if (param[1] == true)
			{
				c_key_file = arg_in[i];
			}
			/****************** Check .bin file **************************/
			string s_key_file = c_key_file;
			ifstream file(c_key_file);
			if (!file || !endsWith(s_key_file, ".bin"))
			{
				cmd_colorError();
				fprintf(stderr, "The argument after -k or dec must be an existing .bin file.\n");
				cmd_colorStandard();
				exit(EXIT_FAILURE);
			}
			printf("BIN FILE !\n");
			isFileBIN = true;
		}
		else if (!strcmp(arg_in[i], "-d") || !strcmp(arg_in[i], "-distr") || !strcmp(arg_in[i], "-distribution"))
		{
			param[2] = true;
		}
		else if (!strcmp(arg_in[i], "-hexp") || !strcmp(arg_in[i], "-histogramexpansion"))
		{
			printf("ouici%d\n", i);

			param[3] = true;
		}
		else if (!strcmp(arg_in[i], "-olsbr") || !strcmp(arg_in[i], "-optlsbr"))
		{
			param[4] = true;
		}
		else if (endsWith(arg_in[i], ".pgm") && !isFilePGM)
		{
			c_file = arg_in[i];
			string s_file = c_file;
			ifstream file(c_file);
			if (!file)
			{
				cmd_colorError();
				fprintf(stderr, "The arguments must have an existing .pgm file.\n");
				cmd_colorStandard();
				exit(EXIT_FAILURE);
			}
			isFilePGM = true;
		}
	}

	if (!isFilePGM)
	{
		cmd_colorError();
		fprintf(stderr, "The arguments must have a .pgm file.\n");
		cmd_colorStandard();
		exit(EXIT_FAILURE);
	}
	if (param[1] == true && !isFileBIN)
	{
		cmd_colorError();
		fprintf(stderr, "The argument after -k or dec must be a .bin file.\n");
		cmd_colorStandard();
		exit(EXIT_FAILURE);
	}
}

/*********************** Chiffrement/Déchiffrement ***********************/
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
		// uint8_t *ImgOutEnc;
		T_in *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, OCTET, nH * (2 * nW));
		uint64_t x = 0, y = 1;
		for (int i = 0; i < nTaille; i++)
		{
			T_in pixel;
			// uint8_t pixel;
			if (recropPixels)
			{
				pixel = (ImgIn[i] * n) / 256;
			}
			else
			{
				pixel = ImgIn[i];
			}

			T_out pixel_enc = paillier.paillierEncryption(n, g, pixel);
			T_in pixel_enc_dec_x = pixel_enc / n;
			T_in pixel_enc_dec_y = pixel_enc % n;
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
		T_out *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, T_out, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			T_in pixel;
			// uint8_t pixel;
			if (recropPixels)
			{

				pixel = (ImgIn[i] * n) / 256;
			}
			else
			{
				pixel = ImgIn[i];
			}

			T_out pixel_enc = paillier.paillierEncryption(n, g, pixel);

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
		T_in *ImgIn;

		allocation_tableau(ImgIn, T_in, nTaille);
		n = img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille); // TODO : Retirer and_get_maxgrey
		allocation_tableau(ImgOutDec, OCTET, nH * (nW / 2));

		int x = 0, y = 1;
		for (int i = 0; i < nH * (nW / 2); i++)
		{
			T_out pixel;
			T_in pixel_enc_dec_x = ImgIn[x];
			T_in pixel_enc_dec_y = ImgIn[y];
			pixel = (pixel_enc_dec_x * n) + pixel_enc_dec_y;
			x = x + 2;
			y = y + 2;
			T_in c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		img_pgm.ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW / 2);
		free(ImgIn);
		free(ImgOutDec);
	}
	else
	{
		T_out *ImgIn;
		allocation_tableau(ImgIn, T_out, nTaille);
		n = img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutDec, OCTET, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			T_out pixel = ImgIn[i];
			T_in c = paillier.paillierDecryption(n, lambda, mu, pixel);
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
	checkParameters(argv, argc, parameters, c_key_file, c_file, p, q, n, lambda, g);

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

		printf("Pub Key G = %" PRIu64 "\n", g);
		printf("Pub Key N = %" PRIu64 "\n", n);
		printf("Priv Key lambda = %" PRIu64 "\n", lambda);
		printf("p = %" PRIu64 "\n", p);
		printf("q = %" PRIu64 "\n", q);

		paillier.generatePrivateKey_64t(lambda, mu, p, q, n, g);
		pk = PaillierPrivateKey(lambda, mu, n);
		pubk = PaillierPublicKey(n, g);

		FILE *f_private_key = NULL;

		f_private_key = fopen("Paillier_private_key.bin", "w+b");

		if (f_private_key == NULL)
		{
			fprintf(stderr, "Error ! Opening Paillier_private_key.bin\n");
			return 1;
		}

		fwrite(&pk, sizeof(PaillierPrivateKey), 1, f_private_key);

		fclose(f_private_key);

		FILE *f_public_key = NULL;
		f_public_key = fopen("Paillier_public_key.bin", "w+b");

		if (f_public_key == NULL)
		{
			fprintf(stderr, "Error ! Opening Paillier_public_key.bin\n");
			return 1;
		}
		fwrite(&pubk, sizeof(PaillierPublicKey), 1, f_public_key);

		fclose(f_public_key);

		printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
		printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
		printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
		printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
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
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				return 1;
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
				fprintf(stderr, "Error ! Opening %s \n", c_key_file);
				return 1;
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
		printf("Pub Key G = %" PRIu64 "\n", pubk.getG());
		printf("Pub Key N = %" PRIu64 "\n", pubk.getN());
		printf("Priv Key lambda = %" PRIu64 "\n", pk.getLambda());
		printf("Priv Key mu = %" PRIu64 "\n", pk.getMu());
		if (n <= 256)
		{
			Paillier<uint8_t, uint16_t> paillier;
			encrypt(s_file, pubk, distributeOnTwo, recropPixels, paillier);
		}
		else if (n > 256 && n <= 65535)
		{

			Paillier<uint16_t, uint32_t> paillier;
			encrypt(s_file, pubk, distributeOnTwo, recropPixels, paillier);
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
			Paillier<uint8_t, uint16_t> paillier;
			decrypt(s_file, pk, distributeOnTwo,paillier);
		}
		else if (n > 256 && n <= 65535)
		{
			Paillier<uint16_t, uint32_t> paillier;
			decrypt(s_file, pk, distributeOnTwo,paillier);
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