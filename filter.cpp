#include <iostream>
#include <complex>

using std::complex;
using std::conj;
using std::endl;
using std::cout;

template <typename T>
complex<T>* reverseConjugate(complex<T>* array, int size)
{
    complex<T>* reverse = new complex<T>[size];
    for (int i = 0; i < size; i++)
    {
        reverse[i] = conj(array[size - 1 - i]);
    }
    return reverse;
}

int main()
{
    const int size = 6;
    complex<double> array[size] = {complex<double>(1.0, 2.0),
                                        complex<double>(3.0, 4.0),
                                        complex<double>(-5.0, 6.0),
                                        complex<double>(7.0, -8.0),
                                        complex<double>(9.0, 10.0),
                                        complex<double>(-11.0, -12.0)
                                        };

    cout << "Original Array:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    complex<double>* result = reverseConjugate(array, size);

    cout << "Reversed and Conjugated Array:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;

    delete[] result;

    return 0;
}