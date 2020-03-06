/*
 * Othello.cpp
 *
 *  Created on: Mar 4, 2020
 *  Author: jessicawu
 */

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

void getSize(int &size);
void makeBoard(GameBoard *game, int ct, bool flag);
void makeBoard2(char arr[], int ct, int size);
void printBoard(GameBoard *game, int ct);
void printBoard2(char arr[], int ct, int size);
char ckwin(GameBoard *game);
int countRow(char arr[], char c, int ct, int size, int num);

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

//testing code
	char arr[5] = { '3', '3', '3', '3', '3' };
	int a = 0;
	a = countRow(arr, '3', 5, 0, 0);

//	printBoard2(arr, 0, 5);
//	for (int i = 5 - 1; i >= 0; i--){
//	    cout << arr[i]<<endl;;
//	}
}
int countRow(char arr[], char c, int size, int ct, int num) {
	if (ct == size) {
		cout << "inside if" << endl;
		cout <<"num\t" <<num << endl;
		return num;
	} else {
		if (arr[ct] == c) {
			cout << "inside else" << endl;
			cout <<"num\t" <<num << endl;
			cout <<"ct\t" <<ct << endl;
			cout <<"size\t" <<size << endl;

			num++;
		}
		countRow(arr, c, size,ct += 1, num);
	}

}
int countSquare(GameBoard *game, char c) {

}
char ckwin(GameBoard *game) {
	int x;
	int o;
}
void getSize(int &size) {
	int tempSize = rand() % 5 + 5;
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
		printFirstRow(size, ct += 1);
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
		printBoard(game, ct += 1);
	}
}

void printBoard2(char arr[], int ct, int size) {
	if (ct == size) {
		cout << endl;
		return;
	} else {
		cout << arr[ct] << "\t";
		printBoard2(arr, ct += 1, size);
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
		makeBoard(game, ct += 1, flag);
	}
}

void makeBoard2(char arr[], int ct, int size) {
	if (ct == size) {
		return;
	} else {
		if (arr[ct] != 'X' && arr[ct] != 'O') {
			arr[ct] = '-';
		}
		makeBoard2(arr, ct += 1, size);
	}

}

