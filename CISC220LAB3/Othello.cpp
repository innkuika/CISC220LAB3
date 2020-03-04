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

int main() {
	srand(time(NULL));
	int size = 0;
	getSize(size);  // gets the size for the game board.  Note we only do this once for this game.
	cout << size;
}
void getSize(int &size){
	int tempSize = rand()%15+5;
	if(tempSize%2 != 0){
		tempSize ++;
	}
	size = tempSize;

}










