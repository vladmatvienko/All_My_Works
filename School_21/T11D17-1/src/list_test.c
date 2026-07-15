#include "list.h"
#define SUCCESS 0
#define FAIL 1
#include <stdio.h>

int test_add_door() {
    struct door d1 = {1, 0};
    struct door d2 = {2, 1};

    struct node* root = init(&d1);
    if (!root) return FAIL;

    const struct node* added = add_door(root, &d2);
    if (!added || added->data->id != 2 || added->data->status != 1) {
        destroy(root);
        return FAIL;
    }

    destroy(root);
    return SUCCESS;
}

int test_remove_door() {
    struct door d1 = {1, 0};
    struct door d2 = {2, 1};

    struct node* root = init(&d1);
    if (!root) return FAIL;

    add_door(root, &d2);

    root = remove_door(root->next, root);
    if (find_door(2, root)) {
        destroy(root);
        return FAIL;
    }

    destroy(root);
    return SUCCESS;
}

int main() {
    if (test_add_door() == SUCCESS) {
        printf("SUCCESS add_door\n");
    } else {
        printf("FAIL add_door\n");
    }

    if (test_remove_door() == SUCCESS) {
        printf("SUCCESS remove_door\n");
    } else {
        printf("FAIL remove_door\n");
    }

    return 0;
}
