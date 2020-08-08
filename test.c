# include <stdio.h>
# include <stdlib.h>
# include <string.h>
//# include "bst_head.h"

/* a custom made struct */
struct node{
	int roll,marks;
	char name[20];
};

/* comparison function for a custom made struct */
int compare (const void* a, const void* b)
{
	int l=((struct node*)a)->marks;
	int r=((struct node*)b)->marks;
	return(r-l);
}

/* print function for a custom made struct*/
void printst (const void* a)
{
	printf("%d %d %s\n",((struct node*)a)->roll,((struct node*)a)->marks,((struct node*)a)->name);
}

int main(void)
{
	int a,b,c;
	char nam[20];
	struct node* head;
	while (1)
	{
		scanf("%d",&a);
		
		if (a==1)
		{
			head=(struct node*)malloc(sizeof(struct node));
			scanf("%d %d %s",&b,&c,nam);
			head->roll=b;
			head->marks=c;
			strcpy(head->name,nam);
			insert(head,sizeof(struct node),compare);
		}
		if (a==2)
		{
			head=(struct node*)malloc(sizeof(struct node));
			scanf("%d",&c);
			head->marks=c;
			search(head,compare);
		}
		if (a==3)
		{
			printTree(printst);
		}
		if (a==4)
		{
			head=(struct node*)malloc(sizeof(struct node));
			scanf("%d",&b);
			head->marks=b;
			delete_it(head,compare);
		}
		if (a==0)
			break;
	}

	return 0;
}
