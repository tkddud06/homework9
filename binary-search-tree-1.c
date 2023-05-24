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
	{
		freeBST(*h); ///////////////////////////////////////////////// 오류 발생함. freeBST에 문제 있는 모양.
	}
	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr == NULL) // 끝까지 탐색한 경우
	{
		return;
	}
	inorderTraversal(ptr->left);
	printf("%d ", ptr->key);
	inorderTraversal(ptr->right);
	// 중위이므로, 왼쪽으로 먼저 이동, 가운데 노드 확인, 이후 오른쪽으로 이동한다.
}

void preorderTraversal(Node* ptr)
{
	if(ptr == NULL) // 끝까지 탐색한 경우
	{
		return;
	}
	printf("%d ", ptr->key);
	preorderTraversal(ptr->left);
	preorderTraversal(ptr->right);
	// 전위이므로, 가운데 노드 확인, 이후 왼쪽으로 이동, 오른쪽으로 이동한다.
}

void postorderTraversal(Node* ptr)
{
	if(ptr == NULL) // 끝까지 탐색한 경우
	{
		return;
	}
	postorderTraversal(ptr->left);
	postorderTraversal(ptr->right);
	printf("%d ", ptr->key);
	// 후위이므로, 왼쪽으로 먼저 이동, 이후 오른쪽으로 이동, 이후 가운데 노드를 확인한다.
}


int insert(Node* head, int key)
{
	Node* ins = head->left;
	Node* prev = head;
	if(ins == NULL) // 첫 노드일 경우(빈 트리에 넣는 경우)
	{
		head->left = (Node*)malloc(sizeof(Node));
		head->left->left = NULL;
		head->left->right = NULL;
		head->left->key = key;
		return 0;
	}

	// 그렇지 않은 나머지 경우
	while(1)
	{	
		prev = ins;
		if(key < ins->key) // 넣을 노드의 키가 현 노드보다 작은 경우
		{
			ins = ins->left; // 넣을 위치는 왼쪽 자식 노드쪽이 될 것.
			if(ins == NULL) // 넣을 자리가 되었다면(더이상 비교할 게 없다면)
			{
				prev->left = (Node*)malloc(sizeof(Node)); // ins 노드의 부모 노드를 기준으로, 왼쪽에 삽입
				prev->left->left = NULL;
				prev->left->right = NULL;
				prev->left->key = key;
				return 0;
			}
		}
		else // 나머지 경우(넣을 노드의 키가 현 노드보다 큰 경우)
		{
			ins = ins->right; // 넣을 위치는 오른쪽 자식 노드쪽이 될 것.
			if(ins == NULL) // 넣을 자리가 되었다면(더이상 비교할 게 없다면)
			{
				prev->right = (Node*)malloc(sizeof(Node)); // ins 노드의 부모 노드를 기준으로, 오른쪽에 삽입
				prev->right->left = NULL;
				prev->right->right = NULL;
				prev->right->key = key;
				return 0;
			}
		}
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node* prev = head;

	if(prev->left == NULL) // 빈 트리라면
	{
		printf("빈 트리입니다\n");
		return -1;
	}
	if(prev->left->key == key) // 첫번째 노드가 지울 노드인 경우
	{
		if(prev->left->left == NULL && prev->left->right == NULL) // 리프 노드인지 체크
		{
			free(prev->left);
			prev->left = NULL;
			return 0; // 지우고, 이전 노드의 left 링크(헤더의 left 링크)를 NULL로 설정
		}
		else // 리프 노드가 아니라면
		{
			printf("리프 노드가 아닙니다");
			return -1;
		}
	}

	prev = prev->left;

	while(prev != NULL) // 끝까지 탐색할 때까지
	{
		if(prev->key > key) // 지울 키의 노드가 부모 노드의 키보다 왼쪽에 있을 경우
		{
			if(prev->left == NULL) // 더이상 서치할 수 있는 해당 자식이 없을 경우
			{
				break;
			}
			if(prev->left->key == key) // 바로 왼쪽 자식이 지울 노드일 경우
			{
				if(prev->left->left == NULL && prev->left->right == NULL) // 리프 노드라면
				{
					free(prev->left);
					prev->left = NULL;
					return 0; // 지우고, 이전 노드의 left 링크를 NULL로 설정
				}
				else // 리프 노드가 아니라면
				{
					printf("리프 노드가 아닙니다");
					return -1;
				}
			}
			else // 해당 자식이 지울 노드가 아닌 경우 해당 왼쪽 노드로 내려감
			{
				prev = prev->left;
			}
		}
		else // 반대 경우(지울 키의 노드가 부모 노드의 키보다 오른쪽에 있을 경우)
		{
			if(prev->right == NULL) // 더이상 서치할 수 있는 해당 자식이 없을 경우
			{
				break;
			}
			if(prev->right->key == key) // 바로 오른쪽 자식이 지울 노드일 경우
			{
				if(prev->right->left == NULL && prev->right->right == NULL) // 리프 노드인지 확인
				{
					free(prev->right);
					prev->right = NULL;
					return 0; // 지우고, 이전 노드의 right 링크를 NULL로 설정
				}
				else // 리프 노드가 아니라면
				{
					printf("리프 노드가 아닙니다");
					return -1;
				}
			}
			else // 해당 자식이 지울 노드가 아닌 경우 해당 오른쪽 노드로 내려감
			{
				prev = prev->right;
			}
		}
	}

	printf("탐색 실패");
	return -1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // 빈 트리인 경우와, 리프 노드를 포함하여 끝까지 탐색하였지만 못찾은 경우
	{
		return NULL;
	}
	if(ptr->key == key) // 키를 찾았다면
	{
		return ptr; // 해당 노드 리턴
	}
	else if(ptr->key > key) // 입력받은 키보다 현재 노드 키가 크다면 왼쪽으로 내려감
	{
		return searchRecursive(ptr->left,key);
	}
	else // 입력받은 키보다 현재 노드 키가 작다면 오른쪽쪽으로 내려감
	{
		return searchRecursive(ptr->right,key);
	}
}

Node* searchIterative(Node* head, int key)
{
	Node* find = head->left; // 찾을 노드를 나타낼 변수 생성
	if(find == NULL) // 빈 트리라면
	{
		return NULL;
	}

	while(find != NULL) // 리프 노드를 포함하여 끝까지 탐색할 때까지 진행
	{
		if(find->key == key) // 키를 찾았다면
		{
			return find; // 해당 노드 리턴
		}
		else if(find->key > key) // 입력받은 키보다 현재 노드 키가 크다면 왼쪽으로 내려감
		{
			find = find->left;
		}
		else // 입력받은 키보다 현재 노드 키가 작다면 오른쪽쪽으로 내려감
		{
			find = find->right;
		}
	}

	return NULL; // 찾기 실패한 경우

}


int freeBST(Node* head) // 후위탐색(?)을 응용
{
	if (head == NULL) // 리프 노드의 자식 노드, 즉 NULL에 접근된 상태
	{
		return 0;
	}
	if (head->right == head) // 첫 헤드의 right는 head 자기자신을 가르키므로
	{
		freeBST(head->left);
		free(head);
		return 0;
	}
	freeBST(head->left); // 왼쪽 탐색
	freeBST(head->right); // 오른쪽 탐색
	free(head); // 가운데 노드 삭제
	return 0;
}
