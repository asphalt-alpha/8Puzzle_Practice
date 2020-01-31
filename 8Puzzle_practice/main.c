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

typedef struct Stack {
	unit stack[X * 20][2];
	int idx;
}Stack;

void QueueInit(Queue* q);
int QueueIsEmpty(Queue* q);
void InsertMatrix(Node* node, unit (*arr)[Y]);
unit(*GetMatrix(Node* node))[Y];
void EnQueue(Queue* q, unit (*arr)[Y], int pre, int cnt, Node* par);
Node* DeQueue(Queue* q);
int IsEnd(unit(*start)[Y]);
void PrintArr(unit (*arr)[Y]);
void Swap(unit* a, unit* b);
Node* Bfs(unit(*arr)[Y]);

SIZE_T GetByte();

void StackInit(Stack * st);
int StackIsEmpty(Stack * stack);
void Push(Stack * st, unit s, unit e);
unit* Pop(Stack * st);

unit* FindChange(unit(*arr1)[Y], unit(*arr2)[Y]);

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
	{6,4,7},
	{8,0,2},
	{5,3,1}
	};

	Stack* stack = (Stack*)calloc(1, sizeof(Stack));
	StackInit(stack);

	start = clock();
	Node* cNode = Bfs(map);
	end = clock();
	res = (float)(end - start) / CLOCKS_PER_SEC;

	printf("EnQueue() 횟수 : %lld 회\n", legendCnt);
	printf("수행시간 : %f 초\n", res);

	Node* parentNode = cNode;

	while (parentNode->pNode != NULL) {
		unit* xy = FindChange(parentNode->pNode->matrix, parentNode->matrix);
		Push(stack, xy[0], xy[1]);
		parentNode = parentNode->pNode;
	}
	int cnt = 1;
	while (!StackIsEmpty(stack)) {
		unit* xy = Pop(stack);
		printf("%d. %d to %d\n", cnt++, xy[0], xy[1]);
	}

	printf("\n 사용 메모리 : %d Byte\n", GetByte());
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
	
	while (!QueueIsEmpty(q)) {
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

int QueueIsEmpty(Queue * q)
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
	
	if (QueueIsEmpty(q)) {
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
	if (QueueIsEmpty(q)) {
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

void StackInit(Stack * st)
{
	st->idx = 0;
}

int StackIsEmpty(Stack * stack)
{
	if (stack->idx <= 0) return 1;
	else return 0;
}

void Push(Stack * st, unit s, unit e)
{
	st->idx++;
	st->stack[st->idx][0] = s;
	st->stack[st->idx][1] = e;
}

unit* Pop(Stack * st)
{
	if (StackIsEmpty(st)) exit(-100);
	return st->stack[st->idx--];
}

unit * FindChange(unit(*arr1)[Y], unit(*arr2)[Y])
{
	unit xy1[2];
	unit xy2[2];
	int i = 0, j = 0;
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			if (arr1[i][j] == 0) {
				xy1[0] = i;
				xy1[1] = j;
			}
			if (arr2[i][j] == 0) {
				xy2[0] = i;
				xy2[1] = j;
			}
		}
	}
	xy1[1] = xy1[0] * X + xy1[1];
	xy1[0] = xy2[0] * X + xy2[1];
	

	return xy1;
}
