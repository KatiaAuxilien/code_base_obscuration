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
    int nbPixel = 512*512;

    uint16_t ImgInEnc[nbPixel];

    for(int i = 0; i < nbPixel; i++)
    {
        uint16_t val = randomBits();
        while(val%32!=0){
            val = randomBits();
        }
        ImgInEnc[i] = val;
        // std::cout << "["<< i <<"] : " << std::bitset<16>(ImgInEnc[i]) << "\n";

    }

	int bits_used = 11;
	int bits_to_take = 5;

	int j = 0; 
    int i = 1;
	while(i < nbPixel){

        // std::cout << "bu : " << bits_used<< "\n";
        // std::cout << "bt : " << bits_to_take << "\n";

		uint16_t new_bits;

        if(bits_used == 16){
            new_bits = ImgInEnc[i] ;
        }else{
            new_bits = ImgInEnc[i] >> 16 - bits_to_take ;
        }

        // std::cout << "Case j "<< j <<" : " << std::bitset<16>(ImgInEnc[j]) << "\n";
                // std::cout << "Case i "<< i <<": " << std::bitset<16>(ImgInEnc[i]) << "\n";

        // std::cout << "new i : " << std::bitset<16>(new_bits) << "\n";



		ImgInEnc[j] = ImgInEnc[j] | new_bits;
        // std::cout << "Résultat final j "<< j <<"  : " << std::bitset<16>(ImgInEnc[j]) << "\n";

		ImgInEnc[i] = ImgInEnc[i] << bits_to_take;
        // std::cout << "Résultat final i "<< i <<" : " << std::bitset<16>(ImgInEnc[i]) << "\n\n";

		if(bits_to_take <= 11){
			j++;
            i++;
		}
         bits_to_take = (bits_to_take + 5) % 16;
            bits_used = 16 - bits_to_take;

	}
    // ImgInEnc[nbPixel - 1] = ImgInEnc[nbPixel - 1] << bits_used;


    
    for(int i = 0; i < nbPixel; i++)
    {
        std::cout << "["<< i <<"] : " << std::bitset<16>(ImgInEnc[i]) << "\n";
    }


	int bits_used = 11;
	int bits_to_take = 5;

    uint16_t ImgOutEnc[nbPixel];
	int j = 0; 
    int i = 1;
    while(i < nbPixel)
    {

        ImgOutEnc[i] = ImgInEnc[j] << bits_used;
        ImgOutEnc[j] = 

    }    


    return 0;
}
