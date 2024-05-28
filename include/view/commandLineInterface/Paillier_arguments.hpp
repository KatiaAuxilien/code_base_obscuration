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
bool endsWith(const std::string &str, const std::string &suffix);

/**
 *  @brief
 *  @details
 *  @param char *arg_in[]
 *  @param int size_arg_in
 *  @authors Katia Auxilien
 *  @date 15/05/2024
 */
void convertToLower(char *arg_in[], int size_arg_in);

/**
 *  @brief Vérifier si n est un nombre premier.
 *  @details
 *  @param int n
 *  @param int i
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 */
bool isPrime(int n, int i = 2);

/**
 *  @brief
 *  @details Vérification de l'argument en paramètre, afin de voir si c'est bel et bien un nombre et qu'il est premier.
 * 	@param char *arg
 *  @authors Katia Auxilien
 *  @date 30/04/2024
 */
uint8_t check_p_q_arg(char *arg);

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
void checkParameters(char *arg_in[], int size_arg, bool param[], char *&c_key_file, char *&c_file, uint64_t &p, uint64_t &q, uint64_t &n, uint64_t &lambda);

/**
 *  @brief
 *  @details Vérification pour le programme effectuant des calculs statistiques sur r.
 *  @param char* arg_in[]
 *  @param bool param[]
 *				0	bool useKeys = false;
 *				1	bool distributeOnTwo = false;
 *				2	bool optimisationLSB = false;
 *  @authors Katia Auxilien
 *  @date 27/05/2024 11:52:00
 */
void checkParameters(char *arg_in[], int size_arg, bool param[], char *&c_key_file, uint64_t &p, uint64_t &q, uint64_t &n, uint64_t &lambda);

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
void checkParameters(char *arg_in[], int size_arg, bool param[], uint64_t &p, uint64_t &q, uint64_t &n, uint64_t &lambda);

#endif // PAILLIER_ARGUMENTS