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
		printf("+ x y z: ����Ʈ�� �� ���� �Է� \n");
		printf("-: ����Ʈ�� �� ������ �����Ѵ�. \n");
		printf("e x y z: ����Ʈ�� �� �Ʒ��� �Է� (��ɾ� +�� �ݴ��� ��ġ, ����Ʈ�� ����� �����Ͱ��� ���� �ö󰣴�.) \n");
		printf("d: ����Ʈ�� �� �Ʒ����� �����Ѵ�. (����Ʈ���� ������ ĭ�� ����ִ�.)\n");
		printf("l: ����Ʈ�� ����� ���� ������ ����Ѵ�.\n");
		printf("c: ����Ʈ�� ����. ����Ʈ�� ��� �� �ٽ� �Է��ϸ� 0������ ����ȴ�.\n");
		printf("m: �������� ���� �� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�.\n");
		printf("n: �������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�.\n");
		printf("s: �������� �Ÿ��� �����Ͽ� ������������ �����Ͽ� ����Ѵ�.\n");
		printf("q: ���α׷��� �����Ѵ�.\n");

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
			printf("����� ���� ���� : %d\n", list.count);
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

		printf("���� �� ���� %d %d %d    %d\n\n", list.coor[value]->x, list.coor[value]->y, list.coor[value]->z, list.coor[value]->Ascend);
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

		printf("���� ����� ���� %d %d %d    %d\n\n", list.coor[value]->x, list.coor[value]->y, list.coor[value]->z, list.coor[value]->Ascend);
	}
}