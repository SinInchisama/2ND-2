#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char filename[11];
	char buffer[10][100] = {0};
	char c;

	scanf("%s", filename);

	FILE* fp = fopen(filename ,"r");
	if ((fp == NULL)) {
		printf(stderr, "can't open file");
	}

	for (int i = 0; i < 10; i++) {

		c = fgetc(fp);
		int count = 0;

		while (c != '\n' && c!= EOF) {
			buffer[i][count++] = c;
			c = fgetc(fp);
		}
		
	}

	printf("%d", strlen(buffer[0]));
	return 0;
}