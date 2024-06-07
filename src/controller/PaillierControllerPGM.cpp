/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : PaillierControllerPGM.cpp
 *
 * Description :
 *
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : 29 Mai 2024, 13:57:00
 *
 *******************************************************************************/
#include "../../include/controller/PaillierControllerPGM.hpp"

PaillierControllerPGM::PaillierControllerPGM()
{
	init();
};
PaillierControllerPGM::~PaillierControllerPGM(){};

void PaillierControllerPGM::init()
{
	this->c_file = NULL;
	this->c_key_file = NULL;
	this->model = PaillierModel::getInstance();
	this->view = commandLineInterface::getInstance();
}

const char *PaillierControllerPGM::getCFile() const
{
	return c_file;
}

void PaillierControllerPGM::setCFile(char *newCFile)
{
	delete[] c_file;
	c_file = new char[strlen(newCFile) + 1];
	strcpy(c_file, newCFile);
}

void PaillierControllerPGM::checkParameters(char *arg_in[], int size_arg, bool param[])
{
	// if (arg_in == NULL || param == NULL) // Sécurité pointeurs.
	// {
	// this->view->getInstance()->error_failure("checkParameters : arguments null.");
	// exit(EXIT_FAILURE);
	// }

	this->convertToLower(arg_in, size_arg);

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
		this->view->getInstance()->error_failure("The first argument must be e, enc, encrypt, encryption or d, dec, decrypt, decryption (the case don't matter)\n");
		exit(EXIT_FAILURE);
	}
	/**************** ... param ******************/

	bool isFilePGM = false;
	bool isFileBIN = false;

	int i = 2;
	if (param[0] == true && (strcmp(arg_in[i], "-k") && strcmp(arg_in[i], "-key")))
	{
		uint64_t p = this->check_p_q_arg(arg_in[2]);
		if (p == 1)
		{
			exit(EXIT_FAILURE);
		}
		this->model->getInstance()->setP(p);

		uint64_t q = this->check_p_q_arg(arg_in[3]);
		if (q == 1)
		{
			exit(EXIT_FAILURE);
		}
		this->model->getInstance()->setQ(q);

		uint64_t n = p * q;
		this->model->getInstance()->setN(n);
		Paillier<uint64_t, uint64_t> tempPaillier;
		this->model->getInstance()->setPaillierGenerationKey(tempPaillier);

		uint64_t pgc_pq = this->model->getInstance()->getPaillierGenerationKey().gcd_64t(p * q, (p - 1) * (q - 1));

		if (pgc_pq != 1)
		{
			string msg = "pgcd(p * q, (p - 1) * (q - 1))= " + to_string(pgc_pq) + "\np & q arguments must have a gcd = 1. Please retry with others p and q.\n";
			this->getView()->error_failure(msg);
			exit(EXIT_FAILURE);
		}
		uint64_t lambda = this->model->getInstance()->getPaillierGenerationKey().lcm_64t(p - 1, q - 1);

		this->model->getInstance()->setLambda(lambda);

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
				this->setCKeyFile(arg_in[i + 1]);
				param[1] = true;
				i++;
			}
			if (param[1] == true)
			{
				this->setCKeyFile(arg_in[i]);
			}
			/****************** Check .bin file **************************/
			string s_key_file = this->getCKeyFile();
			ifstream file(this->getCKeyFile());
			if (!file || !this->endsWith(s_key_file, ".bin"))
			{
				this->view->getInstance()->error_failure("The argument after -k or dec must be an existing .bin file.\n");
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
		else if (this->endsWith(arg_in[i], ".pgm") && !isFilePGM)
		{
			this->setCFile(arg_in[i]);
			string s_file = this->getCFile();
			ifstream file(this->getCFile());
			if (!file)
			{
				this->view->getInstance()->error_failure("The arguments must have an existing .pgm file.\n");
				exit(EXIT_FAILURE);
			}
			isFilePGM = true;
		}
	}

	if (!isFilePGM)
	{
		this->view->getInstance()->error_failure("The arguments must have a .pgm file.\n");
		exit(EXIT_FAILURE);
	}
	if (param[1] == true && !isFileBIN)
	{
		this->view->getInstance()->error_failure("The argument after -k or dec must be a .bin file.\n");
		exit(EXIT_FAILURE);
	}
}

uint8_t PaillierControllerPGM::histogramExpansion(OCTET ImgPixel, bool recropPixels)
{
	uint8_t pixel;
	if (recropPixels)
	{
		uint64_t n = model->getInstance()->getPublicKey().getN();
		pixel = (ImgPixel * n) / 256;
	}
	else
	{
		pixel = ImgPixel;
	}
	return pixel;
}
/*********************** Chiffrement/Déchiffrement ***********************/

