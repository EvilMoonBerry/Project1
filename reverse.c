//Project 1: Warmup to C and Unix programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//https://www.geeksforgeeks.org/c/linked-list-in-c/ How linked list works
typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node *create_node(const char *line_content){
    Node *new_node = malloc(sizeof(Node)); //
    if (!new_node) {
        perror("Failed to allocate node");
        exit(1);
    }

//https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/ How to allocate memory dynamicly
    size_t length = strlen(line_content) + 1;
    new_node->value = malloc(length);
    if (new_node->value==NULL) {
        fprintf(stderr,"error: malloc failed ");
        free(new_node);
        exit(1);
    }
    strcpy(new_node->value, line_content);

    new_node->next = NULL;
    return new_node;
}

// https://www.geeksforgeeks.org/dsa/print-reverse-of-a-linked-list-without-actually-reversing/ print linked list in reverse (Used in both printReverse() and Writeinfile())
void printReverse(struct Node* curr) {

    if (curr == NULL)
        return;

    //print the list after start node
    printReverse(curr->next);

    //Check if the string ends with \n; if not add one for the last lines for cleaner printing
    size_t len = strlen(curr->value);
    if (len == 0 || curr->value[len - 1] != '\n') {
        printf("%s\n", curr->value);
    } else {
        printf("%s", curr->value);
    }
}

void writeinfile(struct Node*curr, FILE *fptr){
    if (curr == NULL)
        return;

    writeinfile(curr->next, fptr);
    
    //Go through the linked list and write lines to the file.
    size_t len = strlen(curr->value);
    //The two final lines are added together so to prevent that \n is added
    if (len == 0 || curr->value[len - 1] != '\n') {
        fprintf(fptr,"%s\n", curr->value);
    } else {
        fprintf(fptr,"%s", curr->value);
    }
}

// writing in file in reverse
void writeinfilestart(struct Node * curr, char * outputfile) {

    //Try to  open the outputfile for writing
    // https://stackoverflow.com/questions/16427664/trying-not-to-overwrite-a-file-in-c To prevent creation of a new file
    FILE *fptr;
    fptr = fopen(outputfile, "r+");
        if (fptr == NULL) {
            fprintf(stderr, "error: cannot open file %s\n", outputfile);
            exit(1);
        }

    if (curr == NULL)
        return;
    //
    writeinfile(curr, fptr);

    fclose(fptr);
}

int main (int argc, char *argv[]) {

    FILE *fptr;
    char *inputfile = NULL;
    size_t input_len = 0;
    char *part =NULL;
    size_t len =0;
    ssize_t line;

    Node *start = NULL;
    Node *end = NULL;

    //Error if more than 2 files are given
    if(argc >3){
        fprintf(stderr,"usage: reverse <input> <output>\n");
        exit(1);
    }

    //Error if input and output files are the same
    if (argc > 2 && strcmp(argv[1], argv[2]) == 0){
        fprintf(stderr,"error: Input and output file must differ\n");
        exit(1);
    }

    //Opening file from separate user input or from commandline
    //https://www.w3schools.com/c/c_files_read.php  How to read files
    if (argc == 1) {
        ssize_t chars_read = getline(&inputfile, &input_len, stdin);
            if (chars_read == -1) {
                fprintf(stderr, "Failed to read filename\n");
                exit(1);
            }

            // Remove new line from user input for correct file name
            inputfile[strcspn(inputfile, "\n")] = '\0';

            //Open file, if the file cannot be open give error message
            fptr = fopen(inputfile, "r");
            if (fptr == NULL) {
                fprintf(stderr, "error: cannot open file %s\n", inputfile);
                exit(1);
            }

            free(inputfile);
        //Open file from command line, if the file cannot be open give error message
        } else {
            fptr = fopen(argv[1], "r");
            if (fptr == NULL) {
                fprintf(stderr, "error: cannot open file %s\n", argv[1]);
                exit(1);
            }
    }

    //https://www.geeksforgeeks.org/c/linked-list-in-c/ How linked list works
    //Loop through file lines and store it to linked list
    while ((line = getline(&part, &len, fptr)) != -1){
        Node *new_node =  create_node (part);
        if (!start){
            start = end = new_node;
        } else {
            end->next = new_node;
            end = new_node;
        }
    }
    
    fclose(fptr);

    free(part);

    // If only inputfile was given then print the inputfile for user in reverse order
    if (argc == 1 || argc == 2 ){
        printReverse(start);
    }
    // If input and outputfile was given then write inputfile text to outputfile in reverse order
    if(argc == 3){
        writeinfilestart(start, argv[2]);
    }
    

    return 0;

}