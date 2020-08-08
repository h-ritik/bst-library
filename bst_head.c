
/* This very same code has been used to create the share library */

/* inclusion of header files*/
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <stdio.h>

/* the structure of node*/
struct _bNode{
	void* _bkey; // key
	struct _bNode* _bleft;	// leftchild pointer
	struct _bNode* _bright;	// rightchild pointer
	struct _bNode* _bparent;	// parent pointer
};

/* declaration of tree*/
struct _btree{
	struct _bNode* _broot;	// pointer to root
};

struct _btree* _bTree=NULL;	// Tree, a global variable

struct _bNode* _bRoot;	// Root(not always Tree->root), a global variable

struct _bNode* _bsubtree;	// subtree, a global variable

int _bsize=0;	// size, measures tree size

int _bleft_size=0;	// measures size of left subtree

int _bright_size=0;	// measures size of right subtree

int _bdepth=0;

/* inorder starts here */
void _binorder (struct _bNode* head,void(*pri)(const void*))
{
	/* if head!=NULL, control enters the block */
	if (head!=NULL)
	{
		/* function is invoked */
		_binorder(head->_bleft,pri);

		/* key is printed */
		pri(head->_bkey);

		/* function is invoked */		
		_binorder(head->_bright,pri);
	}
}
/* inorder ends here */

/* preorder starts here */
void _bpreorder(struct _bNode* head,void(*pri)(const void*))
{
	/* if head!=NULL, control enters the block */
	if (head!=NULL)
	{
		/* key is printed */
		pri(head->_bkey);

		/* function is invoked */
		_bpreorder(head->_bleft,pri);

		/* function is invoked */
		_bpreorder(head->_bright,pri);
	}
}
/* preorder ends here */

/* postorder starts here */
void _bpostorder(struct _bNode* head,void(*pri)(const void*))
{
	/* if head!=NULL, control enters the block */
	if (head!=NULL)
	{
		/* function is invoked */
		_bpostorder(head->_bleft,pri);

		/* function is invoked */
		_bpostorder(head->_bright,pri);

		/* key is printed */
		pri(head->_bkey);
	}
}
/* postorder ends here */


/* printTree starts here */
void printTree(void(* pri)(const void*))
{
	/* if size==0, control enters the block */
	if (_bsize==0)
	{
		/* prints the string */
		printf("False\n");
	}

	/* if Tree is created */
	else
	{
		/* prints the string */
		printf("\ninorder:\n");

		/* function is invoked */
		_binorder(_bTree->_broot,pri);

		/* prints the string */
		printf("\npreorder:\n");

		/* function is invoked */
		_bpreorder(_bTree->_broot,pri);

		/* prints the string */
		printf("\npostorder:\n");

		/* function is invoked */
		_bpostorder(_bTree->_broot,pri);

		/* prints new-line */
		printf("\n\n");
	}
}
/* printTree ends here */

