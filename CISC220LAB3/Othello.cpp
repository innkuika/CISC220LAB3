/*
 * Othello.cpp
 *
 *  Created on: Mar 4, 2020
 *  Author: jessicawu
 */
//get random size
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <signal.h>
#include <float.h>
using namespace std;
struct GameBoard {
	char **board; // the othello board
	int size; //for the size of the board (it's a square, so size is one dimension)
	char p; //for current player ('X' or 'O')
	int totalct; // for number of used squares (so that when the board is full, the game stops)
};

struct Square {
	char p;
	int x; //x coordinate
	int y; //y coordinate
	int xs; //x step
	int ys; //y step
	bool flip; //T if can flip
	int rank; //for AI to determine priority
	int num; //how many chess can be flipped if placed here, -1 if this spot has already been taken
};

void getSize(int &size);
void makeBoard(GameBoard *game, int ct, bool flag);
void makeBoard2(char arr[], int ct, int size);
void printBoard(GameBoard *game, int ct);
void printBoard2(char arr[], int ct, int size);
char ckwin(GameBoard *game);
int countRow(char arr[], char c, int ct, int size, int num);
int countSquare(GameBoard *game, char c, int size, int ct, int num);
bool compplacepiece(GameBoard *game);
void playGame(bool fp1, bool fp2, GameBoard *game, bool whoplaysfirstflag);
void startGame(GameBoard *game);
bool placepieceperson(GameBoard *game);
int flipPieceNum(GameBoard *game, int x, int y, bool flipflag);
void checkRankandFlipNum(GameBoard *game, Square *s) ;
Square* findSpot2(GameBoard *game, Square *bestSpot, int row, int ct);

int main() {
	srand(time(NULL));
	int size = 0;
	getSize(size); // gets the size for the game board.  Note we only do this once for this game.
	GameBoard *game = new GameBoard; // places a gameBoard struct object on the heap.
	game->size = size;  //sets the gameboard's size
	game->totalct = 4;  // the 4 middle squares are taken
	cout << "Size is " << game->size << endl;
	makeBoard(game, 0, true);
	printBoard(game, 0);

//	game->p = 'X';

//	Square *bs = new Square;
//	bs->num = -1;
//	bs->rank = -1;
//
//	Square *s = new Square;
//	s->x = 1;
//	s->y = 0;
	//s = findSpot2(game, bs, 1, 0);
	//int a = flipPieceNum(game, 1, 0, false);


//	cout<<"a = "<<a<<endl;
//
//	cout<< "s rank: "<<s->rank<<endl;
//	cout<< "s num: "<<s->num<<endl;

//	compplacepiece(game);
//	printBoard(game, 0);

	startGame(game);


	return 0;
}

void checkRankandFlipNum(GameBoard *game, Square *s) {

	int size = game->size;
	int x = s->x;
	int y = s->y;
	s->num = flipPieceNum(game, x, y, false);
//	cout<<"flipPieceNum: "<<s->num<<endl;
	if ((game->board[x][y] != '-') || (s->num == 0)) {
		s->num = -1;
		return;
	}

	int emptNum = countSquare(game, '-', size, 0, 0);

	if ((x == 0 && (y == size - 1 || y == 0))
			|| (x == size - 1 && (y == size - 1 || y == 0))) {
		s->rank = 4;
	} else if ((x % 2 == 0 && (y == size - 1 || y == 0))
			|| (y % 2 == 0 && (x == size - 1 || x == 0))) {
		s->rank = 3;
	} else if (y == size - 1 || y == 0 || x == size - 1 || x == 0) {
		if (emptNum < size * size / 2) {
			s->rank = 2;
		} else {
			s->rank = 1;
		}
	} else if (x % 2 == 0 || y % 2 == 0) {
		if (emptNum < size * size / 2) {
			s->rank = 1;
		} else {
			s->rank = 2;
		}
	}

}

Square* findSpot2(GameBoard *game, Square *bestSpot, int row, int ct) {
	if (ct == game->size) {
		return bestSpot;
	} else {
//		cout << "best spot num: " << bestSpot->num << endl;
		Square *temp = new Square;
		temp->x = row;
		temp->y = ct;

		checkRankandFlipNum(game, temp);

		if ((temp->rank > bestSpot->rank)
				|| (temp->rank == bestSpot->rank && temp->num > bestSpot->num)) {
			bestSpot = temp;
		} else {
			delete temp;
		}
		return findSpot2(game, bestSpot, row, ct += 1);
	}
}

