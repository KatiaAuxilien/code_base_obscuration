#include <ctype.h>
#include <bitset>
#include <random>
#include <iostream>


int main(int argc, char const *argv[])
{
    int nbPixel = 5*3;

    uint16_t ImgInEnc[nbPixel] { 65088,9696, 49632, 21888, 52544,56608,39776,54432,736,35648, 61152, 11424, 22912, 39456, 2080 };

    for(int i = 0; i < nbPixel; i++)
    {
        std::cout << "["<< i <<"] : " << std::bitset<16>(ImgInEnc[i]) << "\n";
    }

    std::bitset<165> finalSet;
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

    for (int i = 0; i < 165; i++) {
        std::cout << finalSet[i];
        if ((i + 1) % 11 == 0) { // afficher un saut de ligne tous les 11 bits
            std::cout << std::endl;
        }
    }


//16 bits

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


    //---------------------------------------------------------------------------------//
    //----------------------- Retour en arrière --------------------------------------//


    //16 bits

    //step 1 : On réuni tout sur un bit set de 15*16 en rajoutant 5 zéros
    std::bitset<192> setTemp;
    j = 0;
    for(int i = 0; i < 12; i++)
    {
        std::bitset<16> setImg = ImgOutEnc16bits[i];
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


    return 0;
}


    // uint8_t ImgOutEnc8bits[21];
    // int k = 0;
    // for(int i = 0; i < 21; i++)
    // {
    //     std::bitset<8> setImgOutEnc8bits; 
    //     for(int l = 0; l < 8 ; l++)
    //     {
    //         setImgOutEnc8bits.set(l,finalSet[k]);
    //         k++;
    //     }

    //     ImgOutEnc8bits[i] = (uint8_t) setImgOutEnc8bits.to_ulong();

    //     std::bitset<8> setTest = ImgOutEnc8bits[i];
    //     std::cout << setTest << std::endl;
    // }
