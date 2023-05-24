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
		freeBST(*h); ///////////////////////////////////////////////// ���� �߻���. freeBST�� ���� �ִ� ���.
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
	if(ptr == NULL) // ������ Ž���� ���
	{
		return;
	}
	inorderTraversal(ptr->left);
	printf("%d ", ptr->key);
	inorderTraversal(ptr->right);
	// �����̹Ƿ�, �������� ���� �̵�, ��� ��� Ȯ��, ���� ���������� �̵��Ѵ�.
}

void preorderTraversal(Node* ptr)
{
	if(ptr == NULL) // ������ Ž���� ���
	{
		return;
	}
	printf("%d ", ptr->key);
	preorderTraversal(ptr->left);
	preorderTraversal(ptr->right);
	// �����̹Ƿ�, ��� ��� Ȯ��, ���� �������� �̵�, ���������� �̵��Ѵ�.
}

void postorderTraversal(Node* ptr)
{
	if(ptr == NULL) // ������ Ž���� ���
	{
		return;
	}
	postorderTraversal(ptr->left);
	postorderTraversal(ptr->right);
	printf("%d ", ptr->key);
	// �����̹Ƿ�, �������� ���� �̵�, ���� ���������� �̵�, ���� ��� ��带 Ȯ���Ѵ�.
}


int insert(Node* head, int key)
{
	Node* ins = head->left;
	Node* prev = head;
	if(ins == NULL) // ù ����� ���(�� Ʈ���� �ִ� ���)
	{
		head->left = (Node*)malloc(sizeof(Node));
		head->left->left = NULL;
		head->left->right = NULL;
		head->left->key = key;
		return 0;
	}

	// �׷��� ���� ������ ���
	while(1)
	{	
		prev = ins;
		if(key < ins->key) // ���� ����� Ű�� �� ��庸�� ���� ���
		{
			ins = ins->left; // ���� ��ġ�� ���� �ڽ� ������� �� ��.
			if(ins == NULL) // ���� �ڸ��� �Ǿ��ٸ�(���̻� ���� �� ���ٸ�)
			{
				prev->left = (Node*)malloc(sizeof(Node)); // ins ����� �θ� ��带 ��������, ���ʿ� ����
				prev->left->left = NULL;
				prev->left->right = NULL;
				prev->left->key = key;
				return 0;
			}
		}
		else // ������ ���(���� ����� Ű�� �� ��庸�� ū ���)
		{
			ins = ins->right; // ���� ��ġ�� ������ �ڽ� ������� �� ��.
			if(ins == NULL) // ���� �ڸ��� �Ǿ��ٸ�(���̻� ���� �� ���ٸ�)
			{
				prev->right = (Node*)malloc(sizeof(Node)); // ins ����� �θ� ��带 ��������, �����ʿ� ����
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

	if(prev->left == NULL) // �� Ʈ�����
	{
		printf("�� Ʈ���Դϴ�\n");
		return -1;
	}
	if(prev->left->key == key) // ù��° ��尡 ���� ����� ���
	{
		if(prev->left->left == NULL && prev->left->right == NULL) // ���� ������� üũ
		{
			free(prev->left);
			prev->left = NULL;
			return 0; // �����, ���� ����� left ��ũ(����� left ��ũ)�� NULL�� ����
		}
		else // ���� ��尡 �ƴ϶��
		{
			printf("���� ��尡 �ƴմϴ�");
			return -1;
		}
	}

	prev = prev->left;

	while(prev != NULL) // ������ Ž���� ������
	{
		if(prev->key > key) // ���� Ű�� ��尡 �θ� ����� Ű���� ���ʿ� ���� ���
		{
			if(prev->left == NULL) // ���̻� ��ġ�� �� �ִ� �ش� �ڽ��� ���� ���
			{
				break;
			}
			if(prev->left->key == key) // �ٷ� ���� �ڽ��� ���� ����� ���
			{
				if(prev->left->left == NULL && prev->left->right == NULL) // ���� �����
				{
					free(prev->left);
					prev->left = NULL;
					return 0; // �����, ���� ����� left ��ũ�� NULL�� ����
				}
				else // ���� ��尡 �ƴ϶��
				{
					printf("���� ��尡 �ƴմϴ�");
					return -1;
				}
			}
			else // �ش� �ڽ��� ���� ��尡 �ƴ� ��� �ش� ���� ���� ������
			{
				prev = prev->left;
			}
		}
		else // �ݴ� ���(���� Ű�� ��尡 �θ� ����� Ű���� �����ʿ� ���� ���)
		{
			if(prev->right == NULL) // ���̻� ��ġ�� �� �ִ� �ش� �ڽ��� ���� ���
			{
				break;
			}
			if(prev->right->key == key) // �ٷ� ������ �ڽ��� ���� ����� ���
			{
				if(prev->right->left == NULL && prev->right->right == NULL) // ���� ������� Ȯ��
				{
					free(prev->right);
					prev->right = NULL;
					return 0; // �����, ���� ����� right ��ũ�� NULL�� ����
				}
				else // ���� ��尡 �ƴ϶��
				{
					printf("���� ��尡 �ƴմϴ�");
					return -1;
				}
			}
			else // �ش� �ڽ��� ���� ��尡 �ƴ� ��� �ش� ������ ���� ������
			{
				prev = prev->right;
			}
		}
	}

	printf("Ž�� ����");
	return -1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // �� Ʈ���� ����, ���� ��带 �����Ͽ� ������ Ž���Ͽ����� ��ã�� ���
	{
		return NULL;
	}
	if(ptr->key == key) // Ű�� ã�Ҵٸ�
	{
		return ptr; // �ش� ��� ����
	}
	else if(ptr->key > key) // �Է¹��� Ű���� ���� ��� Ű�� ũ�ٸ� �������� ������
	{
		return searchRecursive(ptr->left,key);
	}
	else // �Է¹��� Ű���� ���� ��� Ű�� �۴ٸ� ������������ ������
	{
		return searchRecursive(ptr->right,key);
	}
}

Node* searchIterative(Node* head, int key)
{
	Node* find = head->left; // ã�� ��带 ��Ÿ�� ���� ����
	if(find == NULL) // �� Ʈ�����
	{
		return NULL;
	}

	while(find != NULL) // ���� ��带 �����Ͽ� ������ Ž���� ������ ����
	{
		if(find->key == key) // Ű�� ã�Ҵٸ�
		{
			return find; // �ش� ��� ����
		}
		else if(find->key > key) // �Է¹��� Ű���� ���� ��� Ű�� ũ�ٸ� �������� ������
		{
			find = find->left;
		}
		else // �Է¹��� Ű���� ���� ��� Ű�� �۴ٸ� ������������ ������
		{
			find = find->right;
		}
	}

	return NULL; // ã�� ������ ���

}


int freeBST(Node* head) // ����Ž��(?)�� ����
{
	if (head == NULL) // ���� ����� �ڽ� ���, �� NULL�� ���ٵ� ����
	{
		return 0;
	}
	if (head->right == head) // ù ����� right�� head �ڱ��ڽ��� ����Ű�Ƿ�
	{
		freeBST(head->left);
		free(head);
		return 0;
	}
	freeBST(head->left); // ���� Ž��
	freeBST(head->right); // ������ Ž��
	free(head); // ��� ��� ����
	return 0;
}
