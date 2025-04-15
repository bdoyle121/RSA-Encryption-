// Brian Doyle 
// April 15th 2024

#include<iostream>
#include<cassert>
using namespace std;

int EuclidAlgGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int ExterdedEuclidAlgGCD (int a, int b, int &s, int &t) {
    if (b == 0) {
        s = 1;
        t = 0;
        return a;
    }

    int s1, t1;
    int d = ExterdedEuclidAlgGCD(b, a % b, s1, t1);
    s = t1;
    t = s1 - (a / b) * t1;
    return d;
}

int mod(int a, int n) {
    int r = a % n;
    return (r < 0) ? r + n : r;
}

int RelativePrime(int n) {
    for (int i = 2; i < n -1; i++) {
        if(EuclidAlgGCD(i, n) == 1) return i;
    }
    return 2;
}

int inverse(int a, int n) {
    int s, t;
    int d = ExterdedEuclidAlgGCD(n, a, s, t);
    if (d == 1) return mod(t, n);
    cout << "a and n are not relatively prime!" << endl;
    return -1;
}

int Encode(int M, int e, int PQ) {
    int result = 1;
    M = M % PQ;
    while (e > 0) {
        if (e % 2 == 1){
            result = (result * M) % PQ;
        }
        e = e >> 1;
        M = (M * M) % PQ;
    }
    return result;
}

int Decode(int C, int d, int PQ) {
    return Encode(C, d, PQ);
}

bool IsPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() 
{
    const int P = 3;
    const int Q = 7;
    int PQ = P * Q;
    int phi = (P - 1) * (Q - 1);

    int e = RelativePrime(phi);
    int d = inverse(e, phi);

    int M;
    cout << "Enter an integer less than" << PQ << ": ";
    cin >> M;

    int C = Encode(M, e, PQ);
    int M1 = Decode(C, d, PQ);

    cout << "Original:" << M << ", Encrypted " << C << ", Decrypted: " << M1 << endl;

    assert(M == M1);
    return 0;
}
