#include <ctype.h>
#include <bitset>
#include <random>
#include <iostream>


uint16_t *compressBits(uint16_t *ImgInEnc, int nb_lignes, int nb_colonnes)
{

	int nbPixel = nb_colonnes * nb_lignes;
	if (nbPixel > 132710400)
	{
		printf("Maximum image size is 132 710 400 pixels.\n");
		exit(EXIT_FAILURE);
	}

	// Taille max image 15360*8640l
	// std::bitset<2123366400> finalSet;
	std::bitset<2123366400> *finalSet = new std::bitset<2123366400>;

	int j = 0;
	std::bitset<16> tempSet;

	for (int i = 0; i < nbPixel; i++)
	{
		tempSet = ImgInEnc[i];
		for (int k = 15; k >= 4; k--)
		{
			finalSet->set(j, tempSet[k]);
			j++;
		}
		// std::cout << i << ' ' << tempSet << std::endl;
	}

	int size_ImgIn11bits = nbPixel * 12;
	int size_ImgOutEnc16bits = ceil((double)size_ImgIn11bits/16);

	// for (int i = 0; i < size_ImgIn11bits; i++)
	// {
	// 	std::cout << finalSet[i];
	// 	if ((i + 1) % 12 == 0)
	// 	{ // afficher un saut de ligne tous les 12 bits
	// 		std::cout << std::endl;
	// 	}
	// }

	uint16_t * ImgOutEnc16bits = new uint16_t[size_ImgOutEnc16bits];

	int k = 0;
	for (int i = 0; i < size_ImgOutEnc16bits; i++)
	{
		std::bitset<16> SetImgOutEnc16bits;
		for (int l = 0; l < 16; l++)
		{
			SetImgOutEnc16bits.set(l, (*finalSet)[k]);
			k++;
		}

		ImgOutEnc16bits[i] = (uint16_t)SetImgOutEnc16bits.to_ulong();
	}

	return ImgOutEnc16bits;
}

uint16_t *decompressBits(uint16_t *ImgInEnc, int nb_lignes, int nb_colonnes)
{
	// TODO : Trouver une solution pour les valeurs comme 12, 192, 15, etc.

    
	std::bitset<192> setTemp;
	int j = 0;
	for (int i = 0; i < 12; i++)
	{
		std::bitset<16> setImg = ImgInEnc[i];
		for (int k = 0; k < 16; k++)
		{
			setTemp.set(j, setImg[k]);
			j++;
		}
	}

	std::cout << setTemp << std::endl;

	// step 2 : On écrit ce bitset dans le tableau originalImg
	int sizeOriginal = nb_lignes * nb_colonnes * 16;

	uint16_t *originalImg = new uint16_t[sizeOriginal];

	j = 0;
	for (int i = 0; i < sizeOriginal; i++)
	{
		std::bitset<16> setImg;
		for (int k = 15; k >= 5; k--)
		{
			setImg.set(k, setTemp[j]);
			j++;
		}
		originalImg[i] = (uint16_t)setImg.to_ulong();
		std::cout << setImg << std::endl;
	}

	return originalImg;
}

uint16_t randomBits(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint16_t> dis(0, 65535);
    return dis(gen);
}


int main(int argc, char const *argv[])
{
    int nbPixel = 5*3;

    uint16_t ImgInEnc[nbPixel];
    uint16_t test[nbPixel];

    for(int i = 0; i < nbPixel; i++)
    {
        uint16_t val = randomBits();
        while(val%32!=0){
            val = randomBits();
        }
        ImgInEnc[i] = val;
        test[i] = val;
        std::cout << "["<< i <<"] : " << ImgInEnc[i] << "\n";
    }

	int size_ImgIn11bits = nbPixel * 12;
	int size_ImgOutEnc16bits = ceil((double)size_ImgIn11bits/16);
	uint16_t * ImgOutEnc16bits = new uint16_t[size_ImgOutEnc16bits];

    ImgOutEnc16bits = compressBits(ImgInEnc,5,3);

    printf("Bit compressed :");
    for(int i = 0; i < size_ImgOutEnc16bits; i++)
	{
		std::bitset<16> temp = ImgOutEnc16bits[i];
		std::cout << temp;
		std::cout << std::endl;
	}



}