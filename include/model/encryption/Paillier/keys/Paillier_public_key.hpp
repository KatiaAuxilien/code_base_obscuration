#ifndef PAILLIER_PUBLIC_KEY
#define PAILLIER_PUBLIC_KEY

#include <cstdint>

class PaillierPublicKey
{
public:
    PaillierPublicKey();
    PaillierPublicKey(uint64_t n, uint64_t g);
    uint64_t getN() const;
    uint64_t getG() const;
    ~PaillierPublicKey();

private:
    uint64_t n, g;
};
#endif // PAILLIER_PUBLIC_KEY
