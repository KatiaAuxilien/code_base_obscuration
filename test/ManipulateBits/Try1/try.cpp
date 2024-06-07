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

    // for(int i = 0; i < nbPixel; i++)
    // {
    //     uint16_t val = randomBits();
    //     while(val%32!=0){
    //         val = randomBits();
    //     }
    //     ImgInEnc[i] = val;
    //     test[i] = val;
    //     std::cout << "["<< i <<"] : " << ImgInEnc[i] << "\n";
    // }

	int bits_used = 11;
	int bits_to_take = 5;

	int j = 0; 
    int i = 1;
	while(i < nbPixel){

        std::cout << "bu : " << bits_used<< "\n";
        std::cout << "bt : " << bits_to_take << "\n";

		uint16_t new_bits;

        if(bits_used == 16){
            new_bits = ImgInEnc[i] ;
        }else{
            new_bits = ImgInEnc[i] >> 16 - bits_to_take ;
        }

        std::cout << "Case j "<< j <<" : " << std::bitset<16>(ImgInEnc[j]) << "\n";
        std::cout << "Case i "<< i <<": " << std::bitset<16>(ImgInEnc[i]) << "\n";

        std::cout << "new i : " << std::bitset<16>(new_bits) << "\n";



		ImgInEnc[j] = ImgInEnc[j] | new_bits;
        std::cout << "Résultat final j "<< j <<"  : " << std::bitset<16>(ImgInEnc[j]) << "\n";

		ImgInEnc[i] = ImgInEnc[i] << bits_to_take;
        std::cout << "Résultat final i "<< i <<" : " << std::bitset<16>(ImgInEnc[i]) << "\n\n";

		if(bits_to_take <= 11){
			j++;
            if(j %3 == 0){
                bits_used = 0;
                bits_to_take = 16; 
            }
            else{
                bits_to_take = (bits_to_take + 5) % 16;
                bits_used = 16 - bits_to_take;
            }
        }else{
            bits_to_take = (bits_to_take + 5) % 16;
            bits_used = 16 - bits_to_take;
        }
        
        

        i++;
	}
    ImgInEnc[nbPixel - 1] = ImgInEnc[nbPixel - 1] << bits_used;


    
    for(int i = 0; i < nbPixel; i++)
    {
        std::cout << "["<< i <<"] : " << std::bitset<16>(ImgInEnc[i]) << "\n";
    }


    // bits_used = 11;
    // bits_to_take = 5;

    // uint16_t ImgOutEnc[nbPixel];
    // j = 0;
    // i = 1;

    // ImgOutEnc[j] = (ImgInEnc[j] >> bits_to_take) << bits_to_take;

    // while(i < nbPixel){
    //     std::cout << "bu : " << bits_used<< "\n";
    //     std::cout << "bt : " << bits_to_take << "\n";

    //     uint16_t new_bits =  (ImgOutEnc[j] << bits_used);

    //     bits_to_take = (bits_to_take + 5) % 16;
    //     bits_used = 16 - bits_to_take;


    //     ImgOutEnc[i] = new_bits | (ImgOutEnc[j] >> 16 - bits_used);


    //     if(bits_to_take <= 11){
    //         j++;
    //         i++;
    //     }

    // }


    // for(int i = 0; i < nbPixel; i++)
    // {
    //     std::cout << "["<< i <<"] : " << std::bitset<16>(ImgOutEnc[i]) << "\n";
    // }

    // for(int i = 0; i < nbPixel ; i++){
    //     if(test[i] != ImgOutEnc[i]){
    //         std::cout << "Echec " << i << "\n";
    //     }
    // }


    return 0;
}
