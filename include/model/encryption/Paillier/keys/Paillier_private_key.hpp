#ifndef PAILLIER_PRIVATE_KEY
#define PAILLIER_PRIVATE_KEY

class PaillierPrivateKey
{
    public:
        PaillierPrivateKey();
        PaillierPrivateKey(uint64_t l, uint64_t m);
        PaillierPrivateKey(uint64_t l, uint64_t m, uint64_t n);
        uint64_t getLambda() const;
        uint64_t getMu() const;
        uint64_t getN() const;
        ~PaillierPrivateKey();

    private:
        uint64_t lambda, mu, n;
};

#endif // PAILLIER_PRIVATE_KEY