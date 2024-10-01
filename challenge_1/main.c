#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define TRUE 1
#define FALSE 0
#define CHUNK_SIZE_TEXT 256


void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Gets a Dynamically Allocated String
char* get_string()
{
    char* line = NULL;
    char* temp = NULL;
    size_t size = 0;
    size_t index = 0;
    int ch = EOF;

    clear_stdin();
    while (ch) {
        ch = getc(stdin);

        if (ch == EOF || ch == '\n')
            ch = 0;

        if (size <= index) {
            size += CHUNK_SIZE_TEXT;
            temp = realloc(line, size);

            if (!temp) {
                free(line);
                line = NULL;
                break;
            }

            line = temp;
        }

        line[index++] = ch;
    }

    return line;
}


int contains_only_whitespace(char* str) 
{
    if (str == NULL)
        return TRUE;

    while (*str) {
        if (*str != '\n')
            return FALSE;

        str++;
    }

    return TRUE;
}

Node* create_new_node()
{
    printf("Text: ");
    char* input = get_string();

    Node* node = (Node*) malloc(sizeof(Node));
    node->text = input;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

int options_select()
{
    printf("Pick Options:\n");
    printf("0 - Exit\n");
    printf("1 - Add item\n");
    printf("2 - Remove item\n");
    printf("3 - Search item\n");
    printf("4 - Print list\n");
    printf("5 - Clear list\n\n");

    while (TRUE) {
        printf("Pick: ");
        int input;
        scanf("%d", &input);

        if (input >= 0 && input <= 5)
            return input;

        printf("Invalid option, please input again.\n");
    }
}

int options_insert()
{
    printf("Insert Item:\n");
    printf("1 - Insert front\n");
    printf("2 - Insert back\n\n");

    while (TRUE) {
        printf("Pick: ");
        int input;
        scanf("%d", &input);

        if (input >= 1 && input <= 2)
            return input;

        printf("Invalid option, please input again.\n");
    }
}

int options_delete()
{
    printf("Delete Item:\n");
    printf("1 - Delete front\n");
    printf("2 - Delete back\n\n");

    while (TRUE) {
        printf("Pick: ");
        int input;
        scanf("%d", &input);

        if (input >= 1 && input <= 2)
            return input;

        printf("Invalid option, please input again.\n");
    }
}

int main(void) 
{
    List* list = list_init();

    while (TRUE) {
        int options = options_select();

        switch (options) {
            case 0:
                printf("Exiting Program.\n");
                list_print(list);
                return 0;
            case 1:
                int insert_opt = options_insert();
                Node* node = create_new_node();

                switch (insert_opt) {
                    case 1:
                        list_insert_front(list, node);
                        break;
                    case 2:
                        list_insert_back(list, node);
                }

                break;
            case 2:
                int delete_opt = options_delete();
                
                switch (delete_opt) {
                    case 1:
                        list_delete_front(list);
                        break;
                    case 2:
                        list_delete_back(list);
                }

                break;
            case 3:
                printf("Sorry, feature not implemented yet.\n");
                break;
            case 4:
                printf("Printing list.\n");
                list_print(list);
                break;
            case 5:
                printf("Clearing list.\n");
                list_clear(list);
        }
    }

    return 0;
}