/* correct_leftsubtree starts here */
void _bcorrect_leftsubtree(struct _bNode* head,int (*comp)(const void*,const void*))
{
	/* if subtree!=NULL, control enters the block */
	if (_bsubtree!=NULL)
	{
		/* temp is declared */
		struct _bNode* temp;

		/* temp is assigned */
		temp=_bsubtree;

		/* if temp!=NULL, control enters the block */
		while(temp!=NULL)
		{
			/* declaration of Parent */
			if (comp(temp->_bkey,head->_bkey)>0)
			{
				/* declaration of Parent */
				struct _bNode* Parent;

				/* declaration of leftchild */
				struct _bNode* leftchild;

				/* declaration of node1 */
				struct _bNode* node1;

				/* declaration of node2 */
				struct _bNode* node2;

				/* Parent is assigned */
				Parent=temp->_bparent;

				/* leftchild is assigned */
				leftchild=temp->_bleft;

				/* if Parent is NULL */
				if (Parent==NULL)
				{
					/* subtree is assigned */
					_bsubtree=leftchild;

					/* if subtree!=NULL */
					if (_bsubtree!=NULL)

						/* subtree->parent is assigned */
						_bsubtree->_bparent=NULL;

					/* temp->left is NULL */
					temp->_bleft=NULL;
				}

				/* if Parent exists */
				else
				{
					/* if temp is leftchild */
					if (Parent->_bleft==temp)

						/* leftchild becomes leftchild */
						Parent->_bleft=leftchild;
					
					else
						/* else leftchild becomes rightchild */
						Parent->_bright=leftchild;

					/* if leftchild!=NULL */
					if (leftchild!=NULL)

						/* leftchild parent is assigned NULL */
						leftchild->_bparent=Parent;

					/* temp->parent is NULL */
					temp->_bparent=NULL;

					/* temp->left is NULL */
					temp->_bleft=NULL;
				}

				/* node1 is assigned Root */
				node1=_bRoot;

				/* this block adds temp to root */
				while(1)
				{
					/* if node1 is NULL */
					if (node1==NULL)

						/* loop breaks */
						break;

					/* node2 is assigned node1 */
					node2=node1;

					/* if temp-> key is smaller */
					if (comp(temp->_bkey,node1->_bkey)<=0)

						/* node1 moves left */
						node1=node1->_bleft;


					else
						/* else node1 moves right */
						node1=node1->_bright;
				}

				/* if temp->key is smaller or equals to node2->key */
				if (comp(temp->_bkey,node2->_bkey)<=0)

					/* temp becomes left child */
					node2->_bleft=temp;
				else
					/* else temp becomes right child */
					node2->_bright=temp;

				/* temp->parent is assigned */
				temp->_bparent=node2;

				/* function is invoked */
				_bcorrect_leftsubtree(head,comp);

				/* loop breaks */
				break;
			}

			/* temp moves right */
			temp=temp->_bright;
		}
	}
}
/* function ends */


/* correct_rightsubtree starts here */
void _bcorrect_rightsubtree(struct _bNode* head, int (*comp)(const void*,const void*))
{
	/* is subtree!=NULL,control enters the block */
	if (_bsubtree!=NULL)
	{
		/* temp is declared */
		struct _bNode* temp;

		/* temp is assigned */
		temp=_bsubtree;

		/* if temp!=NULL, control enters the block */
		while(temp!=NULL)
		{
			/* if temp->key is smaller or is equal to head->key */
			if (comp(temp->_bkey,head->_bkey)<=0)
			{
				/* declaration of rightchild */
				struct _bNode* rightchild;

				/* declaration of parent */
				struct _bNode* Parent;

				/* declaration of node1 */
				struct _bNode* node1;

				/* declaration of node2 */
				struct _bNode* node2;

				/* Parent is assigned temp->parent */
				Parent=temp->_bparent;

				/* right child is assigned */
				rightchild=temp->_bright;

				/* if Parent is NULL */
				if (Parent==NULL)
				{
					/* subtree is assigned */
					_bsubtree=rightchild;

					/* if rightchild!=NULL */
					if (_bsubtree!=NULL)

						/* subtree->parent is assigned NULL */
						_bsubtree->_bparent=NULL;

					/* temp->right is assigned NULL */
					temp->_bright=NULL;
				}

				/* if Parent exists */
				else
				{
					/* if temp is leftchild */
					if (Parent->_bleft==temp)

						/* rightchild bechoes left child */
						Parent->_bleft=rightchild;

					else
						/* else rightchild becomes right child */
						Parent->_bright=rightchild;

					/* if rightchld!=NULL */
					if (rightchild!=NULL)

						/* rightchild->parent is assigned NULL */
						rightchild->_bparent=Parent;

					/* temp->parent is assigned NULL */
					temp->_bparent=NULL;

					/* temp->right is assigned NULL */
					temp->_bright=NULL;
				}

				/* node1 is assigned Root */
				node1=_bRoot;

				/* this block adds temp to root */
				while(1)
				{
					/* if node1 is NULL */
					if (node1==NULL)
						
						/* loop breaks */
						break;

					/* node2 is assigned node1 */
					node2=node1;

					/* if temp-> key is smaller */
					if (comp(temp->_bkey,node1->_bkey)<=0)

						/* node1 moves left */
						node1=node1->_bleft;
					else
						/* else node1 moves right */
						node1=node1->_bright;
				}

				/* if temp->key is smaller or equals to node2->key */
				if (comp(temp->_bkey,node2->_bkey)<=0)

					/* temp becomes left child */
					node2->_bleft=temp;

				else
					/* else temp becomes right child */
					node2->_bright=temp;

				/* temp->parent is assigned */
				temp->_bparent=node2;

				/* function is invoked */
				_bcorrect_rightsubtree(head,comp);

				/* loop breaks */
				break;
			}

			/* temp moves left */
			temp=temp->_bleft;
		}
	}
}	// function ends here


