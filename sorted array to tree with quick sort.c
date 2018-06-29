#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
};


struct Node* new_node(int key)                              //we create a new node at here
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
	return node;
}

void print(struct Node* node)
{
     if (node == NULL)					//we do preorder sort at here.
          return;
 	 printf("%d ", node->key);
     print(node->left);  
     print(node->right);
}    

struct Node* addingFunction(int array[], int first, int last)	//the function create bst from a sorted array	
{
    if (first > last)
	{
      return NULL;
 	}
                                                 				
    int middle = (first + last)/2;				//the member at middle 
    struct Node *node = new_node(array[middle]);
 	node->left =  addingFunction(array, first, middle-1);  //recall function for left node
 	node->right = addingFunction(array, middle+1, last);	//recall function for right node
 	return node;
}

int main()
{
    int i=0,j=0,n,array[50];
    
	FILE *fp;
    fp = fopen("input1.txt", "r");
    
    if (fp == NULL)
	{
        printf("WARNING!!");
        exit (0);
    }
    while(!feof(fp))
	{
    	fscanf(fp,"%d,",&array[i++]);
	}
	n=i;

    printf("Given array:  ");
	while(array[j]!=NULL)
	{
		printf("%d ",array[j]);
		j++;
	}
	printf("\n\n\n");
    struct Node *root = addingFunction(array, 0, n-1);
    printf("Binary Sorted Tree Preorder:  ");
    print(root);
    
    
	fclose(fp);
    return 0;
}
