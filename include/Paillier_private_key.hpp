#ifndef PAILLIER_PRIVATE_KEY
#define PAILLIER_PRIVATE_KEY

class PaillierPrivateKey
{

public:
    PaillierPrivateKey();
    PaillierPrivateKey(uint8_t l, int m);
    uint8_t getLambda();
    int getMu();
    ~PaillierPrivateKey();

private:
    uint8_t lambda;
    int mu;
};
PaillierPrivateKey::PaillierPrivateKey()
{
    lambda = 0;
    mu = 0;
}

PaillierPrivateKey::PaillierPrivateKey(uint8_t l, int m)
{
    lambda = l;
    mu = m;
}

uint8_t PaillierPrivateKey::getLambda()
{
    return lambda;
}

int PaillierPrivateKey::getMu()
{
    return mu;
}

PaillierPrivateKey::~PaillierPrivateKey() {}

#endif // PAILLIER_PRIVATE_KEY