/* insert_at_root starts here */
void _binsert_at_root(struct _bNode* _bone,struct _bNode* _btwo,int(*comp)(const void*,const void*))
{
	/* _bone=Root, _btwo=head */
	/* if Root key is less than head key, control enters the block,
		idea is this: head is more than or equals to Root, so Root along with its left child
		is shifted as left child of head and head takes Root's place in Tree. There may be 
		elements in Roots right subtree that are less than head->key, so we can't directly attach
		 Root's right child as head's right child. We correct it by correct_right_subtree function.
		This function searchs element in right subtree which are smaller than (or equals to)
		head key and then adds those nodes recursively as Root's right children. When this
		 is done we assign the corrected right child as head's right child */
	
	if (comp(_bone->_bkey,_btwo->_bkey)<=0)
	{
		/* Parent is declared */
		struct _bNode* Parent;

		/* Parent is assigned as Root->parent*/
		Parent=_bone->_bparent;

		/* If Parent is NULL,control enters the block */
		if (Parent==NULL)
		{
			/* Tree->root is assined */
			_bTree->_broot=_btwo;
		}

		/* if Parent is not NULL, control enters the block */
		else
		{
			/* if Root is left child */
			if (Parent->_bleft==_bone)

				/* head is assigned as left child*/
				Parent->_bleft=_btwo;


			else
				/* else head is assigned as right child */
				Parent->_bright=_btwo;
		}

		/* head->parent is assigned */
		_btwo->_bparent=Parent;

		/* Root parent is assigned NULL */
		_bone->_bparent=NULL;

		/* subtree is assigned Root->right */
		_bsubtree=_bone->_bright;

		/*if subtree!=NULL */
		if (_bsubtree!=NULL)
		{
			/* subtree->parent is assigned NULL */
			_bsubtree->_bparent=NULL;
		}

		/* Root right is assigned NULL */
		_bone->_bright=NULL;

		/* Root->parent is assigned */
		_bone->_bparent=_btwo;

		/* head->left is assigned */
		_btwo->_bleft=_bone;

		/* head->left is assigned */
		_bRoot=_bone;

		/* function is invoked to correct right subtree */
		_bcorrect_rightsubtree(_btwo,comp);

		/* head->right is assigned */
		_btwo->_bright=_bsubtree;

		/* if subtree!=NULL */
		if (_bsubtree!=NULL)

			/* subtree->parent is assigned */
			_bsubtree->_bparent=_btwo;

	}

	/* if head key is less than Root key , a similar pattern is followed */
	else
	{
		/*Parent is declared */
		struct _bNode* Parent;

		/* Parent is assigned Root->parent */
		Parent=_bone->_bparent;

		/* if Parent is NULL */
		if (Parent==NULL)
		{
			/* Tree->root is assigned */
			_bTree->_broot=_btwo;
		}

		/* if Parent is present */
		else
		{
			/* if Root is left child */
			if (Parent->_bleft==_bone)

				/* head becomes left child */
				Parent->_bleft=_btwo;
			
			else
				/* head becomes right child */
				Parent->_bright=_btwo;
		}

		/* head->parent is assigned */
		_btwo->_bparent=Parent;

		/* Root->parent is assigned NULL */
		_bone->_bparent=NULL;

		/* subtree is assigned */
		_bsubtree=_bone->_bleft;

		/* if subtree!=NULL */
		if (_bsubtree!=NULL)
		{
			/* subtree->parent is assigned NULL */
			_bsubtree->_bparent=NULL;
		}
		
		/* Root->left is assigned NULL */
		_bone->_bleft=NULL;

		/* head->right is assigned */
		_btwo->_bright=_bone;

		/* Root->parent is assigned */
		_bone->_bparent=_btwo;

		_bRoot=_bone;

		/* function is invoked to correct subtree */
		_bcorrect_leftsubtree(_btwo,comp);

		/* head->left is assigned */
		_btwo->_bleft=_bsubtree;

		/* id subtree!=NULL */
		if (_bsubtree!=NULL)

			/* subtree ->parent is assigned */
			_bsubtree->_bparent=_btwo;
	}
}	// function insert_at root ends here


