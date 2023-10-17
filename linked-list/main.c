#include <stdio.h>
#include <stdlib.h>

#define TOTAL_NODES 16

typedef struct node {
    unsigned char location_is_available;
    int data;
    struct node *next;
} Node;

Node list_reserved_memory[TOTAL_NODES];
Node *currentPointer;
Node *previousPointer;

Node *get_node(void);
void add_node_no_DMA(Node **start, int value);
void insert_node_no_DMA(Node **start, int insert_after_value, int value);
void delete_node_no_DMA(Node **start, int value);
void free_list_no_DMA(Node *node);

void add_node(Node **start, int value);
void insert_node(Node **start, int insert_after_value, int value);
void delete_node(Node **start, int value);
void print_list(Node *node);
void free_list(Node *node);

int main(int argc, char *argv[]) {
    /* establish the linked list search pointer */
    currentPointer = &list_reserved_memory[0];

    /* initialize all list locations */
    for (int i = 0; i < TOTAL_NODES; i++) {
        currentPointer->location_is_available = 1;
        currentPointer->data = 0;
        currentPointer->next = NULL;
        currentPointer++;
    }

    /* create first node "head" */
    Node *head = NULL;

    add_node_no_DMA(&head, 5);
    add_node_no_DMA(&head, 128);
    add_node_no_DMA(&head, 41);
    print_list(head);

    /* insert non-exist node, linked list would not have changed */
    insert_node_no_DMA(&head, 77, 92);
    /* insert after node of data 128 */
    insert_node_no_DMA(&head, 128, 84);
    /* insert after the last node */
    insert_node_no_DMA(&head, 41, 97);
    print_list(head);

    /* delete the first node */
    delete_node_no_DMA(&head, 5);
    /* delete the node of data 41 */
    delete_node_no_DMA(&head, 41);
    /* delete the last node */
    delete_node_no_DMA(&head, 97);
    print_list(head);
    free_list_no_DMA(head);
    return 0;

    add_node(&head, 5);
    add_node(&head, 128);
    add_node(&head, 41);

    // insert non-exist node, linked list would not have changed
    insert_node(&head, 77, 92);
    // insert after node of data 128
    insert_node(&head, 128, 84);
    // insert after the last node
    insert_node(&head, 41, 97);

    // delete the first node
    delete_node(&head, 5);
    // delete the node of data 41
    delete_node(&head, 41);
    // delete the last node
    delete_node(&head, 97);

    print_list(head);
    free_list(head);

    return 0;
}

Node *get_node(void) {
    currentPointer = &list_reserved_memory[0];

    for (int i = 0; i < TOTAL_NODES; i++) {
        if (currentPointer->location_is_available == 1) {
            currentPointer->location_is_available = 0;
            return currentPointer;
        }
        currentPointer++;
    }
}

void add_node_no_DMA(Node **start, int value) {
    Node *new_node = get_node();
    new_node->data = value;
    new_node->next = NULL;

    if (*start == NULL) {
        *start = new_node;
        return;
    } else {
        Node *current;
        current = *start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        return;
    }
}

void insert_node_no_DMA(Node **start, int insert_after_value, int value) {
    Node *current = *start;

    while (current != NULL) {
        if (insert_after_value == current->data) {
            Node *new_node = get_node();
            new_node->data = value;
            new_node->next = NULL;
            if (current->next == NULL) {
                current->next = new_node;
                break;
            } else {
                new_node->next = current->next;
                current->next = new_node;
                break;
            }
        }
        current = current->next;
    }
}

void delete_node_no_DMA(Node **start, int value) {
    Node *current = *start;
    Node *temp;

    if (value == current->data) {
        *start = current->next;
        current->location_is_available = 1;
        return;
    }

    while (current != NULL) {
        if (current->next->data == value) {
            temp = current->next;
            current->next = current->next->next;
            temp->location_is_available = 1;
            return;
        }
        current = current->next;
    }
}

void free_list_no_DMA(Node *node) {
    Node *current, *temp;
    current = node;
    while (current != NULL) {
        temp = current;
        current = current->next;
        temp->location_is_available = 1;
    }
}

void add_node(Node **start, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    if (*start == NULL) {
        *start = new_node;
        return;
    } else {
        Node *current;
        current = *start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        return;
    }
}

void insert_node(Node **start, int insert_after_value, int value) {
    Node *current = *start;

    while (current != NULL) {
        if (insert_after_value == current->data) {
            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->data = value;
            new_node->next = NULL;
            if (current->next == NULL) {
                current->next = new_node;
                break;
            } else {
                new_node->next = current->next;
                current->next = new_node;
                break;
            }
        }
        current = current->next;
    }
}

void delete_node(Node **start, int value) {
    Node *current = *start;
    Node *temp;

    if (value == current->data) {
        *start = current->next;
        free(current);
        return;
    }

    while (current != NULL) {
        if (current->next->data == value) {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

void print_list(Node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void free_list(Node *node) {
    Node *current, *temp;
    current = node;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}