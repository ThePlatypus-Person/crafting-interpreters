#ifndef LIST_H
#define LIST_H

typedef struct Node Node;
typedef struct List List;
typedef enum {
    LIST_SUCCESS = 0,
    LIST_ERROR = 1
} ListStatus;

struct Node {
    Node* next;
    Node* prev;
    char* text;
};


struct List {
    Node* first;
    Node* last;
    int length;
};


// return values:
// 0 = Success
// 1 = Fail
List* list_init();
int list_search(List* list, Node* node);

int list_insert_front(List* list, Node* node);
int list_insert_back(List* list, Node* node);
int list_insert_after(List* list, Node* reference, Node* node);
int list_insert_before(List* list, Node* reference, Node* node);

int list_delete(List* list, Node* node);
int list_delete_front(List* list);
int list_delete_back(List* list);

int list_clear(List* list);
int list_print(List* list);

#endif
