#ifndef PAILLIER_PUBLIC_KEY
#define PAILLIER_PUBLIC_KEY

class PaillierPublicKey
{
public:
    PaillierPublicKey();
    PaillierPublicKey(uint8_t n, int g);
    uint8_t getN();
    int getG();
    ~PaillierPublicKey();

private:
    uint8_t n;
    int g;
};
PaillierPublicKey::PaillierPublicKey()
{
    n = g = 0;
}

PaillierPublicKey::PaillierPublicKey(uint8_t N, int G)
{
    n = N;
    g = G;
}

uint8_t PaillierPublicKey::getN()
{
    return n;
}

int PaillierPublicKey::getG()
{
    return g;
}

PaillierPublicKey::~PaillierPublicKey() {}

#endif // PAILLIER_PUBLIC_KEY
