#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

using namespace std;

class crypt {
public:

    static unsigned long long fastPowWithModule(unsigned long long a, unsigned long long x, unsigned long long p) {
        string xs = translateToBinaryWithoutRevers(x);
        unsigned long long y = 1, s = a;
        for (char i : xs) {
            if ((unsigned long long) (i - 48)) {
                y = y * s % p;
            }
            s = s * s % p;
        }
        return y;
    }

    static unsigned long long euclideanAlgorithm(unsigned long long a, unsigned long long b) {
        unsigned long long r;
        while (b != 0) {
            r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    static void generalizedEuclideanAlgorithm(unsigned long long a, unsigned long long b, unsigned long long *s) {
        unsigned long long u[3] = {a, 1, 0}, v[3] = {b, 0, 1}, T[3], q;
        while (v[0] != 0) {
            q = u[0] / v[0];
            T[0] = u[0] % v[0];
            T[1] = u[1] - q * v[1];
            T[2] = u[2] - q * v[2];

            for (unsigned long long i = 0; i < 3; i++) {
                u[i] = v[i];
                v[i] = T[i];
                s[i] = u[i];
            }
        }
    }

    static unsigned long long diffieHellmanAlgorithm(unsigned long long secretKeyA, unsigned long long secretKeyB) {
        unsigned long long bottomRange = 100000000, topRange = 500000000;

        unsigned long long q = randBigPrime(bottomRange, topRange);
        unsigned long long p = 2 * q + 1;

        unsigned long long g;
        while (true) {
            std::random_device rd;
            std::mt19937 mt(rd());
            mt.seed(time(nullptr));
            std::uniform_int_distribution<unsigned long long> dist;
            g = dist(mt) % (p - 1);
            if (g < p && fastPowWithModule(g, q, p) != 1)
                break;
        }
        cout << "q = " << q << endl << "p = " << p << endl << "g = " << g << endl;

        unsigned long long openKeyA = fastPowWithModule(g, secretKeyA, p);
        unsigned long long openKeyB = fastPowWithModule(g, secretKeyB, p);

        unsigned long long linkNumberAB = fastPowWithModule(openKeyB, secretKeyA, p);
        unsigned long long linkNumberBA = fastPowWithModule(openKeyA, secretKeyB, p);

        if (linkNumberAB == linkNumberBA) {
            cout << linkNumberAB << " = " << linkNumberBA;
            cout << endl << "connected" << endl << endl;
        } else {
            cout << endl << "connection failed" << endl << endl;
        }
    }

    static unsigned long long babyStepGiantStep(unsigned long long a, unsigned long long y) {
        long long int bottomRange = 100000000, topRange = 500000000;
        long long int p = 7;
        long long int m = (int) sqrt(p) + 1;
        long long int k = (int) sqrt(p) + 1;
        unsigned long long s[m], i, j;

        for (i = 0; i < m; i++) s[i] = fastPowWithModule(y * pow(a, i), 1, p);
        for (i = 0; i < k; i++) {
            for (j = 0; j < m; j++) {
                if (s[j] == fastPowWithModule(pow(a, (i + 1) * m), 1, p)) {
                    break;
                }
            }
            if (j != m) {
                break;
            }
        }
        cout << "p = " << p << endl;
        cout << "check = " << fastPowWithModule(2,((i + 1) * m - j),p) << endl;
        return ((i + 1) * m - j);
    }

    static string translateToBinaryWithoutRevers(unsigned long long a) {
        string res;
        while (a != 0) {
            res += (char) (a % 2 + 48);
            if (a % 2) a--;
            a /= 2;
        }
        return res;
    }

    static unsigned long long randBigPrime(unsigned long long lower, unsigned long long upper) {
        std::random_device rd;
        std::mt19937 mt(rd());
        mt.seed(time(nullptr));
        std::uniform_int_distribution<unsigned long long> dist(lower, upper);
        while (true) {
            unsigned long long p = 1 | dist(mt);
            if (isPrime(p)) return p;
        }
    }

    static unsigned long long isPrime(unsigned long long n) {

        if ((n & 1) == 0) return n == 2;
        if (n % 3 == 0) return n == 3;
        if (n < 25) return n > 1;
        unsigned long long p = 5;
        while (p * p <= n) {
            if (n % p == 0) return 0;
            p += 2;
            if (n % p == 0) return 0;
            p += 4;
        }
        return 1;
    }
};

int main() {

    unsigned long long s[3];

    cout << crypt::fastPowWithModule(3, 100, 7) << endl;

    //cout<<a.euclideanAlgorithm(28,8);
    crypt::generalizedEuclideanAlgorithm(28, 19, s);
    cout << s[0] << " " << s[1] << " " << s[2] << endl;
    cout << crypt::diffieHellmanAlgorithm(2, 7) << " " << crypt::diffieHellmanAlgorithm(7, 5) << endl;
    cout << crypt::babyStepGiantStep(3, 4);

}