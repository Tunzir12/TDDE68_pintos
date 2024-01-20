#include "list.h"
#include <stdio.h>
#include <stdlib.h>



/* Implement the functions here */

/* Puts x at the end of the list */
void append(struct list_item *first, int x){

    while( first->next != NULL ){

        first = first->next;
    }

    struct list_item *newItem = (struct list_item *)malloc(sizeof(struct list_item));

    newItem->value = x ;
    newItem->next = NULL;

    first->next = newItem ;
}


/* Puts x at the start of the list */
void prepend(struct list_item *first, int x){

    struct list_item *newItem = (struct list_item *)malloc(sizeof(struct list_item));

    newItem->value = x ;
    newItem->next = first->next;
    first->next = newItem;
}


/* Find the first element in the list larger than x and
 * put x right before that element */
void input_sorted(struct list_item *first, int x){

    struct list_item *current = first;
    struct list_item *temp = first->next;

    while( temp != NULL ){

        if(temp->value>x){
            break;
        }
        current = temp;
        temp = temp->next;
    }

    struct list_item *newItem = (struct list_item *)malloc(sizeof(struct list_item));

    newItem->value = x ;
    newItem->next = temp;
    current->next = newItem;
}

void print(struct list_item * first){

    if(first->next == NULL && first->value <= -1){
        printf("List is empty");
    }

    while (first->next != NULL)
    {
        printf("%d ",first->next->value);
        first = first->next;
    }
    printf("\n");

}

void clear(struct list_item *first){

    struct list_item* current = first;
    struct list_item* temp= first->next;
    while( temp != NULL){
        current = temp;
        temp = temp->next;
        free(current);
    }
    first->next = NULL;
}
