//Project 1: Warmup to C and Unix programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node *create_node(const char *line_content){
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("Failed to allocate node");
        exit(1);
    }

    size_t length = strlen(line_content) + 1;
    new_node->value = malloc(length);
    if (!new_node->value) {
        fprintf(stderr,"error: malloc failed ");
        free(new_node);
        exit(1);
    }
    strcpy(new_node->value, line_content);

    new_node->next = NULL;
    return new_node;
}

// print linked list in reverse 
void printReverse(struct Node* curr) {

    if (curr == NULL)
        return;

    // print the list after start node
    printReverse(curr->next);

    //Check if the string ends with \n; if not add one for the last lines for cleaner printing
    size_t len = strlen(curr->value);
    if (len == 0 || curr->value[len - 1] != '\n') {
        printf("%s\n", curr->value);
    } else {
        printf("%s", curr->value);
    }
}
// writing in file in reverse
void writeinfile(struct Node * curr, char * outputfile) {

    FILE *fptr;
    fptr = fopen(outputfile, "a");
            if (fptr == NULL) {
                fprintf(stderr, "error: cannot open file %s\n", outputfile);
                free(outputfile);
                exit(1);
            }
    
    if (curr == NULL)
        return;

    writeinfile(curr->next, outputfile);

    size_t len = strlen(curr->value);
    if (len == 0 || curr->value[len - 1] != '\n') {
        fprintf(fptr,"%s\n", curr->value);
    } else {
        fprintf(fptr,"%s", curr->value);
    }

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

    //Error if input and output files are the same
    if (argc > 2 && strcmp(argv[1], argv[2]) == 0){
        fprintf(stderr,"error: Input and output file must differ\n", argv[1]);
        exit(1);
    }

    //Opening file from separate user input or from commandline
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
                free(inputfile);
                exit(1);
            }

            // free inputfile
            free(inputfile);
        } else {
            fptr = fopen(argv[1], "r");
            if (fptr == NULL) {
                fprintf(stderr, "error: cannot open file %s\n", argv[1]);
                free(fptr);
                exit(1);
            }
    }

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

    // If only input file was given then print the inputfile for user in reverse order
    if (argc == 1 || argc == 2 ){
        printReverse(start);
    }
    // If input and output file was given then write inputfile text to outputfile in reverse order
    if(argc == 3){
        writeinfile(start, argv[2]);
    }

    return 0;

}