#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;

    struct node* left;
    struct node* right;
} node;

struct node* loadTreeFromFile(char* file);

struct node* generateRoot();
struct node* generateNode(int value);
int insertNode(int node_value, struct node* current_node);

int main() {
    loadTreeFromFile("BSTs/bst1.txt");

    return 0;
}

struct node* loadTreeFromFile(char* file) {
    FILE *tree_file;
    tree_file = fopen(file,"r");
    
    node* root = generateRoot();

    if(!tree_file)
        exit(1);

    int value = 0;
    for(; fscanf(tree_file, "%d", &value);) {
        if(!insertNode(value, root)) {
            printf("Problema ao criar a árvore no valor %d", value);
            break;
        }
        if(feof(tree_file))
            break;
    }
    printf("\n");
    fclose(tree_file);
}

// **************** //

struct node* generateRoot() {
    struct node* root = NULL;
    return root;
}

struct node* generateNode(int value) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

int insertNode(int node_value, struct node* current_node) {
    if(current_node == NULL){
        current_node = generateNode(node_value);
        printf("%d ",current_node->value);
        return 1;
    }
    if(node_value > current_node->value) {
        if(current_node->right == NULL) {
            current_node->right = generateNode(node_value);
            printf("%d ",current_node->right->value);
            return 1;
        } else {
            insertNode(node_value, current_node->right);
        }
    }
    if(node_value < current_node->value) {
        if(current_node->left == NULL) {
            current_node->left = generateNode(node_value);
            printf("%d ",current_node->left->value);
            return 1;
        } else {
            insertNode(node_value, current_node->left);
        }
    }
    return 0;
}