#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convn.c"
#include <limits.h>
#include <unistd.h>

double* readCSV(const char* filename, int* numElements) {
   //pass your path in the function
    int ch=chdir("/Documents/GitHub/Filter/data");
    /*if the change of directory was successful it will print successful otherwise it will print not successful*/
    if(ch<0)
    printf("chdir change of directory not successful\n");
    else
    printf("chdir change of directory successful");
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
    const char* filename1 = "60Hz_notch_FIR_weights.csv";
    const char* filename2 = "sample_EEG_data.csv";
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
        printf("number of rows: %d\n",numRows2);
        printf("number of rows: %d\n",numRows1);
        double *y = convn(array1, array2,numRows1,numRows2,numColumns,&lenY);
        //     for(int i=0;i<lenY;i++) {
        // printf("%lf ",y[i]);
        // }
        printf("number of rows: %d\n",lenY);
        writeToFile("output.csv", y, lenY,numColumns);
        free(y);  // Remember to free the dynamically allocated memory
        }
    
    return 0;
}



