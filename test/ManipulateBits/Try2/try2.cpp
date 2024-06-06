#include <ctype.h>
#include <bitset>
#include <random>
#include <iostream>

/**
 * @brief 
 * 
 * @return uint16_t 
 */
uint16_t randomBits(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint16_t> dis(0, 65535);
    return dis(gen);
}

int main(int argc, char const *argv[])
{
    int nbPixel = 5*3;

    uint16_t ImgInEnc[nbPixel]
    { 65088,9696, 49632, 21888, 52544,56608,39776,54432,736,35648, 61152, 11424, 22912, 39456, 2080 };
    uint16_t test[nbPixel];


    for(int i = 0; i < nbPixel; i++)
    {
        std::cout << "["<< i <<"] : " << std::bitset<16>(ImgInEnc[i]) << "\n";
    }


    // int bits = sizeof(ImgInEnc) * 8;
    

    std::bitset<165> finalSet;
    int j = 0;
    std::bitset<11> tempSet = ImgInEnc[j];
    for (int i = 0; i < 165; i++) {
    //     finalSet[165-i] = tempSet[16 - (i % 11)];
    //     if (i % 11 == 10) 
    //     { // vérifier si le bit actuel est le dernier des 11 bits
    //         j++;
    //          tempSet = ImgInEnc[j];
    //     }
    }


    for (int i = 0; i < 165; i++) {
        std::cout << finalSet[i];
        if ((i + 1) % 11 == 0) { // afficher un saut de ligne tous les 11 bits
            std::cout << std::endl;
        }
    }





    return 0;
}
