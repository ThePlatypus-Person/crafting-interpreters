#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define DEBUG


List* list_init() {
    List* list = (List*) malloc(sizeof(List));

    if (list == NULL) {
#ifdef DEBUG
        printf("Error: malloc failed.\n");
#endif
        return NULL;
    }

    list->first = NULL;
    list->last = NULL;
    list->length = 0;
#ifdef DEBUG
    printf("Success: list initialized.\n");
#endif

    return list;
}


int list_search(List* list, Node* node) {
    Node* ref = list->first;

    while (ref) {
        if (ref == node) {
#ifdef DEBUG
            printf("Success: node found.\n");
#endif
            return LIST_SUCCESS;
        }

        ref = ref->next;
    }

#ifdef DEBUG
    printf("Error: node not found.\n");
#endif
    return LIST_ERROR;
}

int list_insert_front(List* list, Node* node) {
    if (list->length == 0) {
        list->first = node;
        list->last = node;
        list->length++;

#ifdef DEBUG
    printf("Success: node inserted into the empty list.\n");
#endif

        return LIST_SUCCESS;
    }

    Node* temp = list->first;

    list->first = node;
    node->prev = NULL;
    node->next = temp;
    temp->prev = node;
    list->length++;

#ifdef DEBUG
    printf("Success: node inserted into front of list.\n");
#endif

    return LIST_SUCCESS;
}

int list_insert_back(List* list, Node* node) {
    if (list->length == 0) {
        list->first = node;
        list->last = node;
        list->length++;

#ifdef DEBUG
    printf("Success: node inserted into the empty list.\n");
#endif

        return LIST_SUCCESS;
    }

    Node* temp = list->last;

    list->last = node;
    node->prev = temp;
    node->next = NULL;
    temp->next = node;
    list->length++;
    
#ifdef DEBUG
    printf("Success: node inserted into back of list.\n");
#endif

    return LIST_SUCCESS;
}

int list_insert_after(List* list, Node* reference, Node* node) {
    if ( !list_search(list, reference) ) {
#ifdef DEBUG
    printf("Error: node not found in list.\n");
#endif
        return LIST_ERROR;
    }

    if (list->last == reference)
        return list_insert_back(list, node);

    node->prev = reference;
    node->next = reference->next;
    reference->next = node;
    node->next->prev = node;

    list->length++;

#ifdef DEBUG
    printf("Success: node inserted into list. \n");
#endif

    return LIST_SUCCESS;
}

int list_insert_before(List* list, Node* reference, Node* node) {
    if ( !list_search(list, reference) ) {
#ifdef DEBUG
    printf("Error: node not found in list.\n");
#endif
        return LIST_ERROR;
    }

    // if reference is the first node
    if (list->first == reference)
        return list_insert_front(list, node);

    node->next = reference;
    node->prev = reference->prev;
    reference->prev = node;
    node->prev->next = node;
    list->length++;

    return LIST_SUCCESS;
}


int list_delete(List* list, Node* node) {
    if (list->length == 0) {
#ifdef DEBUG
        printf("Error: list is empty.\n");
#endif
        return LIST_ERROR;
    }

    if ( !list_search(list, node) ) {
#ifdef DEBUG
        printf("Error: node not found in list.\n");
#endif
        return LIST_ERROR;
    }

    if (list->first == node)
        return list_delete_front(list);

    if (list->last == node)
        return list_delete_back(list);

    Node* prev = node->prev;
    Node* next = node->next;
    node->prev = NULL;
    node->next = NULL;

    next->prev = prev;
    prev->next = next;

    list->length--;
    free(node->text);
    free(node);

#ifdef DEBUG
    printf("Success: node successfully removed.\n");
#endif

    return LIST_SUCCESS;
}

int list_delete_front(List* list) {
    if (list->length == 0) {
#ifdef DEBUG
        printf("Error: list is empty.\n");
#endif
        return LIST_ERROR;
    }

    Node* node = list->first;

    // if there's only one node in the list?
    if (list->length == 1) {
        list->first = NULL;
        list->last = NULL;
        node->prev = NULL;
        node->next = NULL;
    } else {
        list->first = node->next;
        node->next->prev = NULL;
        node->next = NULL;
    }

    list->length--;
    free(node->text);
    free(node);

#ifdef DEBUG
        printf("Success: node removed from front of list.\n");
#endif

    return LIST_SUCCESS;
}

int list_delete_back(List* list) {
    if (list->length == 0) {
#ifdef DEBUG
        printf("Error: list is empty.\n");
#endif
        return LIST_ERROR;
}

    Node* node = list->last;

    if (list->length == 1) {
        list->first = NULL;
        list->last = NULL;
        node->prev = NULL;
        node->next = NULL;
    } else {
        list->last = node->prev;
        node->prev->next = NULL;
        node->prev = NULL;
    }

    list->length--;
    free(node->text);
    free(node);

#ifdef DEBUG
        printf("Success: node removed from back of list.\n");
#endif

    return LIST_SUCCESS;
}

int list_print(List* list) {
    if (list->length == 0) {
#ifdef DEBUG
        printf("Error: list is empty.\n");
#endif
        return LIST_ERROR;
    }

    Node* node = list->first;

    for (int i = 1; i <= list->length; i++) {
        printf("Node-%d: %s\n", i, node->text);
        node = node->next;
    }
    printf("\n");

    return LIST_SUCCESS;
}

int list_clear(List* list) {
    while (list->first) 
        list_delete_front(list);

#ifdef DEBUG
    printf("Success: list cleared successfully.\n");
#endif

    return LIST_SUCCESS;
}
