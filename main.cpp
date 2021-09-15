#include <bits/stdc++.h>

using namespace std;

class crypt {
public:

    static string translateToBinaryWithoutRevers(long long a) {
        string res;
        while (a != 0) {
            res += (char) (a % 2 + 48);
            if (a % 2) a--;
            a /= 2;
        }
        return res;
    }

    static long long fastPowWithModule(long long a, long long b, long long p) {
        string xs = translateToBinaryWithoutRevers(b);
        long long y = 1, s = a;
        for (char i : xs) {
            if ((long long) (i - 48)) {
                y = y * s % p;
            }
            s = s * s % p;
        }
        return y;
    }

    static long long euclideanAlgorithm(long long a, long long b) {
        long long r;
        while (b != 0) {
            r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    static void generalizedEuclideanAlgorithm(long long a, long long b, long long *s) {
        long long u[3] = {a, 1, 0}, v[3] = {b, 0, 1}, T[3], q;
        while (v[0] != 0) {
            q = u[0] / v[0];
            T[0] = u[0] % v[0];
            T[1] = u[1] - q * v[1];
            T[2] = u[2] - q * v[2];

            for (long long i = 0; i < 3; i++) {
                u[i] = v[i];
                v[i] = T[i];
                s[i] = u[i];
            }
        }
    }

    static long long diffieHellmanAlgorithm(long long p, long long a, long long b) {
        long long q = (p - 1) / 2, g;
        long long mas[10] = {3, 5, 7, 11, 13, 17, 23, 29, 31, 37};
        for (long long i : mas)
            if (fastPowWithModule(i, q, p) == 1) {
                g = mas[1];
                break;
            }
        long long a1 = fastPowWithModule(g, a, p);
        long long b1 = fastPowWithModule(g, b, p);
        cout << fastPowWithModule(b1, a, p) << " = " << fastPowWithModule(a1, b, p) << endl;
        return g;
    }

    static long long babyStepGiantStep(long long a, long long p, long long y) {
        long long m = p / 2 - 1, k = p / 2 + 1, s[m], b[k], i, j;
        for (i = 0; i < m; i++) s[i] = fastPowWithModule(y * pow(a, i), 1, p);
        for (i = 0; i < k; i++) b[i] = fastPowWithModule(pow(a, (i + 1) * m), 1, p);
        for (i = 0; i < k; i++) {
            for (j = 0; j < m; j++) {
                if (s[j] == b[i]) break;
            }
            if (j != m) break;
        }
        return ((i + 1) * m - j);
    }
};

int main() {

    long long s[3];

    cout << crypt::fastPowWithModule(3, 100, 7) << endl;

    //cout<<a.euclideanAlgorithm(28,8);
    crypt::generalizedEuclideanAlgorithm(28, 19, s);
    cout << s[0] << " " << s[1] << " " << s[2] << endl;

    cout << crypt::diffieHellmanAlgorithm(23, 7, 13) << " " << crypt::diffieHellmanAlgorithm(7, 5, 11) << endl;

    cout << crypt::babyStepGiantStep(3, 7, 4);


}