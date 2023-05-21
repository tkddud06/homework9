/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr == NULL)
	{
		return;
	}
	inorderTraversal(ptr->left);
	printf("%d ", ptr->key);
	inorderTraversal(ptr->right);
}

void preorderTraversal(Node* ptr)
{
	if(ptr == NULL)
	{
		return;
	}
	printf("%d ", ptr->key);
	preorderTraversal(ptr->left);
	preorderTraversal(ptr->right);
}

void postorderTraversal(Node* ptr)
{
	if(ptr == NULL)
	{
		return;
	}
	postorderTraversal(ptr->left);
	postorderTraversal(ptr->right);
	printf("%d ", ptr->key);
}


int insert(Node* head, int key)
{
	Node* ins = head->left;
	Node* prev = head;
	if(ins == NULL) // 첫 노드일 경우
	{
		head->left = (Node*)malloc(sizeof(Node));
		head->left->left = NULL;
		head->left->right = NULL;
		head->left->key = key;
		return 1;
	}

	// 그렇지 않은 나머지 경우
	while(1)
	{	
		prev = ins;
		if(key < ins->key) // 키가 현 노드보다 작은 경우
		{
			ins = ins->left; // 넣을 위치는 왼쪽 자식 노드
			if(ins == NULL) // 넣을 자리가 되었다면(더이상 비교할 게 없다면)
			{
				prev->left = (Node*)malloc(sizeof(Node)); // ins 노드의 부모 노드를 기준으로, 왼쪽에 삽입
				prev->left->left = NULL;
				prev->left->right = NULL;
				prev->left->key = key;
			}
		}
		else // 나머지 경우
		{
			ins = ins->right; // 넣을 위치는 오른쪽 자식 노드
			if(ins == NULL) // 넣을 자리가 되었다면(더이상 비교할 게 없다면)
			{
				prev->right = (Node*)malloc(sizeof(Node)); // ins 노드의 부모 노드를 기준으로, 오른쪽에 삽입
				prev->right->left = NULL;
				prev->right->right = NULL;
				prev->right->key = key;
			}
		}
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node* del = head->left;
	prev = head;

	if(del == NULL)
	{
		printf("빈 리스트입니다\n");
		return -1;
	}

	while(del != NULL)
	{
		prev = del;

		if(key < ins->key) // 키가 현 노드보다 작은 경우
		{
			del = del->left;
			if(key == del->key)
		{
			if(del->left != NULL || del->right != NULL)
			{
				printf("리프 노드가 아닙니다");
				return -1;
			}
			
			free(del);
			prev->left = NULL;
			return 0;
		}
		}
		else // 나머지 경우
		{
			del = del->right;
			if(key == del->key)
		{
			if(del->left != NULL || del->right != NULL)
			{
				printf("리프 노드가 아닙니다");
				return -1;
			}
			
			free(del);
			prev->right = NULL;
			return 0;
		}
		}


	}
}

Node* searchRecursive(Node* ptr, int key)
{
	
}

Node* searchIterative(Node* head, int key)
{

}


int freeBST(Node* head)
{

}





