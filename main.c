#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convn.c"
#include <limits.h>
#include <unistd.h>
#include "window.c"

double* readCSV(const char* filename, int* numElements) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file: %s\n", filename);
        return NULL;
    }

    // Skip the first line
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the first line\n");
        fclose(file);
        return NULL;
    }


    // Count the number of elements in the file
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ",");
        while (token != NULL) {
            count++;
            token = strtok(NULL, ",");
        }
    }

    // Allocate memory for the array
    double* array = (double*)malloc(count * sizeof(double));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Read the file again and populate the array
    rewind(file);
    fgets(line, sizeof(line), file);  // Skip the first line again
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ",");
        while (token != NULL) {
            array[i++] = atof(token);
            token = strtok(NULL, ",");
        }
    }
    printf("read file\n");

    *numElements = count;
    fclose(file);
    return array;
}

void writeToFile(const char* filename, const double* array, int lenY, int numCols) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot open file: %s\n", filename);
        return;
    }

    // for (int i = 0; i < numElements; i++) {
    //     fprintf(file, "%lf\n", array[i]);
    // }

    for (int i = 0; i < lenY; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if(j<numCols-1){
            fprintf(file,"%lf, ", array[i + j * lenY]);
            }
            else{
                fprintf(file,"%lf\n", array[i + j * lenY]);
            }
        }
        printf("\n");
    }

    fclose(file);
}


int main() {
    // const char* filename1 = "weights_small.csv";
    // const char* filename2 = "eeg_small.csv";
    const char* filename1 = "data/60Hz_notch_FIR_weights.csv";
    const char* filename2 = "data/sample_EEG_data.csv";
    int numRows1;
    double* array1 = readCSV(filename1, &numRows1);
    // for(int i=0;i<numRows1;i++) {
    //     printf("%lf, ",array1[i]);
    //     }
    int numColumns = 16;
    int numRows2;
    int numElements2;
    double* array2 = readCSV(filename2, &numElements2);
    int lenY;
    numRows2 = numElements2/numColumns;
    // for(int i=0;i<numElements2;i++) {
    //     printf("%lf, ",array2[i]);
    //     }
    if (array1 != NULL) {
    int epochSize = 4*500;
    int numEpochs = numRows2/epochSize;
        // Allocate memory for the result array
    int resultLength = numEpochs * (epochSize+numRows1-1)*numColumns;
    double* result = (double*)malloc(resultLength * sizeof(double));
    
    double* channel = (double*)malloc(numRows2 * sizeof(double));;
    for (int col = 0; col < numColumns; col++)
    {
        int el1 = 0;
        for (int el = col; el < numElements2; el+=numColumns) 
        {
            channel[el1] = array2[el];
            
            el1++;
        }
        printf("%d, ",el1);
        // Perform convolution on each epoch
    
        double* channel_result = convn(array1, channel, numRows1,epochSize,numEpochs,&lenY);
    
        // Copy the channel_result to the result array
        int resultIndex = col * lenY*numEpochs;
        printf("%d, ",col * lenY*numEpochs);
        for (int i = 0; i < lenY*numEpochs; i++) {
            result[resultIndex + i] = channel_result[i];
        }
            // Free the memory allocated for the result
        free(channel_result);
    }
    writeToFile("output2.csv", result, lenY*numEpochs,numColumns);
    }
    return 0;
}