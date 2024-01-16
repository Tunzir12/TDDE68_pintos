#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	struct list_item root;
	root.value = -1;
	root.next = NULL;

	/* Write your test cases here */
	int i;
	for(i=0;i<10;i++){
		append(&root,i);
	}
	for(i=0;i<3;i++){
		prepend(&root,i);
	}

    print(&root);
	clear(&root);
	for(i=1;i<10;i+=2){
		append(&root,i);
	}
	print(&root);//1 3 5 7 9
	input_sorted(&root,0);
	input_sorted(&root,3);
	input_sorted(&root,10);
	print(&root);//0 1 3 3 5 7 9 10
	clear(&root);
	return 0;
}
