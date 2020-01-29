#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 3
#define Y 3

#define BOT 1
#define TOP 2
#define LEF 3
#define RIG 4

typedef unsigned char unit;

typedef struct Node{
	struct Node* next;
	unit matrix[X][Y];
	int pre;
	int cnt;
}Node;

typedef struct Queue{
	struct Node* head;
	struct Node* tail;
	int len;
}Queue;

void QueueInit(Queue* q);
int IsEmpty(Queue* q);
void InsertMatrix(Node* node, unit(*arr)[Y]);
unit(*GetMatrix(Node* node))[Y];
void EnQueue(Queue* q, unit (*arr)[Y], int pre, int cnt);
unit(*DeQueue(Queue* q, int* thisPre, int* thisCnt))[Y];
int IsEnd(unit(*start)[Y]);
void PrintArr(unit (*arr)[Y]);
void Swap(unit* a, unit* b);
void Bfs(unit(*arr)[Y]);

unit goal[X][Y] = {
	{1,2,3},
	{4,5,6},
	{7,8,0}
};

long long int legendCnt;

int main() {
	clock_t start, end;
	float res;

	unit map[X][Y] = {
		{6,5,2},
		{7,3,8},
		{1,4,0}
	};

	unit map1[X][Y] = {
		{1,2,3},
		{4,5,6},
		{7,0,8}
	};
	
	start = clock();

	Bfs(map);

	end = clock();
	res = (float)(end - start) / CLOCKS_PER_SEC;

	printf("EnQueue() 횟수 : %lld 회\n", legendCnt);

	printf("수행시간 : %f 초\n", res);
	return 0;
}

void Bfs(unit(*arr)[Y]) {
	Queue* q = (Queue*)calloc(1, sizeof(Queue));
	QueueInit(q);

	EnQueue(q, arr, -1, 0);
	printf("Start\n");
	PrintArr(arr);

	int cnt = 0;
	int a=0;
	//getchar(a);

	while (!IsEmpty(q)) {
		int i = 0, j = 0;
		int preM = 0, preC;
		unit(*data)[Y] = DeQueue(q, &preM, &preC);
		//printf("Dequeued\n");
		//PrintArr(data);

		if (IsEnd(data)) {
			printf("END!\n");
			cnt = preC;
			PrintArr(data);
			break;
		}
		//cnt++;

		int nx = 100, ny = 100;

		int flg = 0;
		for (i = 0; i < X; i++) {
			for (j = 0; j < Y; j++) {
				if (data[i][j] == 0) {
					//printf("find space : [%d] [%d]\n", i, j);
					nx = i;
					ny = j;
					flg = 1;
					break;
				}
			}
			if (flg) break;
		}
		if (!flg) {
			printf("error!\n");
			exit(-1);
		}

		//printf("find space : [%d] [%d]\n", nx, ny);
		
		if (!((nx - 1) < 0) && preM != BOT) {
			Swap(&data[nx][ny], &data[nx - 1][ny]);
			//printf("Swapping...\nPreMove = %d\n", preM);
			//PrintArr(data);
			EnQueue(q, data, TOP, preC + 1);
			Swap(&data[nx][ny], &data[nx - 1][ny]);
			//PrintArr(data);
		}
		if (!((nx + 1) >= X) && preM != TOP) {
			Swap(&data[nx][ny], &data[nx + 1][ny]);
			//printf("Swapping...\nPreMove = %d\n", preM);
			//PrintArr(data);
			EnQueue(q, data, BOT, preC + 1);
			Swap(&data[nx][ny], &data[nx + 1][ny]);
			//PrintArr(data);
		}
		if (!((ny - 1) < 0) && preM != RIG) {
			Swap(&data[nx][ny], &data[nx][ny - 1]);
			//printf("Swapping...\nPreMove = %d\n", preM);
			//PrintArr(data);
			EnQueue(q, data, LEF, preC + 1);
			Swap(&data[nx][ny], &data[nx][ny - 1]);
			//PrintArr(data);
		}
		if (!((ny + 1) >= Y) && preM != LEF) {
			Swap(&data[nx][ny], &data[nx][ny + 1]);
			//("Swapping...\nPreMove = %d\n", preM);
			//PrintArr(data);
			EnQueue(q, data, RIG, preC + 1);
			Swap(&data[nx][ny], &data[nx][ny + 1]);
			//PrintArr(data);
		}
		
	}
	printf("%d\n", cnt);
}

void Swap(unit* a, unit* b) {
	unit temp;
	if (a == NULL) exit(-1);
	temp = *a;
	*a = *b;
	*b = temp;
}

int IsEnd(unit(*start)[Y]) {
	int i = 0, j = 0;
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			if (start[i][j] != goal[i][j])	return 0;
		}
	}
	return 1;
}

void QueueInit(Queue * q)
{
	q->head = NULL;
	q->tail = NULL;
	q->len = 0;
}

int IsEmpty(Queue * q)
{	
	if (q->len == 0) return 1;
	else return 0;
}

void InsertMatrix(Node * node, unit(*arr)[Y])
{
	unsigned char i = 0, j = 0;
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			node->matrix[i][j] = arr[i][j];
		}
	}
}

unit(*GetMatrix(Node * node))[Y]
{
	/*
	unit arr[X][Y];
	int i = 0, j = 0;
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			arr[i][j] = node->matrix[i][j];
		}
	}*/
	return node->matrix;
}

void EnQueue(Queue * q, unit(*arr)[Y], int pre, int cnt)
{
	Node* newNode = (Node*)calloc(1,sizeof(Node));
	//MInit(newNode, 1, sizeof(Node));
	InsertMatrix(newNode, arr);
	newNode->pre = pre;
	newNode->cnt = cnt;
	

	if (IsEmpty(q)) {
		q->head = newNode;
		q->tail = newNode;
	}
	else {
		newNode->next = 0;
		q->tail->next = newNode;
		q->tail = newNode;
	}
	legendCnt++;
	q->len++;
}

unit(*DeQueue(Queue * q, int* thisPre, int* thisCnt))[Y]
{
	if (IsEmpty(q)) {
		printf("Queue is Empty\n");
		exit(-1);
	}

	Node* delNode = q->head;
	q->head = q->head->next;
	unit (*arr)[Y] = GetMatrix(delNode);
	//PrintArr(arr);

	q->len--;
	*thisPre = delNode->pre;
	*thisCnt = delNode->cnt;
	//free(delNode);
	return arr;
}

void PrintArr(unit (*arr)[Y])
{
	int i = 0, j = 0;
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

