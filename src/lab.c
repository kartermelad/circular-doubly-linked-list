#include <stdio.h>
#include <stdlib.h>
#include "lab.h"

list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)) {
    list_t *mylist = (list_t *)malloc(sizeof(list_t));
    if (mylist == NULL) {
        return NULL;
    }
    mylist->destroy_data = destroy_data;
    mylist->compare_to = compare_to;
    mylist->size = 0;
    mylist->head = (node_t *)malloc(sizeof(node_t));
    if (mylist->head == NULL) {
        free(mylist);
        return NULL;
    }
    mylist->head->data = NULL;
    mylist->head->next = mylist->head;
    mylist->head->prev = mylist->head;
    return mylist;
}

void list_destroy(list_t **list) {
    if (list == NULL || *list == NULL) {
        return;
    }
    node_t *current = (*list)->head->next;
    while (current != (*list)->head) {
        node_t *next = current->next;
        (*list)->destroy_data(current->data);
        free(current);
        current = next;
    }
    free((*list)->head);
    free(*list);
    *list = NULL;
}

list_t *list_add(list_t *list, void *data) {
    if (list == NULL) {
        return NULL;
    }
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = list->head->next;
    newNode->prev = list->head;
    list->head->next->prev = newNode;
    list->head->next = newNode;
    list->size++;
    return list;
}

void *list_remove_index(list_t *list, size_t index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    }
    node_t *current = list->head->next;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    void *data = current->data;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    list->size--;
    return data;
}

int list_indexof(list_t *list, void *data) {
    if (list == NULL) {
        return -1;
    }
    node_t *current = list->head->next;
    size_t index = 0;
    while (current != list->head) {
        if (list->compare_to(current->data, data) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}
