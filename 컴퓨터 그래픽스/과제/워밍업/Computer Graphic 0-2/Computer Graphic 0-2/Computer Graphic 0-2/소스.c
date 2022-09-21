#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
	char filename[11];
	char buffer[10][100] = {0};
	char c;
	int wordcount = 0, numcount = 0, bigcount = 0;

	scanf("%s", filename);

	FILE* fp = fopen(filename ,"r");
	if ((fp == NULL)) {
		printf(stderr, "can't open file");
	}

	for (int i = 0; i < 10; i++) {				// 문자열 입력받는 코드

		c = fgetc(fp);
		int count = 0;

		while (c != '\n' && c!= EOF) {
			buffer[i][count++] = c;
			c = fgetc(fp);
		}

		buffer[i][count] = '\n';
	}

	for (int i = 0; i < 10; i++) {
		int judg = 1;
		int big = 0;

		for (int j = 0; j < strlen(buffer[i]);j++) {
			if (!big && isupper(buffer[i][j]))
				big = 1;
			if (buffer[i][j] == ' ') {
				if (buffer[i][j - 1] != ' ') {
					if (judg == 0) {
						wordcount++;
						if (big)
							bigcount++;
					}
					else if (judg == 1)
						numcount++;
				}
				judg = 1;
				big = 0;
			}
			else if (judg && isalpha(buffer[i][j]))
				judg = 0;

		}

		if (judg == 0) {
			wordcount++;
			if (big)
				bigcount++;
		}
		else if (judg == 1)
			numcount++;
	}

	printf("word count: %d \n", wordcount);
	printf("number count: %d \n",numcount);
	printf("Capital word: %d \n",bigcount);

	return 0;
}