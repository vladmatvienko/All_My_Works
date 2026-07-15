#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct node* init(const struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return NULL;

    new_node->data = (struct door*)malloc(sizeof(struct door));
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }

    *(new_node->data) = *door;
    new_node->next = NULL;
    return new_node;
}

struct node* add_door(struct node* elem, const struct door* door) {
    if (!elem) return NULL;

    struct node* new_node = init(door);
    if (!new_node) return NULL;

    new_node->next = elem->next;
    elem->next = new_node;
    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current) {
        if (current->data->id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Удаление элемента из списка
struct node* remove_door(struct node* elem, struct node* root) {
    if (!root || !elem) return NULL;

    struct node* current = root;

    if (current == elem) {
        root = elem->next;
        free(elem->data);
        free(elem);
        return root;
    }

    while (current->next && current->next != elem) {
        current = current->next;
    }

    if (current->next) {
        current->next = elem->next;
        free(elem->data);
        free(elem);
    }

    return root;
}

// Освобождение памяти, занимаемой списком
void destroy(struct node* root) {
    struct node* current = root;
    while (current) {
        struct node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}
