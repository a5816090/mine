//15816090 三浦　敦

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MINE -1
#define OPEN 1
#define CLOSE 0
#define LENGTH 15
#define TRUE 1
#define FALSE 0
#define MARK -2

void mine_exchange(int data[LENGTH][LENGTH], int i, int j, int row, int col) {//mineを置き換える関数
	
}

void ZERO_search(int data[LENGTH][LENGTH], int open[LENGTH][LENGTH], int i, int j, int *remain, int row, int col) {

	if (open[i][j] == CLOSE) {
		open[i][j] = OPEN;
		(*remain)--;
	}
	if (data[i][j] == 0) {
		if (((i - 1) >= 0) && ((i - 1) <= (row - 1)) && ((j - 1) >= 0) && ((j - 1) <= (col - 1)) && data[i - 1][j - 1] != -1) {
			//Open(&open, i - 1, j - 1, &remain);
			if (open[i - 1][j - 1] == CLOSE)
				ZERO_search(data, open, i - 1, j - 1, remain, row, col);
		}
		if (((i - 1) >= 0) && ((i - 1) <= (row - 1)) && (j >= 0) && (j <= (col - 1)) && data[i - 1][j] != -1) {
			//Open(&open, i - 1, j, &remain);
			if (open[i - 1][j] == CLOSE)
				ZERO_search(data, open, i - 1, j, remain, row, col);
		}
		if (((i - 1) >= 0) && ((i - 1) <= (row - 1)) && ((j + 1) >= 0) && ((j + 1) <= (col - 1)) && data[i - 1][j + 1] != -1) {
			//Open(&open, i - 1, j + 1, &remain);
			if (open[i - 1][j + 1] == CLOSE)
				ZERO_search(data, open, i - 1, j + 1, remain, row, col);
		}
		if ((i >= 0) && (i <= (row - 1)) && ((j - 1) >= 0) && ((j - 1) <= (col - 1)) && data[i][j - 1] != -1) {
			//Open(&open, i, j - 1, &remain);
			if (open[i][j - 1] == CLOSE)
				ZERO_search(data, open, i, j - 1, remain, row, col);
		}
		if ((i >= 0) && (i <= (row - 1)) && ((j + 1) >= 0) && ((j + 1) <= (col - 1)) && data[i][j + 1] != -1) {
			//Open(&open, i, j + 1, &remain);
			if (open[i][j + 1] == CLOSE)
				ZERO_search(data, open, i, j + 1, remain, row, col);
		}
		if (((i + 1) >= 0) && ((i + 1) <= (row - 1)) && ((j - 1) >= 0) && ((j - 1) <= (col - 1)) && data[i + 1][j - 1] != -1) {
			//Open(&open, i + 1, j - 1, &remain);
			if (open[i + 1][j - 1] == CLOSE)
				ZERO_search(data, open, i + 1, j - 1, remain, row, col);
		}
		if (((i + 1) >= 0) && ((i + 1) <= (row - 1)) && (j >= 0) && (j <= (col - 1)) && data[i + 1][j] != -1) {
			//Open(&open, i + 1, j, &remain);
			if (open[i + 1][j] == CLOSE)
				ZERO_search(data, open, i + 1, j, remain, row, col);
		}
		if (((i + 1) >= 0) && ((i + 1) <= (row - 1)) && ((j + 1) >= 0) && ((j + 1) <= (col - 1)) && data[i + 1][j + 1] != -1) {
			//Open(&open, i + 1, j + 1, &remain);
			if (open[i + 1][j + 1] == CLOSE)
				ZERO_search(data, open, i + 1, j + 1, remain, row, col);
		}
	}
}

/*int M_search(int data[LENGTH][LENGTH],int row, int col){//markを探す関数
int count=0,i,j;

for (i = 0; i<row; i++) {//初期化
for (j = 0; j<col;j++) {
if(data[i][j] == -2){
count++;
}
}
}
return count;
}*/

