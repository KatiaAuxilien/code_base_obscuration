/**
 * @file PaillierControllerPGM.hpp
 * @brief Header file for the PaillierControllerPGM class, which is a
 * controller for the Paillier cryptosystem applied to PGM (Portable Gray Map)
 * images.
 * @author Katia Auxilien
 * @date 29 May 2024, 13:55:00
 * @details 
 */

#ifndef PAILLIERCONTROLLER_PGM
#define PAILLIERCONTROLLER_PGM

#include <stdio.h>
#include <cctype>
#include <fstream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <ctype.h> //uintN_t
#include <bitset>  //Bitwise operators

#include "../../include/controller/PaillierController.hpp"
#include "../../include/model/image/image_portable.hpp"
#include "../../include/model/image/image_pgm.hpp"
#include "../../include/model/filesystem/filesystemPGM.hpp"

/**
 * \class PaillierControllerPGM
 * \brief Controller for the Paillier cryptosystem applied to PGM images.
 * \details This class is responsible for controlling the Paillier cryptosystem
 * applied to PGM images. It inherits from the PaillierController class and
 * provides additional functionalities specific to PGM images.
 * \author Katia Auxilien
 * \date 29 May 2024, 13:55:00
 */
class PaillierControllerPGM : public PaillierController
{

private:
	char *c_file; /*!< Pointer to the char array containing the file name. */

public:
	/**
	 * \brief
	 * \brief Default constructor.
	 * \details This constructor initializes the PaillierControllerPGM object with
	 * default values.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	PaillierControllerPGM();

	/**
	 * \brief Destructor.
	 * \details This destructor frees the memory allocated by the PaillierControllerPGM object.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	~PaillierControllerPGM();

	/**
	 * \brief
	 *
	 */
	void init();

	/**
	 * \brief
	 * \brief Getter for the c_file attribute.
	 * \details This method returns the value of the c_file attribute.
	 * \return A constant pointer to the char array containing the file name.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	const char *getCFile() const;

	/**
	 * \brief Setter for the c_file attribute.
	 * \details This method sets the value of the c_file attribute.
	 * \param newCFile A pointer to the char array containing the new file name.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	void setCFile(char *newCFile);

	/**
	 *  \brief Check the parameters passed to the program.
	 *  \details This method checks the parameters passed to the program and sets the
	 * 	corresponding attributes of the PaillierControllerPGM object.
	 * \param arg_in An array of char pointers containing the arguments passed to
	 * the program.
	 *  \param size_arg The size of the arg_in array.
	 *  \param bool param[] array of flags to be set based on the command line
	 * arguments.
	 *				0	bool isEncryption = false ;
	 *				1	bool useKeys = false;
	 *				2	bool distributeOnTwo = false;
	 *				3	bool recropPixels = false;
	 *				4	bool optimisationLSB = false;
	 *  \authors Katia Auxilien
	 *  \date 29 May 2024, 13:55:00
	 */
	void checkParameters(char *arg_in[], int size_arg, bool param[]);

	/**
	 * \brief Print the man page message.
	 * \details This method prints the help message for the program.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	void printHelp();

	/*********************** Encryption/Decryption ***********************/
	/**
	 *  \brief Perform histogram expansion on an image pixel.
	 * \details This method performs histogram expansion on an image pixel to increase
	 * the dynamic range of the image.
	 * \param ImgPixel The input image pixel.
	 * \param recropPixels A bool value indicating whether to recrop the pixels.
	 * \return The histogram-expanded image pixel.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	uint8_t histogramExpansion(OCTET ImgPixel, bool recropPixels);

	/************** 8bits **************/
	/**
	 *  \brief Encrypt an image using the Paillier cryptosystem.
	 * \details This method encrypts an image using the Paillier cryptosystem and
	 * writes the encrypted image to a file.
	 * \tparam T_in The input integer type.
	 * \tparam T_out The output integer type.
	 * \param distributeOnTwo A bool value indicating whether to distribute the
	 * encrypted pixels over two bytes.
	 * \param recropPixels A bool value indicating whether to recrop the pixels.
	 * \param paillier A Paillier object used for encryption.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	template <typename T_in, typename T_out>
	void encrypt(bool distributeOnTwo, bool recropPixels, Paillier<T_in, T_out> paillier);

	/**
	 *  \brief Decrypt an image using the Paillier cryptosystem.
	 * \details This method decrypts an image using the Paillier cryptosystem and
	 * writes the decrypted image to a file.
	 * \tparam T_in The input integer type.
	 * \tparam T_out The output integer type.
	 * \param distributeOnTwo A bool value indicating whether the encrypted pixels
	 * were distributed over two bytes.
	 * \param paillier A Paillier object used for decryption.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	template <typename T_in, typename T_out>
	void decrypt(bool distributeOnTwo, Paillier<T_in, T_out> paillier);

	/**
	 * \brief Encrypt an image using the Paillier cryptosystem with compression.
	 * \details This method encrypts an image using the Paillier cryptosystem with
	 * compression and writes the encrypted image to a file.
	 * \tparam T_in The input integer type.
	 * \tparam T_out The output integer type.
	 * \param recropPixels A bool value indicating whether to recrop the pixels.
	 * \param paillier A Paillier object used for encryption.
	 * \author Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	template <typename T_in, typename T_out>
	void encryptCompression(bool recropPixels, Paillier<T_in, T_out> paillier);

	/**
	 * \brief This function compresses the encrypted bits of an image.
	 * \details The function takes an encrypted image represented as a 2D array of 16-bit
	 * unsigned integers, and its dimensions (number of rows and columns). It compresses
	 * the encrypted bits of the image using a bit-packing technique, where each 16-bit
	 * integer is packed into 11 bits, and returns the compressed image as a new 2D array
	 * of 16-bit unsigned integers. The function also updates the number of columns of the
	 * compressed image to reflect the new size.
	 * \param ImgInEnc A 2D array of 16-bit unsigned integers representing the encrypted image to be compressed.
	 * \param nb_lignes An integer representing the number of rows of the encrypted image.
	 * \param nb_colonnes An integer representing the number of columns of the encrypted image.
	 * \return A 2D array of 16-bit unsigned integers representing the compressed encrypted image.
	 * \authors Katia Auxilien
	 * \date 29 May 2024, 13:55:00
	 */
	uint16_t *compressBits(uint16_t *ImgInEnc, int nb_lignes, int nb_colonnes);

