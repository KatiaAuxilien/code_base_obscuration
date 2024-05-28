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

#endif // PAILLIER_PRIVATE_KEY