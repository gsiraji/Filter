#include "window.h"

double** window(const double* signal, int signalLength, double epochLength, int* numEpochs, int* epochSize) 
{
    *epochSize = epochLength * SAMPLING_RATE;  // Number of samples in each epoch

    // Calculate the number of epochs
    *numEpochs = signalLength / (*epochSize);

    // Allocate memory for the epochs
    double** epochs = (double**)malloc(*numEpochs * sizeof(double*));
    for (int i = 0; i < *numEpochs; i++) {
        epochs[i] = (double*)malloc((*epochSize) * sizeof(double));
    }

    // Extract the epochs
    for (int i = 0; i < *numEpochs; i++) {
        // Extract the current epoch
        for (int j = 0; j < *epochSize; j++) {
            int index = i * (*epochSize) + j;
            epochs[i][j] = signal[index];
        }
    }

    return epochs;
}

// int main() {
//     double signal[SIGNAL_LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     int numEpochs, epochSize;

//     double** epochs = window(signal, SIGNAL_LENGTH, EPOCH_LENGTH, &numEpochs, &epochSize);

//     // Perform convolution on each epoch
//     for (int i = 0; i < numEpochs; i++) {
//         double* result = epochs[i];
//         printf("Output:\n");
//         for (int j = 0; j < EPOCH_LENGTH; j++)
//         {
//             printf("%.2f ", result[j]);
//             printf("\n");
//         }

//         // // Free the memory allocated for the result
//         // free(result);
//     }

//     return 0;
// }