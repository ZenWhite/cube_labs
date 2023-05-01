#include <iostream>
#include <cmath>

using namespace std;

struct Complex
{
    double re, im;
};

Complex pow(Complex z, int n)
{
    Complex result = {1, 0};

    for (int i = 1; i <= n; i++)
    {
        Complex temp = result;
        result.re = temp.re * z.re - temp.im * z.im;
        result.im = temp.re * z.im + temp.im * z.re;
    }

    return result;
}

Complex operator*(Complex z1, Complex z2)
{
    Complex result = {0, 0};

    result.re = z1.re * z2.re - z1.im * z2.im;
    result.im = z1.re * z2.im + z1.im * z2.re;

    return result;
}

Complex operator+(Complex z1, Complex z2)
{
    Complex result = {0, 0};

    result.re = z1.re + z2.re;
    result.im = z1.im + z2.im;

    return result;
}

Complex operator-(Complex z1, Complex z2)
{
    Complex result = {0, 0};

    result.re = z1.re - z2.re;
    result.im = z1.im - z2.im;

    return result;
}

Complex operator/(Complex z1, Complex z2)
{
    Complex result = {0, 0};

    double denominator = pow(z2.re, 2) + pow(z2.im, 2);

    result.re = (z1.re * z2.re + z1.im * z2.im) / denominator;
    result.im = (z1.im * z2.re - z1.re * z2.im) / denominator;

    return result;
}

void print(Complex z)
{
    if (z.im < 0)
        cout << z.re << "-i" << abs(z.im) << endl;
    else
        cout << z.re << "+i" << z.im << endl;
}

int main()
{
    Complex a, b, c;

    cout << "Введите значение комплексного числа a: ";
    cin >> a.re >> a.im;

    cout << "Введите значение комплексного числа b: ";
    cin >> b.re >> b.im;

    cout << "Введите значение комплексного числа c: ";
    cin >> c.re >> c.im;

    Complex numerator = pow(a, 3) * b + c;
    Complex denominator = a - b;

    Complex result = numerator / denominator;

    print(result);

    return 0;
}