Square* findSpot(GameBoard *game, Square *bestSpot, int ct) {
	if (ct == game->size) {
		return bestSpot;
	} else {
		Square *temp = new Square;
		temp = findSpot2(game, bestSpot, ct, 0);

		if ((temp->rank > bestSpot->rank)
				|| (temp->rank == bestSpot->rank && temp->num > bestSpot->num)) {
			bestSpot = temp;
		} else {
			//delete temp;
		}
		return findSpot(game, bestSpot, ct += 1);
	}
}

bool compplacepiece(GameBoard *game) {
	Square *bestSpot = new Square;
	bestSpot->rank = -1;
	bestSpot->num = -1;

	bestSpot = findSpot(game, bestSpot, 0);
	cout<<"best spot: "<<bestSpot->x<<bestSpot->y<<endl;

	if (bestSpot->num < 0 || bestSpot->rank < 0) {
		return false;
	} else {
		flipPieceNum(game, bestSpot->x, bestSpot->y, true);
		return true;
	}

}
void setArrToInitial(Square *start, Square arr[]) {
	arr[0].p = start->p;
	arr[0].x = start->x - 1;
	arr[0].y = start->y - 1;
	arr[0].xs = -1;
	arr[0].ys = -1;

	arr[1].p = start->p;
	arr[1].x = start->x - 1;
	arr[1].y = start->y;
	arr[1].xs = -1;
	arr[1].ys = 0;

	arr[2].p = start->p;
	arr[2].x = start->x - 1;
	arr[2].y = start->y + 1;
	arr[2].xs = -1;
	arr[2].ys = 1;

	arr[3].p = start->p;
	arr[3].x = start->x;
	arr[3].y = start->y - 1;
	arr[3].xs = 0;
	arr[3].ys = -1;

	arr[4].p = start->p;
	arr[4].x = start->x;
	arr[4].y = start->y + 1;
	arr[4].xs = 0;
	arr[4].ys = 1;

	arr[5].p = start->p;
	arr[5].x = start->x + 1;
	arr[5].y = start->y - 1;
	arr[5].xs = 1;
	arr[5].ys = -1;

	arr[6].p = start->p;
	arr[6].x = start->x + 1;
	arr[6].y = start->y;
	arr[6].xs = 1;
	arr[6].ys = 0;

	arr[7].p = start->p;
	arr[7].x = start->x + 1;
	arr[7].y = start->y + 1;
	arr[7].xs = 1;
	arr[7].ys = 1;

}

Square* buildArray(Square *start) {
	struct Square *arr = new Square[8];
	arr[0].p = start->p;
	arr[0].x = start->x - 1;
	arr[0].y = start->y - 1;
	arr[0].xs = -1;
	arr[0].ys = -1;

	arr[1].p = start->p;
	arr[1].x = start->x - 1;
	arr[1].y = start->y;
	arr[1].xs = -1;
	arr[1].ys = 0;

	arr[2].p = start->p;
	arr[2].x = start->x - 1;
	arr[2].y = start->y + 1;
	arr[2].xs = -1;
	arr[2].ys = 1;

	arr[3].p = start->p;
	arr[3].x = start->x;
	arr[3].y = start->y - 1;
	arr[3].xs = 0;
	arr[3].ys = -1;

	arr[4].p = start->p;
	arr[4].x = start->x;
	arr[4].y = start->y + 1;
	arr[4].xs = 0;
	arr[4].ys = 1;

	arr[5].p = start->p;
	arr[5].x = start->x + 1;
	arr[5].y = start->y - 1;
	arr[5].xs = 1;
	arr[5].ys = -1;

	arr[6].p = start->p;
	arr[6].x = start->x + 1;
	arr[6].y = start->y;
	arr[6].xs = 1;
	arr[6].ys = 0;

	arr[7].p = start->p;
	arr[7].x = start->x + 1;
	arr[7].y = start->y + 1;
	arr[7].xs = 1;
	arr[7].ys = 1;

	arr[0].flip = false;
	arr[1].flip = false;
	arr[2].flip = false;
	arr[3].flip = false;
	arr[4].flip = false;
	arr[5].flip = false;
	arr[6].flip = false;
	arr[7].flip = false;

	return arr;

}

