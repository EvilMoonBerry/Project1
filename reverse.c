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

int main (int argc, char *argv[]) {

    // Open file for reading
    FILE *fptr = fopen(argv[1],"r");
    if (fptr ==NULL){
        exit(1);
    }

    char *value =NULL;
    size_t len =0;
    ssize_t line;

    Node *start = NULL;
    Node *end = NULL;

    //Loop through file lines and store it to linked list
    while ((line = getline(&value, &len, fptr)) != -1){
        Node *new_node =  create_node (value);
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

    free(value);

    // printing the linked list
    Node *printed_line = start;
    while (printed_line){
        printf("%s", printed_line->value);
        printed_line = printed_line->next;
    }

    return 0;

}