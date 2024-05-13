#ifndef PAILLIER_PUBLIC_KEY
#define PAILLIER_PUBLIC_KEY

class PaillierPublicKey
{
public:
    PaillierPublicKey();
    PaillierPublicKey(uint64_t n, uint64_t g);
    uint64_t getN();
    uint64_t getG();
    ~PaillierPublicKey();

private:
    uint64_t n, g;
};
PaillierPublicKey::PaillierPublicKey()
{
    n = g = 0;
}

PaillierPublicKey::PaillierPublicKey(uint64_t N, uint64_t G)
{
    n = N;
    g = G;
}

uint64_t PaillierPublicKey::getN()
{
    return n;
}

uint64_t PaillierPublicKey::getG()
{
    return g;
}

PaillierPublicKey::~PaillierPublicKey() {}

#endif // PAILLIER_PUBLIC_KEY
