#include <iostream>
#include <cmath>

using namespace std;

long long mod_pow(long long base, long long exp, long long modulus)
{
    long long result = 1;
    base %= modulus;
    while (exp > 0)
    {
        if (exp & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

long long mod_inv(long long a, long long m)
{
    long long b = m, u = 1, v = 0;
    while (a > 0)
    {
        long long q = b / a;
        long long t = a;
        a = b % a;
        b = t;
        t = u;
        u = v - q * u;
        v = t;
    }
    return (v + m) % m;
}

long long L(long long x, long long n)
{
    return (x - 1) / n;
}

int main()
{
    long long p = 13;
    long long q = 19;
    long long n = p * q;
    long long lambda = 36;
    long long m = 112;
    long long g = 7;
    long long r = 27;

    long long mu = mod_inv(L(mod_pow(g, lambda, n * n), n), n);

    long long c = (mod_pow(g, m, n * n) * mod_pow(r, n, n * n)) % (n * n);

    long long decrypted_m = L(mod_pow(c, lambda, n * n), n) * mu % n;

    cout << "Public key: (n = " << n << ", g = " << g << ")" << endl;
    cout << "Private key: (lambda = " << lambda << ", mu = " << mu << ")" << endl;
    cout << "Ciphertext: c = " << c << endl;
    cout << "Decrypted message: m = " << decrypted_m << endl;

    return 0;
}
