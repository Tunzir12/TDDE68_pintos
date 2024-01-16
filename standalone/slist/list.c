#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/* Implement the functions here */
void append(struct list_item *first, int x){
    struct list_item* ptr=first;
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    struct list_item *p = (struct list_item *) malloc ( sizeof (struct  list_item ));
    p->value=x;
    p->next=NULL;
    ptr->next=p;
}
void prepend(struct list_item *first, int x){
    struct list_item* pre=first->next;
    struct list_item *p = (struct list_item *) malloc ( sizeof (struct  list_item ));
    p->value=x;
    p->next=pre;
    first->next=p;
}
//2 4 8 9 
void input_sorted(struct list_item *first, int x){
    struct list_item* parent=first;
    struct list_item* ptr=first->next;
    while(ptr!=NULL){
        if(ptr->value>x){
            break;
        }
        parent=ptr;
        ptr=ptr->next;
    }
    struct list_item *p = (struct list_item *) malloc ( sizeof (struct  list_item ));
    p->value=x;
    p->next=ptr;
    parent->next=p;

    
}

void clear(struct list_item *first){
    struct list_item* parent=first;
    struct list_item* ptr=first->next;
    while(ptr!=NULL){
        parent=ptr;
        ptr=ptr->next;
        free(parent);
    }
    first->next=NULL;
}
void print(struct list_item *first){
    struct list_item* ptr=first;
    while(ptr->next!=NULL){
        printf("%d ", ptr->next->value);
        ptr=ptr->next;
    }
    printf("\n");
}