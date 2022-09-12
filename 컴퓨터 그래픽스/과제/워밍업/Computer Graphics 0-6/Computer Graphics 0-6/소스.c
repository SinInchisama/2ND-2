#include <stdio.h>
#include <stdlib.h>

int board[30][30] = { 0 };

void initboard();
void printboard();
void moveright();
void moveleft();

int main() {
	char command = '\0';

	srand(time(NULL));
	initboard();


	while (command != 'q') {
		printboard();
		scanf(" %c", &command);

		switch (command) {
		case 'r':
			initboard();
			break;
		case 'R':
			moveright();
			break;
		case 'l':
			moveleft();
			break;
		case 'q':
			break;
		}
	}
}

void initboard() {
	int count = 2;
	int x = 0, y = 0;
	int prev = -1;

	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
			board[i][j] = 0;

	board[0][0] = 1;

	while (x != 29 || y != 29) {
		int move = rand() % 3 + 1;
		int direction = rand() % 100;
		if (-1 < direction&& direction < 10&& prev!= 0) {
			if ((board[y][x] - board[y][x - 1] > 3 || board[y][x - 1] == 0))
				for (int i = 0; i < move; i++) {
					if (x - 1 > -1)
						board[y][--x] = count++;
					else
						break;
				}
			prev = 0;
		}
		else if (9 < direction&& direction < 50&& prev != 1) {
			if ((board[y][x] - board[y][x + 1] > 3 || board[y][x + 1] == 0))
				for (int i = 0; i < move; i++) {
					if (x + 1 < 30)
						board[y][++x] = count++;
					else
						break;
				}
			prev = 1;
		}
		else if (49 < direction&& direction < 60 && prev != 2) {
			if ((board[y][x] - board[y - 1][x] > 3 || board[y - 1][x] == 0))
				for (int i = 0; i < move; i++) {
					if (y - 1 > -1)
						board[--y][x] = count++;
					else break;
				}
			prev = 2;
		}
		else if (60 < direction&& direction < 100&& prev != 3) {
			if ((board[y][x] - board[y + 1][x] > 3 || board[y + 1][x] == 0))
				for (int i = 0; i < move; i++) {
					if (y + 1 < 30)
						board[++y][x] = count++;
					else
						break;
				}
			prev = 3;
		}
		
	}

}

void printboard() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++)
			printf("%5d ", board[i][j]);
		printf("\n");
	}
}

void moveright() {
	int newboard[30][30];

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 29; j++) {
			newboard[i][j+1] = board[i][j];
		}
		newboard[i][0] = board[i][29];
	}

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			board[i][j] = newboard[i][j];
		}
	}
}

void moveleft() {
	int newboard[30][30];

	for (int i = 0; i < 30; i++) {
		for (int j = 29; j > 0; j--) {
			newboard[i][j - 1] = board[i][j];
		}
		newboard[i][29] = board[i][0];
	}

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			board[i][j] = newboard[i][j];
		}
	}
}