	/**
	 * \brief Method to decompress an encrypted 8-bit PGM image.
	 * \details This method decompresses an encrypted 8-bit PGM image that was
	 * previously compressed using the encryptCompression method.
	 * \param uint16_t *ImgInEnc pointer to the encrypted and compressed image data.
	 * \param int nb_lignes number of rows in the image.
	 * \param int nb_colonnes number of columns in the image.
	 * \return uint16_t* pointer to the decompressed image data.
	 * \author Katia Auxilien
	 * \date 29 mai 2024, 13:55:00
	 */
	uint16_t *decompressBits(uint16_t *ImgInEnc, int nb_lignes, int nb_colonnes, int nTailleOriginale);

	/**
	 * \brief Method to decompose the dimensions of a compressed image.
	 * \details This method decomposes the dimensions of a compressed image into its
	 * height and width components.
	 * \param int n size of the compressed image in pixels.
	 * \return pair<int, int> pair containing the height and width of the decomposed
	 * image.
	 * \author Katia Auxilien
	 * \date 29 mai 2024, 13:55:00
	 */
	pair<int, int> decomposeDimension(int n);

	/**
	 * \brief Method to decrypt an 8-bit PGM image with compression.
	 * \details This method decrypts an 8-bit PGM image that was previously encrypted
	 * using the encryptCompression method and performs decompression on the decrypted
	 * image before writing it to a file.
	 * \tparam T_in input integer type for Paillier cryptosystem.
	 * \tparam T_out output integer type for Paillier cryptosystem.
	 * \param Paillier<T_in, T_out> paillier instance of the Paillier cryptosystem.
	 * \author Katia Auxilien
	 * \date 29 mai 2024, 13:55:00
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
	//  *  \date 29 May 2024, 13:55:00
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
	//  *  \date 29 May 2024, 13:55:00
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
			uint8_t pixel = histogramExpansion(ImgIn[i], recropPixels);

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
			uint8_t pixel = histogramExpansion(ImgIn[i], recropPixels);
			uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);
			ImgOutEnc[i] = pixel_enc;
		}

		image_pgm::ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n * n);

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
void PaillierControllerPGM::encryptCompression(bool recropPixels, Paillier<T_in, T_out> paillier)
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

	int nH, nW, nTaille; // TODO : Change nH nW to uint16_t and nTaille type to uint32_t
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
		uint8_t pixel = histogramExpansion(ImgIn[i], recropPixels);
		uint16_t pixel_enc = paillier.paillierEncryption(n, g, pixel);

		while (pixel_enc % 32 != 0)
		{
			pixel_enc = paillier.paillierEncryption(n, g, pixel);
		}

		ImgOutEnc[i] = pixel_enc;
	}

	uint16_t *ImgOutEncComp = compressBits(ImgOutEnc, nH, nW);
	int nbPixelsComp = ceil((double)(nH * nW * 11) / 16);
	printf("Size : %d\n", nbPixelsComp);

	pair<int, int> dimensionComp = decomposeDimension(nbPixelsComp);
	int nHComp = dimensionComp.first;
	int nWComp = dimensionComp.second;

	image_pgm::write_image_pgm_compressed_variable_size(cNomImgEcriteEnc, ImgOutEncComp, nHComp, nWComp, n * n, nbPixelsComp, nH, nW);

	free(ImgIn);
	free(ImgOutEnc);
	delete[] ImgOutEncComp;
}

template <typename T_in, typename T_out>
void PaillierControllerPGM::decryptCompression(Paillier<T_in, T_out> paillier)
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
	image_pgm::lire_nb_lignes_colonnes_image_p(cNomImgLue, &nHComp, &nWComp);
	nTailleComp = nHComp * nWComp;
	printf("Controller : %d %d\n", nHComp, nWComp);
	uint16_t *ImgInComp;
	allocation_tableau(ImgInComp, uint16_t, nTailleComp);
	pair<int, int> dimesionOriginal = image_pgm::read_image_pgm_compressed_and_get_originalDimension(cNomImgLue, ImgInComp);

	nH = dimesionOriginal.second;
	nW = dimesionOriginal.first;
	nTaille = nH * nW;

	allocation_tableau(ImgOutDec, OCTET, nTaille);

	uint16_t *ImgInEnc = decompressBits(ImgInComp, nH, nW, nTaille);

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