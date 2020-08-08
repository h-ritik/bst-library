# include <stdio.h>
//# include "bst_head.h"

/* compare function for int* type input*/
int compare (const void* a, const void* b)
{
	int l=*(int*)a;
	int r=*(int*)b;
	return(l-r);
}
/* print function for int* type input*/
void prit(const void* a)
{
	printf("%d\n",*(int *)a);
}

int main(void)
{
	int a,b;
	while(1)
	{
		scanf("%d",&a);
		if (a==1)
		{
			scanf("%d",&b);
			insert(&b,sizeof(int),compare);
		}
		if (a==2)
		{
			scanf("%d",&b);
			search(&b,compare);
		}
		if (a==3)
		{
			printTree(prit);
		}
		if (a==4)
		{
			scanf("%d",&b);
			delete_it(&b,compare);
		}

		if (a==0)
			break;
	}
}