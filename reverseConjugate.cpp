#include <iostream>
#include <complex>

using std::complex;
using std::conj;
using std::endl;

template <typename T>
complex<T>* reverseConjugate(complex<T>* array, int size)
{
    complex<T>* reverse = new complex<T>[size];
    
    /* Reverse array and perform the complex conjugate */
    
    for (int i = 0; i < size; i++)
    {
        reverse[i] = conj(array[size - 1 - i]);
    }
    return reverse;
}


int main()
{

}


// template <typename T, size_t N>
// std::complex<T> reverseConjugate(T (&array)[N])
// {
//     std::complex<T> result[N];

//     for (size_t i = 0; i < N; i++)
//     {
//         size_t reverseIndex = N - 1 - i;
//         result[i] = std::conj(array[reverseIndex]);
//     }

//     return result;
// }