void flipOneDirec(Square *first, GameBoard *game) {
	if (game->board[first->x][first->y] == first->p) {
		return;

	} else {
		//cout << game->board[first->x][first->y] << endl;
		game->board[first->x][first->y] = first->p;
		first->x += first->xs;
		first->y += +first->ys;

		return flipOneDirec(first, game);
	}
}

void flipAllDirec(Square *arr, GameBoard *game, int ct) {
	if (ct == 8) {
		return;
	} else {
		//cout << ct << "flip: " << arr[ct].flip << endl;
		if (arr[ct].flip) {
			flipOneDirec(&arr[ct], game);
		}

		return flipAllDirec(arr, game, ct += 1);
	}

}
int getFlipNumOneDirec(Square *first, GameBoard *game, int num) {
	if (first->x < 0 || first->x >= game->size || first->y < 0
			|| first->y >= game->size
			|| first->p == game->board[first->x][first->y]
			|| game->board[first->x][first->y] == '-') {

		if (first->x < 0 || first->x >= game->size || first->y < 0
				|| first->y >= game->size|| game->board[first->x][first->y] == '-') {
			num = 0;
		}else if (first->p == game->board[first->x][first->y]) {
			first->flip = true;
		}
		return num;
	} else {
		first->x += first->xs;
		first->y += +first->ys;
		num += 1;

		return getFlipNumOneDirec(first, game, num);
	}
}

int getFlipNum(Square arr[], GameBoard *game, int num, int ct) {
	if (ct == 8) {
		return num;
	} else {
		num += getFlipNumOneDirec(&arr[ct], game, 0);
//		cout<<"direction: "<< ct<<endl;
//		cout<<"num: "<< getFlipNumOneDirec(&arr[ct], game, 0)<<endl;
//		cout<<"total num: "<< num<<endl;

		return getFlipNum(arr, game, num, ct += 1);
	}
}

int flipPieceNum(GameBoard *game, int x, int y, bool flipflag) {
	Square *start = new Square;
	start->p = game->p;
	start->x = x;
	start->y = y;
	Square *arr = buildArray(start);

	int num = getFlipNum(arr, game, 0, 0);

	if (flipflag && num != 0) {
		setArrToInitial(start, arr);
		game->board[x][y] = game->p;
		flipAllDirec(arr, game, 0);
	}
	delete[] arr;
	return num;
}

bool placepieceperson(GameBoard *game) {
	int x;
	int y;
	cout << game->p << " Enter the x coordinate: " << endl;
	cin >> x;
	cout << game->p << " Enter the y coordinate: " << endl;
	cin >> y;

	if (x < 0 || x >= game->size || y < 0 || y >= game->size
			|| game->board[x][y] != '-') {
		cout << game->p << " forfeits turn" << endl;
		return false;
	}
	int num = flipPieceNum(game, x, y, true);
	cout << num << endl;

	if (num == 0) {
		cout << game->p << " forfeits turn" << endl;
		return false;
	} else {

		return true;
	}

}

int countRow(char arr[], char c, int size, int ct, int num) {
	if (ct == size) {
		return num;
	} else {
		if (arr[ct] == c) {
			num++;
		}
		return countRow(arr, c, size, ct += 1, num);
	}

}
int countSquare(GameBoard *game, char c, int size, int ct, int num) {
	if (ct == size) {
		return num;
	} else {
		num += countRow(game->board[ct], game->p, game->size, 0, 0);
		return countSquare(game, c, size, ct += 1, num);
	}
}
char ckwin(GameBoard *game) {
	int x = countSquare(game, 'X', game->size, 0, 0);
	int o = countSquare(game, 'O', game->size, 0, 0);

	if (x == o)
		return 'T';
	if (x > o)
		return 'O';
	else
		return 'X';

}
void getSize(int &size) {
//	int tempSize = rand() % 5 + 5;
	int tempSize = 8;
	if (tempSize % 2 != 0) {
		tempSize++;
	}
	size = tempSize;

}

