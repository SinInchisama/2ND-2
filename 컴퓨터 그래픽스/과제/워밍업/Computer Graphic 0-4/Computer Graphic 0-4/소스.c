#include <stdio.h>
#include <stdlib.h>

typedef struct Rectangle {
	int x, y;
}Rectangle;

void initxy(Rectangle* rect[]);

int main() {

	Rectangle rectangle[2];
	srand(time(NULL));

	initxy(rectangle);

	while (1) {

	}
}

void initxy(Rectangle rect[]) {
	for (int i = 0; i < 2; i++) {
		rect[i].x = rand() % 800;
		rect[i]->y = rand() % 600;
	}
}