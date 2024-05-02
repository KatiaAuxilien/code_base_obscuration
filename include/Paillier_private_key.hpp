#ifndef PAILLIER_PRIVATE_KEY
#define PAILLIER_PRIVATE_KEY

class PaillierPrivateKey
{

    public:
    PaillierPrivateKey();
    PaillierPrivateKey(uint64_t l,uint64_t m);
    uint64_t getLambda();
    uint64_t getMu();
    ~PaillierPrivateKey();

    private:
    uint64_t lambda, mu;


};
PaillierPrivateKey::PaillierPrivateKey(){
    lambda = mu = 0;
}

PaillierPrivateKey::PaillierPrivateKey(uint64_t l,uint64_t m){
    lambda = l;
    mu = m;
}

uint64_t PaillierPrivateKey::getLambda(){
    return lambda;
}

uint64_t PaillierPrivateKey::getMu(){
    return mu;
}

PaillierPrivateKey::~PaillierPrivateKey(){}

#endif //PAILLIER_PRIVATE_KEY