int open_or_mark() {//openかmarkかどちらかの値を返す関数
	int i, ope, check, count = 0;
	char len[100];

	do {
		if (count == 0)
			printf("Select the operation (1: open, 2: mark):");
		count = 0;
		gets(len);
		check = TRUE;
		for (i = 0; i < sizeof(len); i++) {
			if (len[i] == ' ') {
				check = FALSE;
				printf("Invalid value!\n");
				break;
			}
		}
		if (check == TRUE) {
			sscanf(len, "%d", &ope);
			if (ope < 1 || ope>2) {
				if (ope != -858993460)//改行以外
					printf("Invalid value!\n");
				else
					count++;
			}
		}

	} while (ope>2 || ope<1);
	return ope;
}

int open_or_mark_or_remove() {//openかmarkかremoveかどれかの値を返す関数
	int i, ope, check, count = 0;
	char len[100];

	do {
		if (count == 0)
			printf("Select the operation (1: open, 2: mark, 3: remove marking):");
		count = 0;
		gets(len);
		check = TRUE;
		for (i = 0; i < sizeof(len); i++) {
			if (len[i] == ' ') {
				check = FALSE;
				printf("Invalid value!\n");
				break;
			}
		}
		if (check == TRUE) {
			sscanf(len, "%d", &ope);
			if (ope <1 || ope>3) {
				if (ope != -858993460)//改行以外
					printf("Invalid value!\n");
				else
					count++;
			}
		}
	} while (ope>3 || ope<1);
	return ope;
}

