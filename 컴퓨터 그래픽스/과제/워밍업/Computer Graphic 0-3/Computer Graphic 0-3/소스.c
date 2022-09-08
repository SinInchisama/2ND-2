#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printallsentence(char sentence[][100]);
void reverssentence(char sentence[][100]);
void addalpha(char sentence[][100]);

int main() {
	char filename[11];
	char buffer[10][100] = { 0 };
	char c,command = 0;
	int wordcount = 0, numcount = 0, bigcount = 0;

	scanf("%s", filename);

	FILE* fp = fopen(filename, "r");
	if ((fp == NULL)) {
		printf(stderr, "can't open file");
	}

	for (int i = 0; i < 10; i++) {				// ���ڿ� �Է¹޴� �ڵ�

		c = fgetc(fp);
		int count = 0;

		while (c != '\n' && c != EOF) {
			buffer[i][count++] = c;
			c = fgetc(fp);
		}
	}

	while (command != 'q') {
		printf("d: ���� ��ü�� ������ \n");
		printf("e: ������ �������� Ư�� ���ڸ� ���� ���� �����ϱ� (3���� �� 2���� @ ���� ����. ���鵵 �ϳ��� ���ڷ� ����ϱ�\n");
		printf("f: ���� (�Ǵ� e ��ɾ�� ���Ե� Ư�� ����)�� �������� ���� ������\n");
		printf("g: ���� ������ Ư�� ���ڸ� �ٸ� ���ڷ� �ٲٱ� (�ٲ� ����, ���Ӱ� �Է��� ���� �Է¹���)\n");
		printf("h: �տ��� �о��� ��, �ڿ��� �о��� �� ������ ���� �������� ����ϱ�\n");
		printf("q: ���α׷� ����\n");

		printf("\n");
		printallsentence(buffer);

		scanf(" %c", &command);

		switch (command)
		{
		case 'd':
			reverssentence(buffer);
			break;
			
		case 'e':
			addalpha(buffer);
			break;

		case 'f':
			break;

		case 'g':
			break;

		case 'h':
			break;

		case 'q':
			break;
		}
	}

	return 0;
}

void printallsentence(char sentence[][100]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < strlen(sentence[i]); j++)
			printf("%c", sentence[i][j]);
		printf("\n");
	}
}

void reverssentence(char sentence[][100]) {
	for (int i = 0; i < 10; i++) {
		char reverse[100] = { NULL };
		for (int j = 0; j < strlen(sentence[i]); j++) {
			reverse[j] = sentence[i][strlen(sentence[i]) - j-1];
		}
		
		strcpy(sentence[i],reverse);
	}
}

void addalpha(char sentence[][100]) {
	for (int i = 0; i < 10; i++) {
		char newsentence[100] = { NULL };
		int count = 0,wordcount = 0;

		for (int j = 0; j < strlen(sentence[i]); j++) {

			newsentence[count++] = sentence[i][j];

			if (++wordcount == 3) {
				for (int k = 0; k < 2; k++)
					newsentence[count++] = '@';
				wordcount = 0;
			}
		}

		strcpy(sentence[i], newsentence);
	}
}