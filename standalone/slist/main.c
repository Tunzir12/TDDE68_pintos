#include "list.h"
#include<stdio.h>
#include <stdlib.h>

int main()
{
	struct list_item root;
	root.value = -1;
	root.next = NULL;

	/* Write your test cases here */

	append(&root, 3);

	print(&root);
	append(&root, 2);
	prepend(&root, 5);
	input_sorted(&root, 4);
	input_sorted(&root, 7);
	print(&root);
	
	clear(&root);

	append(&root, 9);

	print(&root);
	

	return 0;
}
