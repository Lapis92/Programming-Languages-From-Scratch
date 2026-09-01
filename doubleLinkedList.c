#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    struct node *prev;
    struct node *next;
    char *content;
} node;

typedef struct {
    node *first;
    node *last;
} doubleLinkedList;

void printListForwards(doubleLinkedList* list);

void printListBackwards(doubleLinkedList* list);

void insertAfter(doubleLinkedList* list, node* prevNode, node* newNode);

void insertBefore(doubleLinkedList* list, node* nextNode, node* newNode);

void insertAtStart(doubleLinkedList* list, node* newNode);

void insertAtEnd(doubleLinkedList* list, node* newNode);

void removeNode(doubleLinkedList* list, node* node);

void findNode(doubleLinkedList* list, char* find);
/*function removeNode(contentuct doubleLinkedList list, contentuct node node) {
    
}*/
int main() {
    // Create the DLL and nodes in isolation
    doubleLinkedList l1;
    node n1;
    n1.prev = NULL;
    n1.next = NULL;
    n1.content = (char *)malloc(2);
    strcpy(n1.content, "a");
    node n2;
    n2.prev = NULL;
    n2.next = NULL;
    n2.content = (char *)malloc(2);
    strcpy(n2.content, "b");
    node n3;
    n3.prev = NULL;
    n3.next = NULL;
    n3.content = (char *)malloc(2);
    strcpy(n3.content, "c");

    // TEST 1: insert n1 at start 
    insertAtStart(&l1, &n1);
    // TEST 2: insert n3 at end
    insertAtEnd(&l1, &n3);
    printListForwards(&l1); // should be "a c"
    // TEST 3: insert n2 after n1
    insertAfter(&l1, &n1, &n2);
    printListForwards(&l1); // should be "a b c"
    // TEST 4: remove n2
    removeNode(&l1, &n2);
    printListBackwards(&l1); // should be "c a"
    // TEST 5: insert n2 before n3
    insertBefore(&l1, &n3, &n2);
    printListBackwards(&l1); // should be "c b a"
    // TEST 6: find 'c'
    findNode(&l1, "c"); // should be at position '2'
    return 0;
}


void printListForwards(doubleLinkedList* list) {
    node n;
    n.content = (char *)malloc(2);
    n.content = (*list->first).content;
    n.next = (*list->first).next;
    n.prev = NULL;
    printf("Printing forwards: ");
    while (true) {
        printf("%s ", n.content);
        if(n.next != NULL) {
            n.content = (*n.next).content;
            n.prev = (*n.next).prev;
            n.next = (*n.next).next;
        }
        else {
            printf("\n\n");
            break;
        }
    }
}

void printListBackwards(doubleLinkedList* list) {
    node n;
    n.content = (char *)malloc(2);
    n.content = (*list->last).content;
    n.next = NULL;
    n.prev = (*list->last).prev;
    printf("Printing backwards: ");
    while (true) {
        printf("%s ", n.content);
        if(n.prev != NULL) {
            n.content = (*n.prev).content;
            n.next = (*n.prev).next;
            n.prev = (*n.prev).prev;
            
        }
        else {
            printf("\n\n");
            break;
        }
    }
}

void insertAfter(doubleLinkedList* list, node* prevNode, node* newNode) {
    printf("Inserting '%s' after '%s'...\n", newNode->content, prevNode->content);
    newNode->prev = prevNode;
    if (prevNode->next == NULL) {
        newNode->next = NULL;
        list->last = newNode;
    }
    else {
        newNode->next = prevNode->next;
        (*prevNode->next).prev = newNode;
    }
    prevNode->next = newNode;
};

void insertBefore(doubleLinkedList* list, node* nextNode, node* newNode) {
    printf("Inserting '%s' before '%s'...\n", newNode->content, nextNode->content);
    newNode->next = nextNode;
    if (nextNode->prev == NULL) {
        newNode->prev = NULL;
        list->first = newNode;
    }
    else {
        newNode->prev = nextNode->prev;
        (*nextNode->prev).next = newNode;
    }
    nextNode->prev = newNode;
};

void insertAtStart(doubleLinkedList* list, node* newNode) {
    printf("Inserting '%s' at the start...\n", newNode->content);
    if (list->first == NULL) {
        list->first = newNode;
        list->last = newNode;
    }
    else {
        insertBefore(list, list->first, newNode);
    }
};

void insertAtEnd(doubleLinkedList* list, node* newNode) {
    printf("Inserting '%s' at the end...\n", newNode->content);
    if (list->last == NULL) {
        insertAtStart(list, newNode);
    }
    else {
        insertAfter(list, list->last, newNode);
    }
};

void removeNode(doubleLinkedList* list, node* node) {
    printf("Removing '%s'...\n", node->content);
    if (node->prev == NULL) {
        list->first = node->next;
    }
    else {
        (*node->prev).next = node->next;
    }
    if (node->next == NULL) {
        list->last = node->prev;
    }
    else {
        (*node->next).prev = node->prev;
    }
};

void findNode(doubleLinkedList* list, char* find) {
    printf("Searching for string '%s'...\n", find);
    node n;
    n.content = (char *)malloc(2);
    n.content = (*list->first).content;
    n.next = (*list->first).next;
    n.prev = NULL;
    int c = 0;
    while (true) {
        if(strcmp(n.content, find) == 0) {
            printf("Found at position %d!\n", c);
            break;
        }
        else if(n.next != NULL) {
            n.content = (*n.next).content;
            n.prev = (*n.next).prev;
            n.next = (*n.next).next;
        }
        else {
            printf("Didn't find that string...\n");
            break;
        }
        c++;
    }
};