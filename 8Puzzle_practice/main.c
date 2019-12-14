//#include <stdio.h>
//#include <stdlib.h>
//
//#define X 3
//#define Y 3
//
//typedef unsigned char unit;
//
//typedef struct Node{
//	struct Node* next;
//	unit matrix[X][Y];
//}Node;
//
//typedef struct Queue{
//	struct Node* head;
//	struct Node* tail;
//	int len;
//}Queue;
//
//void MInit(void *ptr, int n, int s);
//void QueueInit(Queue* q);
//int IsEmpty(Queue* q);
//void InsertMatrix(Node* node, unit(*arr)[Y]);
//unit(*GetMatrix(Node* node))[Y];
//void EnQueue(Queue* q, unit (*arr)[Y]);
//unit(*DeQueue(Queue* q))[Y];
//
//void PrintArr(unit (*arr)[Y]);
//
//int main() {
//	Queue* q = (Queue*)calloc(1, sizeof(Queue));
//	//MInit(q, 1, sizeof(Queue));
//	QueueInit(q);
//
//	unit arr1[X][Y] = {
//		{1,2,3},
//		{4,5,6},
//		{7,8,0}
//	};
//
//	EnQueue(q, arr1);
//	PrintArr(arr1);
//
//	unit(*arr4)[Y] = DeQueue(q);
//
//	PrintArr(arr4);
//}
//
//void MInit(void * ptr, int n, int s)
//{
//	ptr = calloc(n, s);
//
//	if (!ptr) {
//		printf("Memory Allocation Error\n");
//	}
//}
//
//void QueueInit(Queue * q)
//{
//	q->head = NULL;
//	q->tail = NULL;
//	q->len = 0;
//}
//
//int IsEmpty(Queue * q)
//{	
//	if (q->len == 0) return 1;
//	else return 0;
//}
//
//void InsertMatrix(Node * node, unit(*arr)[Y])
//{
//	unsigned char i = 0, j = 0;
//	for (i = 0; i < X; i++) {
//		for (j = 0; j < Y; j++) {
//			node->matrix[i][j] = arr[i][j];
//		}
//	}
//}
//
//unit(*GetMatrix(Node * node))[Y]
//{
//	/*
//	unit arr[X][Y];
//	int i = 0, j = 0;
//	for (i = 0; i < X; i++) {
//		for (j = 0; j < Y; j++) {
//			arr[i][j] = node->matrix[i][j];
//		}
//	}*/
//	return node->matrix;
//}
//
//void EnQueue(Queue * q, unit(*arr)[Y])
//{
//	Node* newNode = (Node*)calloc(1,sizeof(Node));
//	//MInit(newNode, 1, sizeof(Node));
//	InsertMatrix(newNode, arr);
//
//	if (IsEmpty(q)) {
//		q->head = newNode;
//		q->tail = newNode;
//	}
//	else {
//		newNode->next = NULL;
//		q->tail->next = newNode;
//		q->tail = newNode;
//	}
//
//	q->len++;
//}
//
//unit(*DeQueue(Queue * q))[Y]
//{
//	if (IsEmpty(q)) {
//		printf("Queue is Empty\n");
//		exit(-1);
//	}
//
//	Node* delNode = q->head;
//	q->head = q->head->next;
//	unit (*arr)[Y] = GetMatrix(delNode);
//	PrintArr(arr);
//
//	q->len--;
//	return arr;
//}
//
//void PrintArr(unit (*arr)[Y])
//{
//	int i = 0, j = 0;
//	for (i = 0; i < X; i++) {
//		for (j = 0; j < Y; j++) {
//			printf("%d ", arr[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//
