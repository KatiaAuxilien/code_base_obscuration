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

/**
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

void colorStandard()
{
	printf("\e[0;36m");
}

void colorError()
{
	printf("\e[1;36m");
	fprintf(stderr, "\e[1;35m");
}

/*********************** Méthodes de traitement d'arguments ***********************/

int cutCmd(char *cmd, char *cmd_cut[])
{
	if (cmd == NULL || cmd_cut == NULL) // Sécurité pointeurs.
	{
		colorError();
		fprintf(stderr, "cutCmd : arguments null.");
		colorStandard();
		return EXIT_FAILURE;
	}

	int i = 0;
	cmd_cut[i] = strtok(cmd, " ");
	while (cmd_cut[i] != NULL)
	{
		printf("\t %d => '%s'\n", i, cmd_cut[i]);
		i++;
		cmd_cut[i] = strtok(NULL, " "); // strtok garde en mémoire sa dernière position dans cmd_in.
	}
	// strtok ajoute lui même NULL à la fin.
	return i;
}

void convertToLower(char arg_in[][], int size_arg_in)
{
	for (int j = 0; j < size_arg_in; j++)
	{
		for (int i = 0; arg_in[j][i] != '\0'; i++)
		{
			arg_in[j][i] = tolower(arg_in[j][i]);
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
 *  @param string pos
 * 	@param char *arg
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 */
uint8_t check_p_q_arg(string pos, char *arg)
{
	if (pos == NULL || arg == NULL) // Sécurité pointeurs.
	{
		colorError();
		fprintf(stderr, "check_p_q_arg : arguments null.");
		colorStandard();
		return EXIT_FAILURE;
	}

	for (size_t i = 0; i < strlen(arg); i++)
	{
		if (!isdigit(arg[i]))
		{
			colorError();
			fprintf(stderr, "The %s argument must be an int.\n", pos.c_str());
			colorStandard();
			return EXIT_FAILURE;
		}
	}
	int p = atoi(arg);
	if (!isPrime(p, 2))
	{
		colorError();
		fprintf(stderr, "The %s argument must be a prime number.\n", pos.c_str());
		colorStandard();
		return EXIT_FAILURE;
	}

	return p;
}

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
	if (str == NULL || suffix == NULL) // Sécurité pointeurs.
	{
		colorError();
		fprintf(stderr, "endsWith : arguments null.");
		colorStandard();
		return EXIT_FAILURE;
	}
	return str.size() >= suffix.size() &&
		   str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
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
void checkParameters(char *arg_in[], bool param[], char *c_key_file, char *c_file)
{
	if (arg_in == NULL || param == NULL) // Sécurité pointeurs.
	{
		colorError();
		fprintf(stderr, "checkParameters : arguments null.");
		colorStandard();
		return EXIT_FAILURE;
	}

	/********** Initialisation de param[] à false. *************/
	for (int i = 0; i < 5; i++)
	{
		param[i] = false;
	}

	/**************** First param ******************/
	if (!strcmp(arg_in[0], "e") || !strcmp(arg_in[0], "enc") || !strcmp(arg_in[0], "encrypt") || !strcmp(arg_in[0], "encryption"))
	{
		param[0] = true;
	}
	else if (!strcmp(arg_in[0], "d") || !strcmp(arg_in[0], "dec") || !strcmp(arg_in[0], "decrypt") || !strcmp(arg_in[0], "decryption"))
	{
		param[0] = false;
		param[1] = true;
	}
	else
	{
		colorError();
		fprintf(stderr, "The first argument must be e, enc, encrypt, encryption or d, dec, decrypt, decryption (the case don't matter)\n");
		colorStandard();
		return EXIT_FAILURE;
	}
	/**************** ... param ******************/

	bool isFilePGM = false;
	bool isFileBIN = false;

	int i = 1;
	if (param[0] == true)
	{
		// arg_in[1];
		// arg_in[2];
		// i = ;
	}

	for (i; i < strlen(arg_in); i++)
	{
		if (arg_in[i][0] == '-') // TODO : Gérer les cas où il y a deux fois -k ou -? ... dans la ligne de commande. pour éviter les erreurs.
		{
			if (strpbrk(arg_in[i], "-k") != NULL || strpbrk(arg_in[i], "-key") != NULL || (i == 1 && param[1] == true))
			{ // TODO : 2 cas où on veut check si il y a un argument .bin après le -k OU après le premier argument d
				if(strpbrk(arg_in[i], "-k") != NULL || strpbrk(arg_in[i], "-key") != NULL){
					c_key_file = argv[i + 1];
					param[1] = true;
				}
				if((i == 1 && param[1] == true)){
					c_key_file = argv[i];
				}
				/****************** Check .bin file **************************/
				string s_key_file = c_key_file;
				ifstream file(c_key_file);
				if (!file || !endsWith(s_key_file, ".bin"))
				{
					colorError();
					fprintf(stderr, "The argument after -k or dec must be an existing .bin file.\n");
					colorStandard();
					return EXIT_FAILURE;
				}
				i++;
				isFileBIN = true;
			}
			else if (strpbrk(arg_in[i], "-d") != NULL || strpbrk(arg_in[i], "-distr") != NULL || strpbrk(arg_in[i], "-distribution") != NULL)
			{
				param[2] = true;
			}
			else if (strpbrk(arg_in[i], "-hexp") != NULL || strpbrk(arg_in[i], "-histogramexpansion"))
			{
				param[3] = true;
			}
			else if (strpbrk(arg_in[i], "-olsbr") != NULL || strpbrk(arg_in[i], "-optlsbr") != NULL)
			{
				param[4] = true;
			}
			else if ( endsWith(arg_in[i], ".pgm"))
			{
				c_file = arg_in[i];
				string s_file = c_file;
				ifstream file(c_file);
				if (!file)
				{
					colorError();
					fprintf(stderr, "The arguments must have an existing .pgm file.\n");
					colorStandard();
					return EXIT_FAILURE;
				}
				isFilePGM = true;
			}
		}
	}

	if(!isFilePGM){
		colorError();
		fprintf(stderr, "The arguments must have a .pgm file.\n");
		colorStandard();
		return EXIT_FAILURE;
	}
	if(param[1] == true && !isFileBIN){
		colorError();
		fprintf(stderr, "The argument after -k or dec must be a .bin file.\n");
		colorStandard();
		return EXIT_FAILURE;
	}

	/*
	if (tolower(argv[1][1]) == 'k')
		{
			useKeys = true;
		}
		if (tolower(argv[1][1]) == 'r' || argv[1][2] == 'r' || argv[1][3] == 'r')
		{
			recropPixels = true;
		}

	if (tolower(argv[1][1]) == '2' || argv[1][2] == '2' || argv[1][3] == '2')
	{
		distributeOnTwo = true;
	}
	if (tolower(argv[1][1]) == 'l' || argv[1][2] == 'l' ||argv[1][3] == 'l')
	{
		optimisationLSB = true;
	}

	int argImg = 4;
	string englishArgNumb = "fourth";
	char *c_key_file;
	if (useKeys)
	{
		argImg = 3;
		englishArgNumb = "third";

		c_key_file = argv[2];
		string s_key_file = c_key_file;
		ifstream file(c_key_file);
		if (!file || !endsWith(s_key_file, ".bin"))
		{
			cerr << "The second argument must be an existing .bin file." << endl;
			return 1;
		}
	}
	char *c_file = argv[argImg];
	string s_file = c_file;
	ifstream file(c_file);
	if (!file || !endsWith(s_file, ".pgm"))
	{
		cerr << "The " + englishArgNumb + " argument must be an existing .pgm file." << endl;
		return 1;
	}
*/
}
/*********************** Chiffrement/Déchiffrement ***********************/

void encrypt(string s_file, PaillierPublicKey pubk, bool distributeOnTwo, bool recropPixels)
{
	Paillier paillier;
	paillier = Paillier();
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
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutEnc, OCTET, nH * (2 * nW));
		uint64_t x = 0, y = 1;
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

			uint16_t pixel_enc = paillier.paillierEncryption_8t(n, g, pixel);
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

			uint16_t pixel_enc = paillier.paillierEncryption_8t(n, g, pixel);

			ImgOutEnc[i] = pixel_enc;
		}

		img_pgm.ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n);

		free(ImgIn);
		free(ImgOutEnc);
		nTaille = nH * nW;
	}
}

