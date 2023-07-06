#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    FILE* myfile; 

    //pass your path in the function
    int ch=chdir("/Users/tfai/Documents/GitHub/Filter");
    /*if the change of directory was successful it will print successful otherwise it will print not successful*/
    if(ch<0)
    printf("chdir change of directory not successful\n");
    else
    printf("chdir change of directory successful");

    myfile = fopen("data/eeg_small.csv", "r"); 
    if ( myfile == NULL ) { 
        printf("Cannot open TEXT file\n");
        return 1; 
    }

    // double aa;
    // while (1 == fscanf(myfile, "%lf", &aa)) {
    //     printf("%lf\n", aa);
    // }

    char line[256];
    while (fgets(line, sizeof(line), myfile) != NULL) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            double aa;
            sscanf(token, "%lf", &aa);
            printf("%lf\n", aa);
            token = strtok(NULL, ",");
        }
    }

    fclose(myfile);

    

    return 0;
}