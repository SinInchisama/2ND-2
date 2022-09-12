#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

void print_board(char board[][4], int viewboard[][4]);
void init_board(char board[][4], int viewboard[][4]);
void check_board(char board[][4], int viewboard[][4]);

int score = 0;

int main()
{
	// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
	int Count = 0,row;
	char board[4][4];
	int viewboard[4][4];
	char line;

	srand(time(NULL));
	init_board(board, viewboard);

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 2; j++) {
			system("cls");
			print_board(board, viewboard);
			printf("count %d, score %d\n", 20 - i, score);

			printf("input card :");
			scanf(" %c%d", &line, &row);

			if (line == 'r') {
				init_board(board, viewboard);
				break;
				i = 0;
			}
			else if (line == 'q')
				break;
			else
				viewboard[row-1][line - 97] = 2;
		}

		if (line == 'q' || line == 'r')
			break;
		else
			check_board(board, viewboard);
	}
	return 0;
}

void print_board(char board[][4],int viewboard[][4]) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("  a  b  c  d \n");

	for (int i = 0; i < 4; i++) {
		printf("%d", i+1);
		for (int j = 0; j < 4; j++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			if (viewboard[i][j] == 0)
				printf(" * ");
			else if (viewboard[i][j] == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), board[i][j] - 64);
				printf(" %c ", board[i][j]);
			}
			else if (viewboard[i][j] == 2)
				printf(" O ");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("\n");
	}
}

void init_board(char board[][4], int viewboard[][4]) {
	int overlap[8] = { 0 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			viewboard[i][j] = 0;

			while (1) {
				int a = rand() % 8;

				if (overlap[a] != 2) {
					board[i][j] = 65 + a;
					overlap[a]++;
					break;
				}
			}
		}
	}
}

void check_board(char board[][4], int viewboard[][4]) {
	int count[2][2] = { 0 }, k = 0;

	for (int i = 0; i < 4; i++) {
		for(int j= 0;j<4;j++)
			if (viewboard[i][j] == 2) {
				count[k][0] = i;
				count[k++][1] = j;
			}
	}


	viewboard[count[0][0]][count[0][1]] = viewboard[count[1][0]][count[1][1]] = 1;
	print_board(board, viewboard);
	Sleep(500);
	if (board[count[0][0]][count[0][1]] != board[count[1][0]][count[1][1]])
		viewboard[count[0][0]][count[0][1]] = viewboard[count[1][0]][count[1][1]] = 0;
	else
		score += 50;
}