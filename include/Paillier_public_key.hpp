#ifndef PAILLIER_PUBLIC_KEY
#define PAILLIER_PUBLIC_KEY

class PaillierPublicKey
{
public:
    PaillierPublicKey();
    PaillierPublicKey(int n, long int g);
    int getN();
    long int getG();
    ~PaillierPublicKey();

private:
    int n;
    long int g;
};
PaillierPublicKey::PaillierPublicKey()
{
    n = g = 0;
}

PaillierPublicKey::PaillierPublicKey(int N, long int G)
{
    n = N;
    g = G;
}

int PaillierPublicKey::getN()
{
    return n;
}

long int PaillierPublicKey::getG()
{
    return g;
}

PaillierPublicKey::~PaillierPublicKey() {}

#endif // PAILLIER_PUBLIC_KEY