uint16_t * PaillierControllerPGM::compressBits(uint16_t * ImgInEnc, int nb_lignes, int nb_colonnes){
	
	int nbPixel = nb_colonnes * nb_lignes;
	if(nbPixel > 132710400)
	{
		this->view->getInstance()->error_failure("Maximum image size is 132 710 400 pixels.\n");
		exit(EXIT_FAILURE);
	}

	//Taille max image 15360*8640l
    std::bitset<2123366400> finalSet;
    int j = 0;
    std::bitset<16> tempSet;

    for (int i = 0; i < nbPixel; i++) {
        tempSet = ImgInEnc[i];
        for(int k = 15; k >=  5; k--)
        {
            finalSet.set(j, tempSet[k]);
            j++;
        }
        std::cout << i << ' '<< tempSet << std::endl;

    }

	int size_ImgIn11bits= nbPixel * 11;

    for (int i = 0; i < size_ImgIn11bits; i++) {
        std::cout << finalSet[i];
        if ((i + 1) % 11 == 0) { // afficher un saut de ligne tous les 11 bits
            std::cout << std::endl;
        }
    }

	uint16_t ImgOutEnc16bits[12];

    int k = 0;
    for(int i = 0; i < 11; i++)
    {
        std::bitset<16> SetImgOutEnc16bits; 
        for(int l = 0; l < 16 ; l++)
        {
            SetImgOutEnc16bits.set(l,finalSet[k]);
            k++;
        }

        ImgOutEnc16bits[i] = (uint16_t) SetImgOutEnc16bits.to_ulong();

        std::bitset<16> setTest = ImgOutEnc16bits[i];
    }

	return ImgOutEnc16bits;
}

uint16_t * PaillierControllerPGM::decompressBits(uint16_t *ImgInEnc, int nb_lignes, int nb_colonnes){
//TODO : Trouver une solution pour les valeurs comme 12, 192, 15, etc.
    std::bitset<192> setTemp;
    int j = 0;
    for(int i = 0; i < 12; i++)
    {
        std::bitset<16> setImg = ImgInEnc[i];
        for(int k = 0; k < 16 ; k ++){
            setTemp.set(j,setImg[k]); 
            j++;
        }
    }

    std::cout << setTemp << std::endl;

    //step 2 : On écrit ce bitset dans le tableau originalImg
    uint16_t originalImg[15];
    j=0;
    for(int i = 0; i < 15 ; i ++)
    {
        std::bitset<16> setImg;
        for(int k = 15; k >= 5; k--)
        {
            setImg.set(k,setTemp[j]);
            j++;
        }
        originalImg[i] = (uint16_t) setImg.to_ulong();
        std::cout << setImg << std::endl;
    }

}


/************** n > 8bits**************/
/*
template <typename T_in, typename T_out>
void encrypt2(bool distributeOnTwo, bool recropPixels, Paillier<T_in, T_out> paillier)
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
	this->img_pgm.lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);

	if (distributeOnTwo)
	{
		uint16_t *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		this->img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
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

		this->img_pgm.ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW * 2, n);

		free(ImgIn);
		free(ImgOutEnc);
	}
	else
	{
		uint32_t *ImgOutEnc;
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		this->img_pgm.lire_image_p(cNomImgLue, ImgIn, nTaille);
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

		this->img_pgm.ecrire_image_pgm_variable_size(cNomImgEcriteEnc, ImgOutEnc, nH, nW, n);

		free(ImgIn);
		free(ImgOutEnc);
		nTaille = nH * nW;
	}
}

template <typename T_in, typename T_out>
void decrypt2(bool distributeOnTwo, Paillier<T_in, T_out> paillier)
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

	OCTET *ImgOutDec;
	this->img_pgm.lire_nb_lignes_colonnes_image_p(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	if (distributeOnTwo)
	{
		uint16_t *ImgIn;

		allocation_tableau(ImgIn, uint16_t, nTaille);
		n = this->img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille); // TODO : Retirer and_get_maxgrey
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
		this->img_pgm.ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW / 2);
		free(ImgIn);
		free(ImgOutDec);
	}
	else
	{
		uint32_t *ImgIn;
		allocation_tableau(ImgIn, uint32_t, nTaille);
		n = this->img_pgm.lire_image_pgm_and_get_maxgrey(cNomImgLue, ImgIn, nTaille);
		allocation_tableau(ImgOutDec, OCTET, nTaille);

		for (int i = 0; i < nTaille; i++)
		{
			uint32_t pixel = ImgIn[i];
			uint16_t c = paillier.paillierDecryption(n, lambda, mu, pixel);
			ImgOutDec[i] = static_cast<OCTET>(c);
		}
		this->img_pgm.ecrire_image_p(cNomImgEcriteDec, ImgOutDec, nH, nW);
		free(ImgIn);
		free(ImgOutDec);
	}
}
*/
