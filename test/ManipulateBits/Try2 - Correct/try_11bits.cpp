#include <ctype.h>
#include <bitset>
#include <random>
#include <iostream>

uint16_t randomBits(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint16_t> dis(0, 65535);
    return dis(gen);
}


int main(int argc, char const *argv[])
{
    int nbPixel = 4*5;

    uint16_t ImgInEnc[nbPixel];

    for(int i = 0; i < nbPixel; i++)
    {
        uint16_t val = randomBits();
        while(val%32!=0){
            val = randomBits();
        }
        ImgInEnc[i] = val;
    }

    printf("\nORIGIN :\n");

    for(int i = 0; i < nbPixel; i++)
    {
        std::cout << "["<< i <<"] : " << std::bitset<16>(ImgInEnc[i]) << "\n";
    }

    std::bitset<220> finalSet;
    int j = 0;
    std::bitset<16> tempSet;

    for (int i = 0; i < nbPixel; i++) {
        tempSet = ImgInEnc[i];
        for(int k = 15; k >=  5; k--)
        {
            finalSet.set(j, tempSet[k]);
            j++;
        }
        // std::cout << i << ' '<< tempSet << std::endl;

    }

    // for (int i = 0; i < 220; i++) {
    //     std::cout << finalSet[i];
    //     if ((i + 1) % 11 == 0) { // afficher un saut de ligne tous les 11 bits
    //         std::cout << std::endl;
    //     }
    // }

//16 bits
    int sizeComp = ceil((double)(nbPixel * 11)/16);

    uint16_t ImgOutEnc16bits[sizeComp];

    int k = 0;
    for(int i = 0; i < sizeComp; i++)
    {
        std::bitset<16> SetImgOutEnc16bits; 
        for(int l = 0; l < 16 ; l++)
        {
            SetImgOutEnc16bits.set(l,finalSet[k]);
            k++;
        }

        ImgOutEnc16bits[i] = (uint16_t) SetImgOutEnc16bits.to_ulong();

        std::bitset<16> setTest = ImgOutEnc16bits[i];
        // std::cout << setTest << std::endl;

    }

    printf("\nCOMP : \n");

    
    for(int i = 0; i < sizeComp; i++)
    {
        std::cout << "["<< i <<"] : " << std::bitset<16>(ImgInEnc[i]) << "\n";
    }


    printf("\nRetour arrière \n");

    //---------------------------------------------------------------------------------//
    //----------------------- Retour en arrière --------------------------------------//


    //16 bits

    std::bitset<224> setTemp;
    j = 0;

    
    for(int i = 0; i < sizeComp; i++)
    {
        std::bitset<16> setImg = ImgOutEnc16bits[i];
        for(int k = 0; k < 16 ; k ++)
        {
            setTemp.set(j,setImg[k]); 
            j++;
        }
    }

    // std::cout << setTemp << std::endl;

    //step 2 : On écrit ce bitset dans le tableau originalImg
    uint16_t originalImg[nbPixel];
    j=0;
    for(int i = 0; i < nbPixel ; i ++)
    {
        std::bitset<16> setImg;
        for(int k = 15; k >= 5; k--)
        {
            setImg.set(k,setTemp[j]);
            j++;
        }
        originalImg[i] = (uint16_t) setImg.to_ulong();
        // std::cout << setImg << std::endl;
    }

    printf("\nDECOMP :\n");

    for(int i = 0; i < nbPixel; i++)
    {
        std::cout << "["<< i <<"] : " << std::bitset<16>(originalImg[i]) << "\n";
    }


    int nbSame = 0;
    for(int i = 0 ; i < nbPixel ; i++)
    {
        if(ImgInEnc[i] == originalImg[i])
        {
            // printf("\nLes mêmes [%d] \n", i);
            nbSame++;
        }
    }

    if(nbSame == nbPixel)
    {
        printf("\nLes mêmes \n");
    }else{
        printf("\nno\n");
    }

    return 0;
}
