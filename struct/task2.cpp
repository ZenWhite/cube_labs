#include <math.h>
#include <complex>
#include <fstream>
#include <iostream>

using namespace std;

int SLAU(complex<float> **matrica_a, int n,
         complex<float> *massiv_b, complex<float> *x)
{
    int i, j, k, r;
    complex<float> c, M, s;
    float max;
    complex<float> **a, *b;
    a = new complex<float> *[n];
    for (i = 0; i < n; i++)
        a[i] = new complex<float>[n];
    b = new complex<float>[n];
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i][j] = matrica_a[i][j];
    for (i = 0; i < n; i++)
        b[i] = massiv_b[i];
    for (k = 0; k < n; k++)
    {
        max = abs(a[k][k]);
        r = k;
        for (i = k + 1; i < n; i++)
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                r = i;
            }
        for (j = 0; j < n; j++)
        {
            c = a[k][j];
            a[k][j] = a[r][j];
            a[r][j] = c;
        }
        c = b[k];
        b[k] = b[r];
        b[r] = c;
        for (i = k + 1; i < n; i++)
        {
            for (M = a[i][k] / a[k][k], j = k; j < n; j++)
                a[i][j] -= M * a[k][j];
            b[i] -= M * b[k];
        }
    }
    if (abs(a[n - 1][n - 1]) == 0)
        if (abs(b[n - 1]) == 0)
            return -1;
        else
            return -2;
    else
    {
        for (i = n - 1; i >= 0; i--)
        {
            for (s = 0, j = i + 1; j < n; j++)
                s += a[i][j] * x[j];
            x[i] = (b[i] - s) / a[i][i];
        }
        return 0;
    }
    for (i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    delete[] b;
}

int INVERSE(complex<float> **a, int n,
            complex<float> **y)
{
    int i, j, res;
    complex<float> *b, *x;
    b = new complex<float>[n];
    x = new complex<float>[n];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            if (j == i)
                b[j] = 1;
            else
                b[j] = 0;
        res = SLAU(a, n, b, x);
        if (res != 0)
            break;
        else
            for (j = 0; j < n; j++)
                y[j][i] = x[j];
    }
    delete[] x;
    delete[] b;
    if (res != 0)
        return -1;
    else
        return 0;
}

int main()
{
    setlocale(LC_ALL, "");
    int i, j, p, N;
    complex<float> initial(-2, 3.5);
    complex<float> **A, **B, **AB, **AA, **C, **CC, **X;
    ifstream fA, fB;
    ofstream g;
    fA.open("a.txt");
    fB.open("b.txt");
    fA >> N;
    cout << "N=" << N << endl;

    A = new complex<float> *[N];
    for (i = 0; i < N; A[i] = new complex<float>[N], i++)
        ;

    B = new complex<float> *[N];
    for (i = 0; i < N; B[i] = new complex<float>[N], i++)
        ;

    AB = new complex<float> *[N];
    for (i = 0; i < N; AB[i] = new complex<float>[N], i++)
        ;

    AA = new complex<float> *[N];
    for (i = 0; i < N; AA[i] = new complex<float>[N], i++)
        ;

    C = new complex<float> *[N];
    for (i = 0; i < N; C[i] = new complex<float>[N], i++)
        ;

    CC = new complex<float> *[N];
    for (i = 0; i < N; CC[i] = new complex<float>[N], i++)
        ;

    X = new complex<float> *[N];
    for (i = 0; i < N; i++)
        X[i] = new complex<float>[N];

    for (i = 0; i < N; i++)
        for (j = 0; j < N; fA >> A[i][j], j++)
            ;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; fB >> B[i][j], j++)
            ;

    cout << endl
         << "Matrix A" << endl;
    for (i = 0; i < N; cout << endl, i++)
        for (j = 0; j < N; cout << A[i][j] << "     ", j++)
            ;

    cout << endl
         << "Matrix B" << endl;
    for (i = 0; i < N; cout << endl, i++)
        for (j = 0; j < N; cout << B[i][j] << "     ", j++)
            ;

    cout << endl
         << "A - B^T:" << endl;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            AB[i][j] = A[i][j] - B[j][i];

    for (i = 0; i < N; cout << endl, i++)
        for (j = 0; j < N; cout << AB[i][j] << "     ", j++)
            ;

    cout << endl
         << "(A - B^T)^2:" << endl;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (int p = 0; p < N; p++)
                AA[i][j] += AB[i][p] * AB[p][j];

    for (i = 0; i < N; cout << endl, i++)
        for (j = 0; j < N; cout << AA[i][j] << "     ", j++)
            ;

    cout << endl
         << "C:" << endl;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            C[i][j] = AA[i][j] * initial;

    for (i = 0; i < N; cout << endl, i++)
        for (j = 0; j < N; cout << C[i][j] << "     ", j++)
            ;

    cout << endl
         << "C^-1:" << endl;

    INVERSE(C, N, X);

    for (i = 0; i < N; cout << endl, i++)
        for (j = 0; j < N; cout << X[i][j] << "     ", j++)
            ;

    fA.close();
    fB.close();

    return 0;
}
