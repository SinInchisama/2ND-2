#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printallsentence(char sentence[][100]);
void reverssentence(char sentence[][100]);
void reversword(char sentence[][100]);
void changealpha(char sentence[][100]);
void overlapword(char sentence[][100]);
//void addalpha(char sentence[][100]);

int addalpha = 0;

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

	for (int i = 0; i < 10; i++) {				// 문자열 입력받는 코드

		c = fgetc(fp);
		int count = 0;

		while (c != '\n' && c != EOF) {
			buffer[i][count++] = c;
			c = fgetc(fp);
		}
	}

	while (command != 'q') {
		printf("d: 문장 전체를 뒤집기 \n");
		printf("e: 동일한 간격으로 특정 문자를 일정 갯수 삽입하기 (3문자 후 2개의 @ 문자 삽입. 공백도 하나의 문자로 취급하기\n");
		printf("f: 띄어쓰기 (또는 e 명령어로 삽입된 특정 문자)를 기준으로 문자 뒤집기\n");
		printf("g: 문자 내부의 특정 문자를 다른 문자로 바꾸기 (바꿀 문자, 새롭게 입력할 문자 입력받음)\n");
		printf("h: 앞에서 읽었을 때, 뒤에서 읽었을 때 어디까지 같은 문자인지 출력하기\n");
		printf("q: 프로그램 종료\n");

		printf("\n");
		printallsentence(buffer);

		scanf(" %c", &command);
		system("cls");
		

		switch (command)
		{
		case 'd':
			reverssentence(buffer);
			break;
			
		case 'e':
			if (!addalpha)
				addalpha = 1;
			else
				addalpha = 0;
			/*addalpha(buffer);*/
			break;
		case 'f':
			reversword(buffer);
			break;

		case 'g':
			changealpha(buffer);
			break;

		case 'h':
			overlapword(buffer);
			break;

		case 'q':
			break;
		}
	}

	return 0;
}

void printallsentence(char sentence[][100]) {
	for (int i = 0; i < 10; i++) {
		int add = 1;
		printf("%c", sentence[i][0]);
		for (int j = 1; j < strlen(sentence[i]); j++) {
			if (addalpha) {
				if ((add++) % 3 == 0)
					printf("@@");
			}
			printf("%c", sentence[i][j]);
		}
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

void reversword(char sentence[][100]) {
	for (int i = 0; i < 10; i++) {
		int prev = 0, next;
		
		for (int j = 1; j < strlen(sentence[i]); j++) {
			if (sentence[i][j] == ' ') {
				char reverse[20] = { NULL };
				for (int k = 0; k < j - prev; k++)
					reverse[k] = sentence[i][j - k - 1];
				for (int k = prev; k < j; k++)
					sentence[i][k] = reverse[k - prev];

				prev = j + 1;
			}
		}

		char reverse[20] = { NULL };
		for (int k = 0; k < strlen(sentence[i]) - prev; k++)
			reverse[k] = sentence[i][strlen(sentence[i]) - k - 1];
		for (int k = prev; k < strlen(sentence[i]); k++)
			sentence[i][k] = reverse[k - prev];
	}
}

void changealpha(char sentence[][100]) {
	char change[3];
	printf("바꿀 단어를 입력해주세요 ex) ab  대소문자도 맞추어주세요\n");
	scanf("%s", change);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < strlen(sentence[i]); j++) {
			if (sentence[i][j] == change[0])
				sentence[i][j] = change[1];
		}
	}
}

void overlapword(char sentence[][100]) {
	for (int i = 0; i < 10; i++) {
		if (sentence[i][0] == sentence[i][strlen(sentence[i]) - 1]) {
			int prev = 0,next;
			char copy[20] = {'\0'};
			for (int j = 0; j < strlen(sentence[i]); j++) {
				if (sentence[i][j] == sentence[i][strlen(sentence[i]) - 1 - j])
					next = j;
				else
					break;
			}
			for (int j = prev; j <= next; j++)
				copy[j] = sentence[i][j];

			printf("%d번째 문장 %s\n",i,copy);
		}
	}
}