#include <stdlib.h>
#include <stdio.h>

struct list_node {
    unsigned value : 4;
    struct list_node *next;
};

struct linked_list {
    size_t size;
    struct list_node *head;
};

void free_linked_list(struct linked_list *list) {
    if (!list) {
        return;
    }
    struct list_node *node = list->head;
    while (node) {
        struct list_node *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(list);
}

struct linked_list *int_to_linked_list(int number) {
    if (number < 0) {
        return NULL;
    }
    struct linked_list *list = malloc(sizeof(*list));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    struct list_node **last_node = &list->head;
    while (number || !list->size) {
        struct list_node *current_node = malloc(sizeof(*list));
        if (!current_node) {
            free_linked_list(list);
            return NULL;
        }
        current_node->next = NULL;
        current_node->value = number % 10;
        number /= 10;
        *last_node = current_node;
        last_node = &current_node->next;
        ++list->size;
    }
    return list;
}

void print_linked_list(struct linked_list *list) {
    if (!list || !list->head) {
        return;
    }
    struct list_node *node = list->head;
    while (node) {
        printf("%u", node->value);
        node = node->next;
    }
}

void print_number_recursive(struct list_node *node) {
    if (node->next) {
        print_number_recursive(node->next);
    }
    printf("%u", node->value);
}

void print_number_rec(struct linked_list *list) {
    if (!list || !list->head) {
        return;
    }
    print_number_recursive(list->head);
}

void print_number_iter(struct linked_list *list) {
    if (!list || !list->head) {
        return;
    }
    

    unsigned int digits[list->size];
    struct list_node *current_node = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        digits[i] = current_node->value;
        current_node = current_node->next;
    }
    
    for (size_t i = list->size; i > 0; --i) { //umgekehrter Reihenfolge
        printf("%u", digits[i - 1]);
    }
}

int main() {
    struct linked_list *list1 = int_to_linked_list(10);
    print_linked_list(list1);  //10
    printf("\n");
    print_number_rec(list1);   //01
    printf("\n");
    print_number_iter(list1);  //10
    free_linked_list(list1);
    printf("\n");

    struct linked_list *list2 = int_to_linked_list(504);
    printf("\n");
    print_linked_list(list2);  //504
    printf("\n");
    print_number_rec(list2);   //405
    printf("\n");
    print_number_iter(list2);  //504
    free_linked_list(list2);

    
    return EXIT_SUCCESS;
}