void decrypt(string s_file, PaillierPrivateKey pk, bool distributeOnTwo)
{
	Paillier paillier = Paillier();
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
		n = img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille);
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
			uint8_t c = paillier.paillierDecryption_16t(n, lambda, mu, pixel);
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
			uint8_t c = paillier.paillierDecryption_16t(n, lambda, mu, pixel);
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
	/*
		0	bool isEncryption;
		1	bool useKeys = false;
		2	bool distributeOnTwo = false;
		3	bool recropPixels = false;
		4	bool optimisationLSB = false;
	*/

	char *cmd_line[255];
	int size_cmd_line = cutCmd(argv, cmd_line);

	convertToLower(cmd_line, size_cmd_line);

	/*********************** Traitement de clé ***********************/
	Paillier paillier = Paillier();
	PaillierPrivateKey pk;
	PaillierPublicKey pubk;

	if (!useKeys && isEncryption)
	{
		uint64_t p = check_p_q_arg("second", argv[2]);
		if (p == 1)
		{
			return 1;
		}
		uint64_t q = check_p_q_arg("third", argv[3]);
		if (q == 1)
		{
			return 1;
		}
		uint64_t lambda, n, mu;
		n = p * q;
		uint64_t pgc_pq = paillier.gcd_64t(p * q, (p - 1) * (q - 1));

		if (pgc_pq != 1)
		{
			printf("pgcd(p * q, (p - 1) * (q - 1))= %" PRIu64 "\n", pgc_pq);
			fprintf(stderr, "p & q arguments must have a gcd = 1. Please retry with others p and q.\n");
			return 1;
		}
		vector<uint64_t> set = paillier.calc_set_same_remainder_divide_euclide_64t(n * n);
		uint64_t g = paillier.choose_g_in_vec_64t(set, n, lambda);

		if (g == 0)
		{
			fprintf(stderr, "ERROR with g.\n");
			return 1;
		}

		paillier.generatePrivateKey_64t(lambda, mu, p, q, n, g);
		pk = PaillierPrivateKey(lambda, mu);
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
	/*********************** Chiffrement ***********************/
	if (isEncryption)
	{
		encrypt(s_file, pubk, distributeOnTwo, recropPixels);
	}
	/*********************** Déchiffrement ***********************/
	else
	{
		decrypt(s_file, pk, distributeOnTwo);
	}
}