/* function insert starts here */
void _brec_insert(struct _bNode* _bone, struct _bNode* _btwo,int(*comp)(const void*,const void*))
{
	/* n is declared */
	int n;

	/* n is assigned a random value */
	n=1+rand()%_bsize;

	/* if n==1, control enters the block */
	if (n==1)
	{
		/* insert at root is invoked */
		_binsert_at_root(_bone,_btwo,comp);

		/* prints the string */
		printf("True\n");
	}

	/* if n!=1, control enters the block */
	else
	{	
		/* if head->key is less than Root->key,control enters the block */
		if (comp(_bone->_bkey,_btwo->_bkey)>=0)
		{
			/* if Root->left is NULL, control enters the block */
			if (_bone->_bleft==NULL)
			{
				/* head parent is assigned */
				_bone->_bleft=_btwo;

				/* Root->left is aasigned */
				_btwo->_bparent=_bone;

				/* prints the string */
				printf("True\n");
			}

			/* if Root->left!=NULL */
			else

				/* insert is invoked */
				_brec_insert(_bone->_bleft,_btwo,comp);
		}

		/* if head->key is more than Root->key, control enters the block */
		else
		{
			/* if Root->right is NULL */
			if (_bone->_bright==NULL)
			{
				/* head->parent is assigned */
				_bone->_bright=_btwo;

				/* Root->right is assigned */
				_btwo->_bparent=_bone;

				/* prints the string */
				printf("True\n");
			}

			/* if Root->right is not NULL */
			else
				/* insert is invoked */
				_brec_insert(_bone->_bright,_btwo,comp);
		}
	}
}


/* function insert starts here */
void insert(void* _New,size_t t,int(*comp)(const void*,const void*))
{
	/* declaration of _space */
	void* _space;

	/* memory allocation for _space */
	_space=malloc(t);

	/* uses memcpy to copy */
	memcpy(_space,_New,t);

	/* declaration of node */
	struct _bNode* head;

	/* memory allocation of head */
	head=(struct _bNode*)malloc(sizeof(struct _bNode));

	/* head-> parent is set */
	head->_bparent=NULL;

	/* head->left is set */
	head->_bleft=NULL;

	/* head->right is set */
	head->_bright=NULL;

	/* key is set */
	head->_bkey=_space;

	/* rand is seeded */
	srand(time(NULL));

	/* if size is 0 */ 
	if (_bsize==0)
	{
		/* memory allocated for Tree */
		_bTree=(struct _btree*)malloc(sizeof(struct _btree));

		/* Tree->root is set */
		_bTree->_broot=head;

		/* True is set */
		printf("True\n");

		/* size is increased */
		++_bsize;
	}

	/* if size>0 */
	else
	{
		/* function is invoked */
		_brec_insert(_bTree->_broot,head,comp);

		/* size is increased*/
		++_bsize;
	}
}
/* function ends here */


