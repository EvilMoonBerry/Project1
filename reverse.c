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

    // Allocate memory 
    size_t length = strlen(line_content) + 1;
    new_node->value = malloc(length);
    if (!new_node->value) {
        perror("Failed to allocate memory");
        free(new_node);
        exit(1);
    }
    strcpy(new_node->value, line_content);

    new_node->next = NULL;
    return new_node;
}

// printing linked list in reverse 
void printReverse(struct Node* curr) {

    // Base case
    if (curr == NULL)
        return;

    // print the list after start node
    printReverse(curr->next);

    // Check if the string ends with \n; if not, add one for correct printing
    size_t len = strlen(curr->value);
    if (len == 0 || curr->value[len - 1] != '\n') {
        printf("%s\n", curr->value);
    } else {
        printf("%s", curr->value);
    }
}
// writing in file in reverse
void writeinfile(struct Node* curr) {

    FILE *fptr = fopen("testfile.txt", "a");

    // Base case
    if (curr == NULL)
        return;

    // print the list after start node
    writeinfile(curr->next);

    // Check if the string ends with \n; if not, add one for correct printing
    size_t len = strlen(curr->value);
    if (len == 0 || curr->value[len - 1] != '\n') {
        fprintf(fptr,"%s\n", curr->value);
        printf("%s\n", curr->value);
    } else {
        fprintf(fptr,"%s", curr->value);
        printf("%s", curr->value);
    }
}

int main (int argc, char *argv[]) {

    // Open file for reading
    FILE *fptr = fopen(argv[1],"r");
    if (fptr ==NULL){
        exit(1);
    }

    char *test =NULL;
    size_t len =0;
    ssize_t line;

    Node *start = NULL;
    Node *end = NULL;

    //Loop through file lines and store it to linked list
    while ((line = getline(&test, &len, fptr)) != -1){
        Node *new_node =  create_node (test);
        if (!start){
            start = end = new_node;
        } else {
            end->next = new_node;
            end = new_node;
        }
    }
    printf("\n");

    // Close the file
    fclose(fptr);

    free(test);

    // printing the linked list
    Node *printed_line = start;
    while (printed_line){
        printf("%s", printed_line->value);
        printed_line = printed_line->next;
    }

    printf("\n");

    printf("\n");

    printReverse(start);

    writeinfile(start);

    return 0;

}