void printFirstRow(int size, int ct) {
	if (ct == 0) {
		cout << " \t";
	}
	if (ct == size) {
		cout << endl;
		return;
	} else {
		cout << ct << " \t";
		return printFirstRow(size, ct += 1);
	}
}

void printBoard(GameBoard *game, int ct) {
	if (ct == 0) {
		printFirstRow(game->size, ct);
	}
	if (ct == game->size) {
		return;
	} else {
		cout << ct << "\t";
		printBoard2(game->board[ct], 0, game->size);
		return printBoard(game, ct += 1);
	}
}

void printBoard2(char arr[], int ct, int size) {
	if (ct == size) {
		cout << endl;
		return;
	} else {
		cout << arr[ct] << "\t";
		return printBoard2(arr, ct += 1, size);
	}

}

void makeBoard(GameBoard *game, int ct, bool flag) {
	if (flag) {
		game->board = new char*[game->size];
		flag = false;
	}
	if (ct == game->size) {
		return;
	} else {
		game->board[ct] = new char[game->size];
		if (ct == game->size / 2) {
			game->board[ct][ct - 1] = 'O';
			game->board[ct][ct] = 'X';
		}
		if (ct == (game->size / 2) - 1) {
			game->board[ct][ct + 1] = 'O';
			game->board[ct][ct] = 'X';
		}
		makeBoard2(game->board[ct], 0, game->size);
		return makeBoard(game, ct += 1, flag);
	}
}

void makeBoard2(char arr[], int ct, int size) {
	if (ct == size) {
		return;
	} else {
		if (arr[ct] != 'X' && arr[ct] != 'O') {
			arr[ct] = '-';
		}
		return makeBoard2(arr, ct += 1, size);
	}

}

void playGame(bool fp1, bool fp2, GameBoard *game, bool whoplaysfirstflag) {
	bool s1 = true;
	bool s2 = true;
	if (fp1 && fp2 && (s1 || s2)) {
		if (whoplaysfirstflag) {
			game->p = 'X';
			s1 = placepieceperson(game);
			printBoard(game, 0);
			game->p = 'O';
			s2 = placepieceperson(game);
			printBoard(game, 0);
		} else {
			game->p = 'O';
			s1 = placepieceperson(game);
			printBoard(game, 0);
			game->p = 'X';
			s2 = placepieceperson(game);
			printBoard(game, 0);
		}
	} else if (fp1 == false && fp2 == false && (s1 || s2)) {
		game->p = 'X';
		s1 = compplacepiece(game);
		printBoard(game, 0);
		game->p = 'O';
		s2 = compplacepiece(game);
		printBoard(game, 0);
	} else {
		if (whoplaysfirstflag) {
			game->p = 'X';
			s1 = placepieceperson(game);
			printBoard(game, 0);
			game->p = 'O';
			s2 = compplacepiece(game);
			printBoard(game, 0);
		} else {
			game->p = 'X';
			s1 = compplacepiece(game);
			printBoard(game, 0);
			game->p = 'O';
			s2 = placepieceperson(game);
			printBoard(game, 0);
		}
	}
	if ((s1 == false && s2 == false)
			|| game->totalct == game->size * game->size) {
		cout << "Game over" << endl;
		printBoard(game, 0);
		return;
	}
	playGame(fp1, fp2, game, whoplaysfirstflag);

}
void startGame(GameBoard *game) {
	cout << "How many players? (0,1, or 2)" << endl;
	int numplayers;
	cin >> numplayers;
	if (numplayers == 0) {
		playGame(false, false, game, true);
	} else if (numplayers == 1) {
		bool whoplaysfirstflag;
		rand() % 2 == 0 ? whoplaysfirstflag = true : whoplaysfirstflag = false;
		playGame(true, false, game, whoplaysfirstflag);
	} else
		playGame(true, true, game, true);
	char w = ckwin(game);
	if (w != 'T') {
		cout << w << " WON!!!!  " << endl;
	} else {
		cout << "Tie game. " << endl;
	}
	string s;
	cout << "Play again? (Y or N)" << endl;
	cin >> s;
	if (s == "Y") {
		game->totalct = 4;
		makeBoard(game, 0, false);
		cout << "STARTING OVER" << endl;
		printBoard(game, 0);
		startGame(game);
	} else {
		cout << "THANKS FOR PLAYING!" << endl;
	}
}

