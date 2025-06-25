//Project 1: Warmup to C and Unix programming


#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    // Open file for reading
    FILE *fptr = fopen(argv[1],"r");
    if (fptr ==NULL){
        exit(1);
    }

    size_t buffer = 100;
    char *filetext = malloc(buffer);
    size_t len = 0;

    // Allocating memory and exit
    if (filetext == NULL){
        perror("Memory allocation failed");
        fclose(fptr);
        exit(1);
    }

    //Loop through file lines and store it inside filetext and print it to command line
    while (fgets(filetext,100, fptr) !=NULL){
        printf("%s", filetext);
    }
    printf("\n");

    // Close the file
    fclose(fptr);

}