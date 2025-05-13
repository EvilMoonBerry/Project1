//Project 1: Warmup to C and Unix programming


#include <stdio.h>

int main (int argc, char *argv[]) {

    FILE *fptr;

    // Open file for reading
    fptr = fopen(argv[1],"r");

    char filetext[100];

    //Loop through file lines and store it inside filetext and print it to command line
    while (fgets(filetext,100, fptr)){
        printf("%s", filetext);
    }

    // Close the file
    fclose(fptr);

}