# include <stdio.h>
# include <string.h>
//# include "bst_head.h"

/* comparison function for type char* */
int compare (const void* a, const void* b)
{
	char* l=(char*)a;
	char* r=(char*)b;
	
	if (strcmp(l,r)==0)
		return (0);
	else
	{
		unsigned int value=1000000;
		char c;
		int index=0;
		while(1)
		{
			if (l[index]!=r[index])
			{
				break;
			}
			index++;
		}
		return (l[index]-r[index]);
	}
}

/* print function for type char* */
void prit(const void* a)
{
	printf("%s\n",(char*)a);
}

int main (void)
{
	int a;
	char nam[20];
	while(1)
	{
		scanf("%d",&a);
		if (a==1)
		{
			scanf("%s",nam);
			insert(nam,sizeof(nam),compare);
		}
		if (a==2)
		{
			scanf("%s",nam);
			search(nam,compare);
		}
		if (a==3)
		{
			printTree(prit);
		}
		if (a==4)
		{
			scanf("%s",nam);
			delete_it(nam,compare);
		}
		if (a==0)
			break;
	}
	return 0;
}