/* function search starts here */ 
void _bsearch(struct _bNode* one,void* two,int(*comp)(const void*,const void*))
{
	/* if Tree is not NULL */
	if (one==NULL)
	{
		/* prints the False */
		printf("False\n");
	}

	/* if tree is not NULL */
	else
	{
		/* if head->key equals key_num */
		if (comp(one->_bkey,two)==0)

			/* the loop breaks */
			printf("True, depth:%d\n",_bdepth);

		/* if one->key > two */
		else if (comp(one->_bkey,two)>0)
		{
			/* depth increases */
			++_bdepth;

			/* function is invoked */
			_bsearch(one->_bleft,two,comp);
		}

		/* else head moves right */
		else
		{
			/* depth increases */
			++_bdepth;

			/* function is invoked */
			_bsearch(one->_bright,two,comp);	
		}
	}
}
/* function ends here */


/* funtion search starts here */
void search(void* _New,int (*comp)(const void*,const void*))
{
	/* depth is 0 */
	_bdepth=0;

	/* if Tree is not created */
	if (_bsize==0)

		/* prints the string */
		printf("False\n");
	else
		/* function is invoked */
		_bsearch(_bTree->_broot,_New,comp);
}
/* function ends here */

/* calculates the size of left subtree */
void __bcalculate_left_size(struct _bNode* head)
{
	/* if head!=NULL */
	if (head!=NULL)
	{
		/* function is invoked */
		__bcalculate_left_size(head->_bleft);
		
		/* size increments */
		++_bleft_size;
		
		/* function is invoked */
		__bcalculate_left_size(head->_bright);
	}
}
/* function ends here */

/* calculates the size of right subtree */
void _bcalculate_right_size(struct _bNode* head)
{
	/* if head!=NULL */
	if (head!=NULL)
	{
		/* function is invoked */
		_bcalculate_right_size(head->_bleft);
		
		/* size increases */
		++_bright_size;

		/* function is invoked */
		_bcalculate_right_size(head->_bright);
	}
}
/* function ends here */


/* join starts here */
struct _bNode* _bjoin(struct _bNode* L,struct _bNode* R)
{
	/* left_size is assigned 0 */
	_bleft_size=0;

	/* function is invoked */
	__bcalculate_left_size(L);

	/* right_size is assigned 0 */
	_bright_size=0;

	/* function is invoked */
	_bcalculate_right_size(R);

	/* total is declared */
	int total;

	/* total is assigned */
	total=_bleft_size+_bright_size;

	/* if total is 0 */
	if (total==0)
	{
		/* NULL is returned */
		return (NULL);
	}

	/* if left_size is 0 */
	else if (_bleft_size==0)
	{
		/* R is returned */
		return (R);
	}

	/* if (right_size is 0) */
	else if (_bright_size==0)
	{
		/* L is returned */
		return (L);
	}
	
	/* n is declared */
	int n;

	/* n is assigned a randomized value */
	n=rand()%total;

	/* if n is less than left_size */
	if (n<_bleft_size)
	{
		/* rightchild is declared */
		struct _bNode* rightchild;

		/* rightchild is assigned */
		rightchild=L->_bright;

		/* L->right is assigned to NULL */
		L->_bright=NULL;

		/* if rightchild!=NULL */
		if (rightchild!=NULL)

			/* rightchild->parent is NULL */
			rightchild->_bparent=NULL;

		/* function is invoked */
		L->_bright=_bjoin(rightchild,R);

		/* rightchild is assigned */
		rightchild=L->_bright;

		/* if rightchild!=NULL */
		if (rightchild!=NULL)

			/* rightchild->parent is assigned */ 
			rightchild->_bparent=L;

		/* L id returned */
		return (L);
	}

