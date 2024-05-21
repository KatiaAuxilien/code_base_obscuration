#ifndef PAILLIER_PRIVATE_KEY
#define PAILLIER_PRIVATE_KEY

class PaillierPrivateKey
{
    public:
        PaillierPrivateKey();
        PaillierPrivateKey(uint64_t l, uint64_t m);
        PaillierPrivateKey(uint64_t l, uint64_t m, uint64_t n);
        uint64_t getLambda();
        uint64_t getMu();
        uint64_t getN();
        ~PaillierPrivateKey();

    private:
        uint64_t lambda, mu, n;
};

PaillierPrivateKey::PaillierPrivateKey()
{
    lambda = mu = 0;
}

PaillierPrivateKey::PaillierPrivateKey(uint64_t l, uint64_t m)
{
    lambda = l;
    mu = m;
}

PaillierPrivateKey::PaillierPrivateKey(uint64_t l, uint64_t m, uint64_t nn)
{
    lambda = l;
    mu = m;
    n = nn;
}

uint64_t PaillierPrivateKey::getLambda()
{
    return lambda;
}

uint64_t PaillierPrivateKey::getMu()
{
    return mu;
}

uint64_t PaillierPrivateKey::getN()
{
    return n;
}

PaillierPrivateKey::~PaillierPrivateKey() {}

#endif // PAILLIER_PRIVATE_KEY
