#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    int value;

    struct node* left;
    struct node* right;
} node;

struct node* loadTreeFromFile(char* file);
void showTree(struct node* root);
void isFull(struct node* root);
void searchValue(struct node* root, int search_value);
int getHeight(struct node* root);

struct node* generateRoot();
struct node* generateNode(int value);
void insertNode(int node_value, struct node* *(current_node));
int numberOfNodes(struct node* root);
int heightOfNode(struct node* root, int search_value);
int findValue(struct node* root, struct node* node, int search_value);

//*** MAIN ***//
int main() {
    struct node* root = loadTreeFromFile("BSTs/bst1.txt");
    int search_value;
    scanf("%d", &search_value);
    searchValue(root, search_value);

    return 0;
}

//*** MAIN FUNCTIONS***//

struct node* loadTreeFromFile(char* file) {
    FILE *tree_file;
    tree_file = fopen(file,"r");

    if(!tree_file)
        exit(1);

    struct node* root = generateRoot();

    int value = 0;
    for(; fscanf(tree_file, "%d", &value);) {
        insertNode(value, &root);

        if(feof(tree_file))
            break;
    }
    fclose(tree_file);

    return root;
}

void showTree(struct node* root) {
    
}

void isFull(struct node* root) {
    int number_of_nodes = numberOfNodes(root);
    int max_number_of_nodes = pow(2,getHeight(root)) -1;
    
    if(number_of_nodes == max_number_of_nodes) {
        printf("Árvore é cheia\n");
    }
    else
        printf("Árvore não é cheia\n");
}

void searchValue(struct node* root, int search_value) {
    int value_found = findValue(root, root, search_value);
    if(!value_found)
        printf("Nó com valor procurado não encontrado\n");
}

int getHeight(struct node* root) {
    if(!root)
        return 0;

    struct node* node = root;

    int left_branch = getHeight(node->left);
    int right_branch = getHeight(node->right);

    if(left_branch >= right_branch) return left_branch + 1;
    else return right_branch + 1;
}

// *** AUX FUNCTIONS *** //
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

void insertNode(int node_value, struct node** current_node) {
    if(*current_node == NULL)
        *current_node = generateNode(node_value);
    else if ((*current_node)->value > node_value)
        insertNode(node_value, &(*current_node)->left);
    else
        insertNode(node_value, &(*current_node)->right);
}

int numberOfNodes(struct node* root) {
    int left_branch, right_branch;
    left_branch = right_branch = 0;

    if(root->left == NULL && root->right == NULL)
        return 1;

    if(root->left != NULL)
        left_branch = numberOfNodes(root->left);

    if(root->right != NULL)
        right_branch = numberOfNodes(root->right);

    return left_branch + right_branch + 1;
}

int heightOfNode(struct node* root, int search_value) {
    if(!root)
        return 0;

    if(root->value == search_value)
        return 1;
    
    if(heightOfNode(root->left, search_value) > 0)
        return heightOfNode(root->left, search_value) + 1;

    if(heightOfNode(root->right, search_value) > 0)
        return heightOfNode(root->right, search_value) + 1;
}

int findValue(struct node* root, struct node* node, int search_value) {
    if(!node)
        return 0;
    
    if(root->value == search_value) {
        printf("Nível do nó = 1\n");
        printf("Não possui pai e irmão\n");
        return 1;
    }

    if(node->left != NULL) {
        if(node->left->value == search_value) {
            int height_of_node = heightOfNode(root, search_value);
            printf("Nível do nó: %d\n", height_of_node);
            printf("Valor do pai: %d\n", node->value);
            if(node->right != NULL)
                printf("Possui irmão\n");
            else
                printf("Não possui irmão\n");
            return 1;
        }
    }

    if(node->right != NULL) {
        if(node->right->value == search_value) {
            int height_of_node = heightOfNode(root, search_value);
            printf("Nível do nó: %d\n", height_of_node);
            printf("Valor do pai: %d\n", node->value);
            if(node->left != NULL)
                printf("Possui irmão\n");
            else
                printf("Não possui irmão\n");
            return 1;
        }
    }

    int left_branch, right_branch;
    left_branch = right_branch = 0;
    
    if(node->left != NULL)
        left_branch = findValue(root, node->left, search_value);
    if(node->right != NULL)

    if(left_branch + right_branch > 0)
        return 1;
    else
        return 0;
}