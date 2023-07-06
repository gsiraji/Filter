#include <stdio.h>
#include <stdlib.h>
// #define SIGNAL_LENGTH 30000    // Length of the signal
// #define EPOCH_LENGTH 4*16       // Length of each epoch 
// #define SAMPLING_RATE 500     // Sampling rate of the signal in samples per second

#define SIGNAL_LENGTH 10    // Length of the signal
#define EPOCH_LENGTH 2       // Length of each epoch 
#define SAMPLING_RATE 1     // Sampling rate of the signal in samples per second

double** window(const double* signal, int signalLength, double epochLength, int* numEpochs, int* epochSize);