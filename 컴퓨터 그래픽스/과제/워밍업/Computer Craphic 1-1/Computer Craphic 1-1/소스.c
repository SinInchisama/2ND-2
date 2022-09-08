#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int size = 3;

typedef struct ARRAY {
	int number[4][4];
}ARRAY;

void printmenu();						// �޴� ����
void initarray(ARRAY *array);			// ��� �ʱ�ȭ �Լ�
void printarray(ARRAY *array);			// ��� ���
int determinant(ARRAY array);			// ��Ľ�
ARRAY mularray(ARRAY* array);
ARRAY changearray(ARRAY array);			// ��ġ ���

int main() {

	ARRAY array[2];
	ARRAY result = {0};
	char select = 'a';

	srand(time(NULL));

	initarray(array);
	printmenu();

	while (select != 'q') {

		scanf(" %c", &select);
		system("cls");
		printmenu();
		printf("\n");

		switch (select) {
		case 'm':
			result = mularray(array);
			printarray(&result);
			break;

		case'a':
			for (int i = 0; i < size * size; i++) {
				result.number[i / size][i % size] = array[0].number[i / size][i % size] + array[1].number[i / size][i % size];
			}
			printarray(&result);
			break;

		case 'd':
			for (int i = 0; i < size * size; i++) {
				result.number[i / size][i % size] = array[0].number[i / size][i % size] - array[1].number[i / size][i % size];
			}
			printarray(&result);
			break;

		case 'r':
			printarray(&array[0]);
			printf("= %d\n",determinant(array[0]));
			printarray(&array[1]);
			printf("= %d\n",determinant(array[1]));
			break;

		case 't':

			array[0] = changearray(array[0]);
			array[1] = changearray(array[1]);

			printarray(&array[0]);
			printf("= %d\n", determinant(array[0]));
			printarray(&array[1]);
			printf("= %d\n", determinant(array[1]));
			break;

		case 'h':
			if (size == 3) {
				size = 4;
				for (int i = 0; i < 3; i++) {
					array[0].number[3][i] = array[0].number[i][3] = 0;
					array[1].number[3][i] = array[1].number[i][3] = 0;
				}
				array[1].number[3][3] = array[0].number[3][3] = 1;
			}
			else size = 3;
			break;
			
		case 's':
			initarray(array);
			break;

		case 'q':
				break;
		}
	}

	return 0;
}

void printmenu() {
	printf("m: ����� ����\n");
	printf("a: ����� ����\n");
	printf("d: ����� ����\n");
	printf("r: ��Ľ��� �� (Determinant) \n");
	printf("t: ��ġ ���(Transposed matrix)�� �� ��Ľ��� ��\n");
	printf("h: 3X3 ����� 4X4 ��ķ� ��ȯ�ϰ� ��Ľ��� �� (4��4�� ��Ľ� ��) ���\n");
	printf("s: ����� ���� ���� �����ϰ� �����Ѵ�.\n");
	printf("q: ���α׷� ����\n");
}

void initarray(ARRAY *array) {

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			array[i].number[j / 3][j % 3] = rand() % 3;
		}
	}
	size = 3;
}

void printarray(ARRAY* array) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			printf(" %d ", array->number[i][j]);
		printf("\n");
	}

	printf("");
}

int determinant(ARRAY array) {
	int det = 0;
	
	det = array.number[0][0] * array.number[1][1] * array.number[2][2] + array.number[0][1] * array.number[1][2] * array.number[2][0] + array.number[0][2] * array.number[1][0] * array.number[2][1]
		- array.number[0][0] * array.number[1][2] * array.number[2][1] - array.number[0][1] * array.number[1][0] * array.number[2][2] - array.number[0][2] * array.number[1][1] * array.number[2][1];

	return det;
}

ARRAY mularray(ARRAY* array) {
	ARRAY mul = {0};

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++)
				mul.number[i][j] = mul.number[i][j] + (array[0].number[i][k] * array[1].number[k][j]);
		}
	}
	return mul;
}

ARRAY changearray(ARRAY array) {
	ARRAY change;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			change.number[i][j] = array.number[j][i];
		}
	}

	return change;
}