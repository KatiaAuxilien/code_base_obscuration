/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier_arguments.hpp
 *
 * Description : Méthodes de traitement d'arguments 
 * 
 * 
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 21 mai 2024, 16:43:00
 *
 *******************************************************************************/
#ifndef PAILLIER_ARGUMENTS
#define PAILLIER_ARGUMENTS

#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cmath>

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
void checkParameters(char *arg_in[], int size_arg, bool param[], char *&c_key_file, char *&c_file, uint64_t &p, uint64_t &q, uint64_t &n, uint64_t &lambda)
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
			fprintf(stderr, "pgcd(p * q, (p - 1) * (q - 1))= %" PRIu64 "\np & q arguments must have a gcd = 1. Please retry with others p and q.\n",pgc_pq);
			cmd_colorStandard();
			exit(EXIT_FAILURE);
		}
		lambda = paillier.lcm_64t(p - 1, q - 1);


		i = 4;
		isFileBIN = true;
	}

	for (i = i; i < size_arg; i++)
	{
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
			isFileBIN = true;
		}
		else if (!strcmp(arg_in[i], "-d") || !strcmp(arg_in[i], "-distr") || !strcmp(arg_in[i], "-distribution"))
		{
			param[2] = true;
		}
		else if (!strcmp(arg_in[i], "-hexp") || !strcmp(arg_in[i], "-histogramexpansion"))
		{
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


#endif // PAILLIER_ARGUMENTS