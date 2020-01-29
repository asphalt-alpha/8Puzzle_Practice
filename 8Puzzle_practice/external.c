//#include <stdio.h>  
//#include <stdlib.h>  
//#include <string.h>  
//
//#define swap( a, b ) temp = a; a = b; b = temp;  
//#define TILE_NUM    9  
//
//typedef struct node {
//	int parent;
//	int child;
//	struct node *next;
//}NODE;
//typedef struct list {
//	int cnt;
//	NODE* head;
//}LIST;
//
//char start[TILE_NUM] = { 2, 8, 3, 1, 6, 4, 7, -1, 5 };
//char goal[TILE_NUM] = { 1, 2, 3, 8, -1, 4, 7, 6, 5 };
//char close = 0;     // �Դ� ���� close��忡 �߰��Ѵ�.  
//int  dist = 0;
//
//void o_c_node_init(LIST *list);
//void add_o_node(LIST *list, int parent, int child);
//void del_node(LIST *list);
//void func();
//int  find_empty();
//int  heruistic(LIST *list);
//void draw(char *node);
//
//void o_c_node_init(LIST *list)
//{
//	list->cnt = 0;
//	list->head = NULL;
//}
//
//void add_o_node(LIST *list, int parent, int child)
//{
//	int i = 0;
//	NODE *p = (NODE *)malloc(sizeof(NODE));
//	p->parent = parent;
//	p->child = child;
//	NODE *tmp = list->head;
//	// ���� �̵��� ��ΰ� ������ �־��� ��ġ��� return  
//	if (close == child)
//		return;
//	if (list->cnt == 0) {
//		list->head = p;
//		p->next = list->head;
//		list->cnt = 1;
//	}
//	else {
//		tmp = list->head;
//		for (i = 0; i < list->cnt; i++)
//			tmp = tmp->next;
//		p->next = tmp->next;
//		tmp->next = p;
//		list->cnt++;
//	}
//}
//
//void del_node(LIST *list)
//{
//	NODE *tmp = list->head;
//	while (list->cnt != 0) {
//		free(list->head);
//		list->head = tmp->next;
//		tmp->next = (tmp->next)->next;
//		list->cnt--;
//	}
//}
//int find_empty()
//{
//	int i = 0;
//	int j = 0;
//	int cnt = 0;
//	/* ����ִ� Ÿ���� ã�´�.  */
//	for (i = 0; i < TILE_NUM; i++) {
//		if (start[i] == -1) {
//			return i;
//		}
//	}
//	return -1;  // ����ִ� Ÿ���� ��ã���� ��� -1��ȯ.  
//}
//void func()
//{
//	int i = 0;
//	int cnt = 0;
//	int empty = 0;
//	int select[2] = { 0x0, };    // [0] = parent, [1] = child  
//
//	LIST list;
//	NODE *tmp;
//	o_c_node_init(&list);   // ���� ���, Ŭ���� ���  �ʱ�ȭ  
//	empty = find_empty();   // �� Ÿ�� ã��  
//
//	/* ������ Ÿ���� open��忡 �߰��Ѵ�. */
//	if (empty != -1) {
//		if (empty > 2) {                // UP  
//			add_o_node(&list, empty, empty - 3);
//		}
//		if (empty < 6) {           // DOWN  
//			add_o_node(&list, empty, empty + 3);
//		}
//		if ((empty % 3) != 2) {    // RIGHT  
//			add_o_node(&list, empty, empty + 1);
//		}
//		if ((empty % 3) != 0) {     // LEFT  
//			add_o_node(&list, empty, empty - 1);
//		}
//
//		/* �̵������ �ּ��� ���� ã�´�. */
//		dist++;
//		close = empty;
//		select[1] = heruistic(&list);
//		tmp = list.head;
//		while (1) {
//			if (select[1] == tmp->child) {
//				select[0] = tmp->parent;
//				break;
//			}
//			tmp = tmp->next;
//		}
//		/* ����(-1)�� �̵��� ��ġ�� �ִ� Ÿ���� �ٲ۴�. */
//		start[select[0]] = start[select[1]];
//		start[select[1]] = -1;
//	}
//	del_node(&list);
//}
//int heruistic(LIST *list)
//{
//	char node[TILE_NUM] = { 0x0, };
//	int misplaced = 0;
//	int totalHerst = 0;
//	int i = 0;
//	int j = 0;
//	int _short = -1;
//	int select_node = 0;
//	NODE *tmp = list->head;
//
//	while (1) {
//		if (i == list->cnt)
//			break;
//		else {
//			misplaced = 0;
//			memcpy(node, start, 9);
//			node[tmp->child] = node[tmp->parent];
//			node[tmp->parent] = -1;
//
//			/* ��ǥ Ÿ�ϰ� �̵����� ���� Ÿ���� ���Ͽ�, ���� �ʴ� Ÿ���� ������ Ȯ���Ѵ�. */
//			for (j = 0; j < TILE_NUM; j++) {
//				if (node[j] != goal[j])
//					misplaced += 1;
//			}
//			totalHerst = dist + misplaced;
//
//			/* ���� ����߿��� F���� ���� ���� ��带 ã�´�. */
//			if ((_short == -1) || (_short > totalHerst)) {
//				_short = totalHerst;
//				select_node = tmp->child;
//			}
//			tmp = tmp->next;
//			i++;
//		}
//	}
//	printf("close : %d, dist : %d, short path : %d, select tile: %d\n", close, dist, _short, select_node);
//	return select_node;
//}
//
//void draw(char *node)
//{
//	int i = 0;
//	for (i = 0; i < TILE_NUM; i++) {
//		if (i % 3 == 0)    printf("\n");
//		if (node[i] == -1)
//			printf("  ");
//		else
//			printf("%d ", node[i]);
//	}
//	printf("\n");
//}
//int main(void)
//{
//	draw(start);
//	while (1) {
//		printf("=================\n");
//		if (memcmp(start, goal, 9) == 0)  break;
//		func();
//		draw(start);
//	}
//	return 0;
//}
