#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>

#define X 3
#define Y 3

#define BOT 1
#define TOP 2
#define LEF 3
#define RIG 4

typedef unsigned char unit;

typedef struct Node{
	struct Node* next;	//4
	unit matrix[X][Y];  //9
	unit pre;			//1
	unit cnt;			//1
	struct Node* pNode;	//4
}Node;

typedef struct Queue{
	struct Node* head;
	struct Node* tail;
	int len;
}Queue;

void QueueInit(Queue* q);
int IsEmpty(Queue* q);
void InsertMatrix(Node* node, unit (*arr)[Y]);
unit(*GetMatrix(Node* node))[Y];
void EnQueue(Queue* q, unit (*arr)[Y], int pre, int cnt, Node* par);
Node* DeQueue(Queue* q);
int IsEnd(unit(*start)[Y]);
void PrintArr(unit (*arr)[Y]);
void Swap(unit* a, unit* b);
Node* Bfs(unit(*arr)[Y]);

SIZE_T GetByte() {
	SIZE_T x = 0;
	MEMORY_BASIC_INFORMATION memInfo;
	SIZE_T vAddress = 0;
	ZeroMemory(&memInfo, sizeof(memInfo));
	while (vAddress < (SIZE_T)0x8000000 && VirtualQuery((LPCVOID)vAddress, &memInfo, sizeof(memInfo))) {
		if (memInfo.State == MEM_COMMIT && memInfo.Type == MEM_PRIVATE) {
			x += memInfo.RegionSize;
		}
		vAddress += memInfo.RegionSize;
	}
	return x;
}

unit goal[X][Y] = {
	{1,2,0},
	{4,5,0},
	{7,8,0}
};

long long int legendCnt;

int main() {
	clock_t start, end;
	float res;

	unit map[X][Y] = {
	{1,0,4},
	{2,0,8},
	{7,0,5}
	};

	start = clock();
	Node* cNode = Bfs(map);
	end = clock();
	res = (float)(end - start) / CLOCKS_PER_SEC;

	printf("EnQueue() 횟수 : %lld 회\n", legendCnt);
	printf("수행시간 : %f 초\n", res);

	Node* parentNode = cNode;

	while (parentNode != NULL) {
		PrintArr(parentNode->matrix);
		parentNode = parentNode->pNode;
	}
	printf("%d\n", GetByte());
	return 0;
}

Node* Bfs(unit(*arr)[Y]) {
	Queue* q = (Queue*)calloc(1, sizeof(Queue));
	Node* endNode = NULL;
	QueueInit(q);

	EnQueue(q, arr, -1, 0, NULL);
	printf("Start\n");
	PrintArr(arr);

	int cnt = 0;
	int a=0;
	
	while (!IsEmpty(q)) {
		int i = 0, j = 0;
		Node* dataNode = DeQueue(q);
		endNode = dataNode;
		unit(*data)[Y] = GetMatrix(dataNode);
		int preM = dataNode->pre;
		int preC = dataNode->cnt;
		
		if (IsEnd(data)) {
			printf("END!\n");
			cnt = preC;
			PrintArr(data);
			break;
		}
		
		unit nx = 0, ny = 0, flg=0;
		for (i = 0; i < X; i++) {
			for (j = 0; j < Y; j++) {
				if (data[i][j] == 0) {
					nx = i;
					ny = j;
					flg = 1;
					break;
				}
			}
			if (flg) break;
		}
		if (!flg) {
			exit(-1);
		}

		if (!((nx - 1) < 0) && preM != BOT) {
			Swap(&data[nx][ny], &data[nx - 1][ny]);
			EnQueue(q, data, TOP, preC + 1, dataNode);
			Swap(&data[nx][ny], &data[nx - 1][ny]);
		}
		if (!((nx + 1) >= X) && preM != TOP) {
			Swap(&data[nx][ny], &data[nx + 1][ny]);
			EnQueue(q, data, BOT, preC + 1, dataNode);
			Swap(&data[nx][ny], &data[nx + 1][ny]);
		}
		if (!((ny - 1) < 0) && preM != RIG) {
			Swap(&data[nx][ny], &data[nx][ny - 1]);
			EnQueue(q, data, LEF, preC + 1, dataNode);
			Swap(&data[nx][ny], &data[nx][ny - 1]);
		}
		if (!((ny + 1) >= Y) && preM != LEF) {
			Swap(&data[nx][ny], &data[nx][ny + 1]);
			EnQueue(q, data, RIG, preC + 1, dataNode);
			Swap(&data[nx][ny], &data[nx][ny + 1]);
		}
	}
	printf("%d\n", cnt);
	return endNode;
}

void Swap(unit* a, unit* b) {
	unit temp = *a;
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

void InsertMatrix(Node * node, unit (*arr)[Y])
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
	return node->matrix;
}

void EnQueue(Queue * q, unit (*arr)[Y], int pre, int cnt, Node* par)
{
	Node* newNode = (Node*)calloc(1,sizeof(Node));
	InsertMatrix(newNode, arr);
	newNode->pre = pre;
	newNode->cnt = cnt;
	newNode->pNode = par;
	
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

Node* DeQueue(Queue* q) {
	if (IsEmpty(q)) {
		printf("Queue is already Empty.\n");
		exit(-1);
	}
	Node* delNode = q->head;
	q->head = q->head->next;
	q->len--;
	return delNode;
}

void PrintArr(unit(*arr)[Y])
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