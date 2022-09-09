#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct XYZ {
	int x;
	int y;
	int z;
	int Ascend;
}XYZ;

typedef struct List {
	XYZ* coor[10];
	int count,top;
}List;

void printlist(List list);
void addtoplist(char* command, List* list);
void removetoplist(List* list);
void addunderlist(char* command, List* list);
void removeunderlist(List* list);
void farpoint(List list);
void closepoint(List list);
List Ascendlist(List list);

int main() {
	List list = {NULL};
	XYZ commandnum;
	char command[20] = { '\0' };

	while (command[0] != 'q') {
		printf("+ x y z: 리스트의 맨 위에 입력 \n");
		printf("-: 리스트의 맨 위에서 삭제한다. \n");
		printf("e x y z: 리스트의 맨 아래에 입력 (명령어 +와 반대의 위치, 리스트에 저장된 데이터값이 위로 올라간다.) \n");
		printf("d: 리스트의 맨 아래에서 삭제한다. (리스트에서 삭제된 칸이 비어있다.)\n");
		printf("l: 리스트에 저장된 점의 개수를 출력한다.\n");
		printf("c: 리스트를 비운다. 리스트를 비운 후 다시 입력하면 0번부터 저장된다.\n");
		printf("m: 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력한다.\n");
		printf("n: 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다.\n");
		printf("s: 원점과의 거리를 정렬하여 오름차순으로 정렬하여 출력한다.\n");
		printf("q: 프로그램을 종료한다.\n");

		printlist(list);
		
		scanf(" %[^\n]", command);
		system("cls");

		switch (command[0]) {
		case '+':
			addtoplist(command, &list);
			break;
		case '-':
			removetoplist(&list);
			break;
		case 'e':
			addunderlist(command, &list);
			break;
		case 'd':
			removeunderlist(&list);
			break;
		case 'l':
			printf("저장된 점의 개수 : %d\n", list.count);
			break;
		case 'c':
			for (int i = 0; i < 10; i++) {
				if (list.coor[i] != NULL) {
					XYZ* remove = list.coor[i];
					list.coor[i] = NULL;
					free(remove);
					list.count = 0;
					list.top = 0;
				}
			}
			break;
		case 'm':
			farpoint(list);
			break;
		case'n':
			closepoint(list);
			break;
		case 's':
			list = Ascendlist(list);
			break;
		case 'q':
			break;
		}
	}
}

void printlist(List list) {
	for (int i = 9; i >-1 ; i--) {
		printf("\n------------------------------------\n");
		if (list.coor[i] != NULL)
			printf("%d		|		%d %d %d|  %d\n", i, list.coor[i]->x, list.coor[i]->y, list.coor[i]->z,list.coor[i]->Ascend);
		else
			printf("%d		|		        |   \n", i);
	}
}

void addtoplist(char* command, List* list) {
	if (list->count != 10) {
		XYZ* Addnum = (XYZ*)malloc(sizeof(XYZ));
		char num[3][10] = { '\0' };
		int i = 2;

		for (int j = 0; j < 3; j++) {
			int k = 0;
			for (; i < strlen(command); i++) {

				if (command[i] == ' ')
					break;

				num[j][k++] = command[i];
			}
			i++;
		}

		Addnum->x = atoi(num[0]);
		Addnum->y = atoi(num[1]);
		Addnum->z = atoi(num[2]);
		Addnum->Ascend = Addnum->x * Addnum->x + Addnum->y * Addnum->y + Addnum->z * Addnum->z;

		
		if (list->top <10) {
			list->coor[list->top] = Addnum;
			list->count++;
			list->top++;
		}
		else{
			for (int a = 0; a < 9; a++) {
				if (list->coor[a] == NULL) {
					list->coor[a] = Addnum;
					list->count++;
				}
		}
		}
		
	}
}

void removetoplist(List* list) {

	if (list->count != 0) {
		for (int i = 9; i > -1; i--) {
			if (list->coor[i] != NULL) {
				XYZ* remove = list->coor[i];
				list->coor[i] = NULL;
				free(remove);
				list->count--;
				list->top--;
				break;
			}
		}
	}
}

void addunderlist(char* command, List* list)
{
	if (list->count != 10) {
		XYZ* Addnum = (XYZ*)malloc(sizeof(XYZ));
		char num[3][10] = { '\0' };
		int i = 2;

		for (int j = 0; j < 3; j++) {
			int k = 0;
			for (; i < strlen(command); i++) {

				if (command[i] == ' ')
					break;

				num[j][k++] = command[i];
			}
			i++;
		}

		Addnum->x = atoi(num[0]);
		Addnum->y = atoi(num[1]);
		Addnum->z = atoi(num[2]);
		Addnum->Ascend = Addnum->x ^ 2 + Addnum->y ^ 2 + Addnum->z ^ 2;

		if (list->count > 0) {
			for (i = 9; i > 0; i--) {
				if(list->coor[i-1])
				list->coor[i] = list->coor[i - 1];
			}
			list->coor[0] = Addnum;
			list->count++;
			list->top++;
		}
	}
}

void removeunderlist(List* list) {
	if (list->count > 0) {
		for (int i = 0; i < 10; i++) {
			if (list->coor[i] != NULL) {
				XYZ* remove = list->coor[i];
				list->coor[i] = NULL;
				free(remove);
				list->count--;
				break;
			}
		}
	}
}

List Ascendlist(List list) {
	List new = {'\0'};

	for (int i = 0; i < list.count; i++) {
		int value = 0,result = 10000;

		for (int j = 0; j < 10; j++) {
			if (list.coor[j] != NULL) {
				if (result > list.coor[j]->Ascend) {
					result = list.coor[j]->Ascend;
					value = j;
				}
			}
		}

		new.coor[i] = list.coor[value];
		list.coor[value] = NULL;
	}

	return new;
}

void farpoint(List list) {
	if (list.count != 0) {
		int value = 0, result = 0;

		for (int i = 0; i < 10; i++) {
			if (list.coor[i] != NULL) {
				if (list.coor[i]->Ascend > result) {
					result = list.coor[i]->Ascend;
					value = i;
				}
			}
		}

		printf("가장 먼 점은 %d %d %d    %d\n\n", list.coor[value]->x, list.coor[value]->y, list.coor[value]->z, list.coor[value]->Ascend);
	}
}

void closepoint(List list) {
	if (list.count != 0) {
		int value = 0, result = 10000;

		for (int i = 0; i < 10; i++) {
			if (list.coor[i] != NULL) {
				if (list.coor[i]->Ascend > result) {
					result = list.coor[i]->Ascend;
					value = i;
				}
			}
		}

		printf("가장 가까운 점은 %d %d %d    %d\n\n", list.coor[value]->x, list.coor[value]->y, list.coor[value]->z, list.coor[value]->Ascend);
	}
}