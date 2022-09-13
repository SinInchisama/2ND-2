#include <stdio.h>
#include <stdlib.h>

typedef struct Rectangle {
	int x, y;
}Rectangle;

void initxy(Rectangle rect[]);
void crashcheck(Rectangle rect[]);

int main() {

	Rectangle rectangle[2];
	int round = 0;
	char c = 0;

	srand(time(NULL));

	initxy(rectangle);

	while (c != 'q') {
		printf("Rect 1 : (%d, %d) (%d, %d)\n", rectangle[0].x, rectangle[0].y, rectangle[0].x + 100, rectangle[0].y + 100);
		printf("Rect 2 : (%d, %d) (%d, %d)\n", rectangle[1].x, rectangle[1].y, rectangle[1].x + 100, rectangle[1].y + 100);
		printf("order : %d \n", round);
		scanf(" %c", &c);
		system("cls");

		switch (c) {
		case 'w':
			if (rectangle[round].y - 30 >= 0)
				rectangle[round].y = rectangle[round].y - 30;
			else
				printf("%d crash Wall\n",round);
			break;
		case 's':
			if (rectangle[round].y + 130 <= 600)
				rectangle[round].y = rectangle[round].y + 30;
			else 
				printf("%d crash Wall\n", round);
			break;
		case 'd':
			if (rectangle[round].x + 130 <= 800)
				rectangle[round].x = rectangle[round].x + 30;
			else
				printf("%d crash Wall\n", round);
			break;
		case 'a':
			if (rectangle[round].x - 30 >= 0)
				rectangle[round].x = rectangle[round].x - 30;
			else
				printf("%d crash Wall\n", round);
			break;
		case 'q':
			break;
		}

		crashcheck(rectangle);

		if (!round)
			round = 1;
		else
			round = 0;
	}
}

void initxy(Rectangle rect[]) {
	for (int i = 0; i < 2; i++) {
		rect[i].x = rand() % 701;
		rect[i].y = rand() % 501;
	}
}

void crashcheck(Rectangle rect[]) {
	if (rect[0].x <= rect[1].x + 100&& rect[0].x >= rect[1].x && rect[0].y <= rect[1].y + 100&& rect[0].y >= rect[1].y)
		printf("Creat crash \n");
	else if(rect[0].x+100>=rect[1].x&& rect[0].x + 100 <= rect[1].x + 100 &&rect[0].y<=rect[1].y+100&& rect[0].y >= rect[1].y)
		printf("Creat crash \n");
	else if(rect[0].x+100>=rect[1].x&& rect[0].x + 100 <= rect[1].x + 100 &&rect[0].y+100>=rect[1].y && rect[0].y + 100 <= rect[1].y + 100)
		printf("Creat crash \n");
	else if(rect[0].x<=rect[1].x + 100 && rect[0].x >= rect[1].x &&rect[0].y+100>=rect[1].y && rect[0].y + 100 <= rect[1].y + 100)
		printf("Creat crash \n");
}