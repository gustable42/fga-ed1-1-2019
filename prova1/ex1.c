#include <stdio.h>
#include <stdlib.h>

struct element {
    int number;
    struct element* next;
};

struct element* header = NULL;

struct element* create_new_element(int number);
struct element* create_header();
void free_list(struct element* header);
void insert_element(int number, struct element* header);
int find_i_element_number(int position, struct element* header);
int list_length(struct element* header);

int main() {
    struct element* header = create_header();

    int num = 0;
    while(num >= 0) {
        scanf("%d", &num);
        if(num < 0) break;
        insert_element(num, header);
    }

    int position;

    scanf("%d", &position);
    int number = find_i_element_number(position, header);
    printf("%d\n", number);

    free_list(header);

    return 0;
}

struct element* create_new_element(int number) {
    struct element* element = (struct element*)malloc(sizeof(struct element));
    element->number = number;
    element->next = NULL;
    return element;
}

struct element* create_header() {
    struct element* header = (struct element*)malloc(sizeof(struct element));
    header->next = NULL;
    return header;
}

void free_list(struct element* header) {
    struct element* current_element = header->next;

    while(current_element->next != NULL) {
        struct element* temp = current_element->next;
        free(current_element);
        current_element = temp;
    }
}

void insert_element(int number, struct element* header) {
    struct element* element = create_new_element(number);

    element->next = header->next;
    header->next = element;
}

int find_i_element_number(int position, struct element* header) {
    struct element* temp = header->next;
    int length = list_length(header);

    if(length < position) {
        return -1;
    }

    int i = 1;
    while(header->next != NULL) {
        if(i == position) {
            return temp->number;
        }
        i++;
        temp = temp->next;
    }

    return -1;
}

int list_length(struct element* header) {
    struct element* temp = header->next;
    int i = 1;
    while(temp->next != NULL) {
        i++;
        temp = temp->next;
    }
    return i;
}