#ifndef PAILLIER_PUBLIC_KEY
#define PAILLIER_PUBLIC_KEY

class PaillierPublicKey
{
public:
    PaillierPublicKey();
    PaillierPublicKey(int n, int g);
    int getN();
    int getG();
    ~PaillierPublicKey();

private:
    int n;
    int g;
};
PaillierPublicKey::PaillierPublicKey()
{
    n = g = 0;
}

PaillierPublicKey::PaillierPublicKey(int N, int G)
{
    n = N;
    g = G;
}

int PaillierPublicKey::getN()
{
    return n;
}

int PaillierPublicKey::getG()
{
    return g;
}

PaillierPublicKey::~PaillierPublicKey() {}

#endif // PAILLIER_PUBLIC_KEY
