/*
 * Othello.cpp
 *
 *  Created on: Mar 4, 2020
 *      Author: jessicawu
 */

//Problem 0
//#include <iostream>
//#include <stdlib.h>
//using namespace std;
//
////int func(int k) {
////	if (k <= 2) {
////		return 1;
////	}
////	return (func(k - 1) + func(k - 2));
////}
////
////int main() {
////	cout << func(7);
////	return 0;
////}
#include <iostream>
#include <stdlib.h>
#include <time.h>
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

int main() {
	srand(time(NULL));
	int size = 0;
	getSize(size); // gets the size for the game board.  Note we only do this once for this game.
	GameBoard *game = new GameBoard; // places a gameBoard struct object on the heap.
	game->size = size;  //sets the gameboard's size
	game->totalct = 4;  // the 4 middle squares are taken
	cout << "Size is " << game->size << endl;
	//makeBoard(game, 0, true);


//test for makeBoard2
//	char arr[5] = {'3','3','3','3','3'};
//	makeBoard2(arr,0,5);
//	for (int i = 5 - 1; i >= 0; i--){
//	    cout << arr[i]<<endl;;
//	}
}
void getSize(int &size) {
	int tempSize = rand() % 15 + 5;
	if (tempSize % 2 != 0) {
		tempSize++;
	}
	size = tempSize;

}

void makeBoard(GameBoard *game, int ct, bool flag) {

}

void makeBoard2(char arr[], int ct, int size) {
	if (ct == size) {
		//cout << "inside if";
	} else {
		//cout << "inside else"<<endl;
		//cout << ct << endl;
		arr[ct] = '-';
		//ct++;
		makeBoard2(arr, ct += 1, size);
	}

}