	/* else if n is greater than left_size */
	else
	{
		/* leftchild is declared */
		struct _bNode* leftchild;

		/* leftchild is assigned */
		leftchild=R->_bleft;

		/* R->left is assigned */
		R->_bleft=NULL;

		/* leftchild!=NULL */
		if (leftchild!=NULL)

			/* leftchild->parent is assigned NULL */
			leftchild->_bparent=NULL;

		/* R->left is assigned */
		R->_bleft=_bjoin(L,leftchild);

		/* leftchild is assigned */
		leftchild=R->_bleft;

		/* if leftchild!=NULL */
		if (leftchild!=NULL)

			/* leftchild->parent is assigned */
			leftchild->_bparent=R;
		
		/* R is returned */
		return (R);
	}
}
/* function ends here */


/* function find starts here */
struct _bNode* _bfind (void *_New,int (*comp)(const void*,const void*))
{
	/* one is declared */
	struct _bNode* one;

	/* one is assigned */
	one=_bTree->_broot;

	/* while one!=NULL */
	while(one!=NULL)
	{
		/* one->key == new */
		if (comp(one->_bkey,_New)==0)

			/* the loop breaks */
			break;

		/* one->key > new */
		if (comp(one->_bkey,_New)>0)

			/* one moves left */
			one=one->_bleft;
		
		else
			/* one moves right */
			one=one->_bright;
	}

	/* returns one */
	return (one);
}
/* find ends here */


/* function delete_it starts here */
void delete_it (void* _New,int (*comp)(const void*, const void*))
{
	/* head is declared */
	struct _bNode* head;

	/* head is assigned NULL */
	head=NULL;

	/* if Tree is already built */
	if (_bsize!=0)

		/* find is invoked */
		head=_bfind(_New,comp);

	/* if the key is not present*/
	if (head==NULL)
	{
		/* prints the string */
		printf("False\n");
	}

	/* if a node with the key is found */
	else
	{
		/* dcelaration of parent */
		struct _bNode* Parent;

		/* declaration of rightchild */
		struct _bNode* rightchild;

		/* declaration of leftchild */
		struct _bNode* leftchild;

		/* declaration of new_tree */
		struct _bNode* new_tree;

		/* Parent is assigned */
		Parent=head->_bparent;

		/* leftchild is assigned */
		leftchild=head->_bleft;

		/* rightchild is aasigned */
		rightchild=head->_bright;

		/* head->left is assigned NULL */
		head->_bleft=NULL;

		/* head->right is assigned NULL */
		head->_bright=NULL;

		/* if leftchild is not NULL */
		if (leftchild!=NULL)

			/* leftchild-> parent is set to NULL */
			leftchild->_bparent=NULL;

		/* if rightchild is not NULL */
		if (rightchild!=NULL)

			/*	rightchild->parent is set to NULL */ 
			rightchild->_bparent=NULL;

		/* join function is called */
		new_tree=_bjoin(leftchild,rightchild);

		/* if Parent is NULL */
		if (Parent==NULL)
		{
			/* Tree->root is modefied */
			_bTree->_broot=new_tree;

			/* head is freed */
			free(head);
		}

		/* if Parent!=NULL */
		else
		{
			/* if head was leftchild */
			if (Parent->_bleft==head)

				/* new_tree becomes leftchild */
				Parent->_bleft=new_tree;

			/* if head was rightchild */
			else

				/* new_tree becomes rightchild */
				Parent->_bright=new_tree;

			/* if new_tree!=NULL */
			if (new_tree!=NULL)

				/* new_tree->parent is modefied */
				new_tree->_bparent=Parent;

			/* head is freed */
			free(head);
		}

		/* prints the string */
		printf("True\n");

		/* bsize decrements */
		--_bsize;
	}
}
/* function delete_it ends here */