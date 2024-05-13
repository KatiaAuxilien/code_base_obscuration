#ifndef PAILLIER_PRIVATE_KEY
#define PAILLIER_PRIVATE_KEY

class PaillierPrivateKey
{

public:
    PaillierPrivateKey();
    PaillierPrivateKey(int l, int m);
    int getLambda();
    int getMu();
    ~PaillierPrivateKey();

private:
    int lambda;
    int mu;
};
PaillierPrivateKey::PaillierPrivateKey()
{
    lambda = 0;
    mu = 0;
}

PaillierPrivateKey::PaillierPrivateKey(int l, int m)
{
    lambda = l;
    mu = m;
}

int PaillierPrivateKey::getLambda()
{
    return lambda;
}

int PaillierPrivateKey::getMu()
{
    return mu;
}

PaillierPrivateKey::~PaillierPrivateKey() {}

#endif // PAILLIER_PRIVATE_KEY