int main() {
	int i, j, random, mine_count = 0, mine_around = 0, row, col, remain = 0;
	int row_len, col_len, level, ope, M_count = 0;
	int check, M_miss = 0, open_remain = 0;
	int data[LENGTH][LENGTH], open[LENGTH][LENGTH];
	char len[100];

	srand((unsigned int)time(NULL));

	do {//行入力
		printf("Enter the number of rows (an integer within the range from 5 to 15):");
		gets(len);
		check = TRUE;
		for (i = 0; i < sizeof(len); i++) {
			if (len[i] == ' ') {
				check = FALSE;
				printf("Invalid value! Enter an integer within the range from 5 to 15.\n");
				break;
			}
		}
		if (check == TRUE) {
			sscanf(len, "%d", &row_len);
			if (row_len <5 || row_len>15) {
				printf("Invalid value! Enter an integer within the range from 5 to 15.\n");
			}
		}

	} while (row_len <5 || row_len>15);

	do {//列入力
		printf("Enter the number of columns (an integer within the range from 5 to 15):");
		gets(len);
		check = TRUE;
		for (i = 0; i < sizeof(len); i++) {
			if (len[i] == ' ') {
				check = FALSE;
				printf("Invalid value! Enter an integer within the range from 5 to 15.\n");
				break;
			}
		}
		if (check == TRUE) {
			sscanf(len, "%d", &col_len);
			if (col_len <5 || col_len>15) {
				printf("Invalid value! Enter an integer within the range from 5 to 15.\n");
			}
		}
	} while (col_len <5 || col_len>15);

	do {//レベル入力
		printf("Select the degree of difficulty of the game (1: novice, 2: middle, 3: advanced):");
		gets(len);
		check = TRUE;
		for (i = 0; i < sizeof(len); i++) {
			if (len[i] == ' ') {
				check = FALSE;
				printf("Invalid value! Enter either 1, 2, or 3.\n");
				break;
			}
		}
		if (check == TRUE) {
			sscanf(len, "%d", &level);
			if (level <1 || level>3) {
				printf("Invalid value! Enter either 1, 2, or 3.\n");
			}
		}
	} while (level <1 || level>3);

	for (i = 0; i<col_len; i++) {//1行目
		if (i == 0) {
			printf("  ");
		}
		printf("| %2d", i);
		if (i == (col_len - 1)) {
			printf("\n");
		}
	}

	for (i = 0; i<col_len; i++) {//2行目
		if (i == 0) {
			printf("--");
		}
		printf("+---");
		if (i == (col_len - 1)) {
			printf("\n");
		}
	}

	for (i = 0; i<row_len; i++) {//初期化
		for (j = 0; j<col_len; j++) {
			data[i][j] = 0;
			open[i][j] = CLOSE;
			random = rand() % 10;
			if (level == 1) {//noviceの時
				if (random == 0) {//爆弾設置
					data[i][j] = MINE;
					mine_count++;
				}
				else {
					remain++;
				}
			}
			if (level == 2) {//middleの時
				if (random >= 0 && random <= 1) {//爆弾設置
					data[i][j] = MINE;
					mine_count++;
				}
				else {
					remain++;
				}
			}
			if (level == 3) {//advancedの時
				if (random >= 0 && random <= 3) {//爆弾設置
					data[i][j] = MINE;
					mine_count++;
				}
				else {
					remain++;
				}
			}
		}
	}

	for (i = 0; i<row_len; i++) {//周りの数を数える
		for (j = 0; j<col_len; j++) {
			mine_around = 0;
			if (((i - 1) >= 0) && ((i - 1) <= (row_len - 1)) && ((j - 1) >= 0) && ((j - 1) <= (col_len - 1)) && data[i - 1][j - 1] == -1) {
				mine_around++;
			}
			if (((i - 1) >= 0) && ((i - 1) <= (row_len - 1)) && (j >= 0) && (j <= (col_len - 1)) && data[i - 1][j] == -1) {
				mine_around++;
			}
			if (((i - 1) >= 0) && ((i - 1) <= (row_len - 1)) && ((j + 1) >= 0) && ((j + 1) <= (col_len - 1)) && data[i - 1][j + 1] == -1) {
				mine_around++;
			}
			if ((i >= 0) && (i <= (row_len - 1)) && ((j - 1) >= 0) && ((j - 1) <= (col_len - 1)) && data[i][j - 1] == -1) {
				mine_around++;
			}
			if ((i >= 0) && (i <= (row_len - 1)) && ((j + 1) >= 0) && ((j + 1) <= (col_len - 1)) && data[i][j + 1] == -1) {
				mine_around++;
			}
			if (((i + 1) >= 0) && ((i + 1) <= (row_len - 1)) && ((j - 1) >= 0) && ((j - 1) <= (col_len - 1)) && data[i + 1][j - 1] == -1) {
				mine_around++;
			}
			if (((i + 1) >= 0) && ((i + 1) <= (row_len - 1)) && (j >= 0) && (j <= (col_len - 1)) && data[i + 1][j] == -1) {
				mine_around++;
			}
			if (((i + 1) >= 0) && ((i + 1) <= (row_len - 1)) && ((j + 1) >= 0) && ((j + 1) <= (col_len - 1)) && data[i + 1][j + 1] == -1) {
				mine_around++;
			}
			if (data[i][j] != -1) {
				data[i][j] = mine_around;
			}
		}
	}



	for (i = 0; i<row_len; i++) {//表示
		printf("%2d", i);
		for (j = 0; j<col_len; j++) {
			if (open[i][j] == CLOSE) {
				printf("| ? ");
			}
			else {
				if (data[i][j] == -1) {
					printf("| X ");
				}
				else {
					printf("| %d ", data[i][j]);
				}
			}
		}
		printf("\n");
	}

	printf("The number of mined cells: %d\n", mine_count);

	ope = open_or_mark();

	if (ope == 1) {//open時
		printf("Enter the coordinate of a cell to open\n");
		printf("(row and column numbers divided by an en space):");
		scanf("%d %d", &row, &col);

		while ((open[row][col] != CLOSE) || (row<0) || (row>(row_len - 1)) || (col<0) || (col>(col_len - 1))) {
			if (open[row][col] == OPEN) {
				printf("The cell is already open.\n");
			}
			if ((row<0) || (row>(row_len - 1)) || (col<0) || (col>(col_len - 1))) {
				printf("Incorrect coordinate!\n");
			}
			printf("Enter the coordinate of a cell to open\n");
			printf("(row and column numbers divided by an en space):");
			scanf("%d %d", &row, &col);
		}
		ZERO_search(data, open, row, col, &remain, row_len, col_len);
	}
	if (ope == 2) {//mark時
		printf("Enter the coordinate of a cell to mark\n");
		printf("(row and column numbers divided by an en space):");
		scanf("%d %d", &row, &col);

		while ((open[row][col] != CLOSE) || (row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
			if (open[row][col] == OPEN) {
				printf("The cell is already open.\n");
			}
			if (open[row][col] == MARK) {
				printf("The cell is already marked.\n");
			}
			if ((row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
				printf("Incorrect coordinate!\n");
			}
			printf("Enter the coordinate of a cell to mark\n");
			printf("(row and column numbers divided by an en space):");
			scanf("%d %d", &row, &col);
		}
		open[row][col] = MARK;
		if (data[row][col] != MINE) {//間違ってmarkした場合
			M_miss++;
		}
		M_count++;
	}


	while (remain != 0 || M_miss != 0) {//安全な場所がまだCLOSEの間

		if (data[row][col] == MINE && open[row][col] == OPEN) {//爆弾に当たったら

			for (i = 0; i < col_len; i++) {//1行目
				if (i == 0) {
					printf("  ");
				}
				printf("| %2d", i);
				if (i == (col_len - 1)) {
					printf("\n");
				}
			}

			for (i = 0; i < col_len; i++) {//2行目
				if (i == 0) {
					printf("--");
				}
				printf("+---");
				if (i == (col_len - 1)) {
					printf("\n");
				}
			}

			for (i = 0; i < row_len; i++) {//表示
				printf("%2d", i);
				for (j = 0; j < col_len; j++) {
					if (data[i][j] == -1) {
						printf("| X ");
					}
					else {
						printf("| %d ", data[i][j]);
					}
				}
				printf("\n");
			}
			printf("GAME OVER!\n");
			return -1;
		}

		for (i = 0; i < col_len; i++) {//1行目
			if (i == 0) {
				printf("  ");
			}
			printf("| %2d", i);
			if (i == (col_len - 1)) {
				printf("\n");
			}
		}

		for (i = 0; i < col_len; i++) {//2行目
			if (i == 0) {
				printf("--");
			}
			printf("+---");
			if (i == (col_len - 1)) {
				printf("\n");
			}
		}

		for (i = 0; i < row_len; i++) {//表示
			printf("%2d", i);
			for (j = 0; j < col_len; j++) {
				if (open[i][j] == CLOSE) {
					printf("| ? ");
				}
				else if (open[i][j] == MARK) {
					printf("| M ");
				}
				else {
					if (data[i][j] == -1) {
						printf("| X ");
					}
					else {
						printf("| %d ", data[i][j]);
					}
				}
			}
			printf("\n");
		}

		printf("The number of remaining cells to open: %d\n", remain);

		if (M_count == 0) {
			ope = open_or_mark();
		}
		else {
			ope = open_or_mark_or_remove();
		}

		if (ope == 1) {//open時
			printf("Enter the coordinate of a cell to open\n");
			printf("(row and column numbers divided by an en space):");
			scanf("%d %d", &row, &col);

			while ((open[row][col] != CLOSE) || (row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
				if (open[row][col] == OPEN) {
					printf("The cell is already open.\n");
				}
				if (open[row][col] == MARK) {
					printf("To open the cell,remove its marking first.\n");
				}
				if ((row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
					printf("Incorrect coordinate!\n");
				}
				printf("Enter the coordinate of a cell to open\n");
				printf("(row and column numbers divided by an en space):");
				scanf("%d %d", &row, &col);
			}
			ZERO_search(data, open, row, col, &remain, row_len, col_len);
		}
		if (ope == 2) {//mark時
			printf("Enter the coordinate of a cell to mark\n");
			printf("(row and column numbers divided by an en space):");
			scanf("%d %d", &row, &col);

			while ((open[row][col] != CLOSE) || (row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
				if (open[row][col] == OPEN) {
					printf("The cell is already open.\n");
				}
				if (open[row][col] == MARK) {
					printf("The cell is already marked.\n");
				}
				if ((row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
					printf("Incorrect coordinate!\n");
				}
				printf("Enter the coordinate of a cell to mark\n");
				printf("(row and column numbers divided by an en space):");
				scanf("%d %d", &row, &col);
			}
			open[row][col] = MARK;
			if (data[row][col] != MINE) {//間違ってmarkした場合
				M_miss++;
			}
			M_count++;
		}
		if (ope == 3) {//remove時
			printf("Enter the coordinate of a cell to remove marking\n");
			printf("(row and column numbers divided by an en space):");
			scanf("%d %d", &row, &col);

			while ((open[row][col] != MARK) || (row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
				if (open[row][col] == OPEN) {
					printf("The cell is already open.\n");
				}
				else if (open[row][col] != MARK) {
					printf("This cell is not marked.\n");
				}
				if ((row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
					printf("Incorrect coordinate!\n");
				}

				printf("Enter the coordinate of a cell to remove marking\n");
				printf("(row and column numbers divided by an en space):");
				scanf("%d %d", &row, &col);
			}
			open[row][col] = CLOSE;
			if (data[row][col] != MINE)//間違ってmarkしたセルを取り消した場合
				M_miss--;
			M_count--;
		}
		open_remain = 0;
		for (i = 0; i < row_len; i++) {//残りの？の数を数える関数
			for (j = 0; j < col_len; j++) {
				if (open[i][j] == CLOSE) {
					open_remain++;
				}
			}
		}
		printf("miss: %d, open_remain: %d\n", M_miss, open_remain);
		if (M_miss != 0 && open_remain == 0) {//間違ってmarkした個所がある場合
			for (i = 0; i < col_len; i++) {//1行目
				if (i == 0) {
					printf("  ");
				}
				printf("| %2d", i);
				if (i == (col_len - 1)) {
					printf("\n");
				}
			}

			for (i = 0; i < col_len; i++) {//2行目
				if (i == 0) {
					printf("--");
				}
				printf("+---");
				if (i == (col_len - 1)) {
					printf("\n");
				}
			}

			for (i = 0; i < row_len; i++) {//表示
				printf("%2d", i);
				for (j = 0; j < col_len; j++) {
					if (open[i][j] == CLOSE) {
						printf("| ? ");
					}
					else if (open[i][j] == MARK) {
						printf("| M ");
					}
					else {
						if (data[i][j] == -1) {
							printf("| X ");
						}
						else {
							printf("| %d ", data[i][j]);
						}
					}
				}
				printf("\n");
			}
			printf("The number of remaining cells to open: %d\n", remain);
			printf("Enter the coodinate of a cell to remove marking.\n");
			printf("(row and column numbers divided by an en space):");
			scanf("%d %d", &row, &col);

			while ((open[row][col] != MARK) || (row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
				if (open[row][col] == OPEN) {
					printf("The cell is already open.\n");
				}
				else if (open[row][col] != MARK) {
					printf("This cell is not marked.\n");
				}
				if ((row < 0) || (row >(row_len - 1)) || (col < 0) || (col >(col_len - 1))) {
					printf("Incorrect coordinate!\n");
				}

				printf("Enter the coordinate of a cell to remove marking\n");
				printf("(row and column numbers divided by an en space):");
				scanf("%d %d", &row, &col);
			}
			open[row][col] = CLOSE;
			if (data[row][col] != MINE)//間違ってmarkしたセルを取り消した場合
				M_miss--;
			M_count--;
			printf("miss: %d, open_remain: %d\n", M_miss, open_remain);
		}
	}

	printf("Congratulations!\n");

	return 0;
}
