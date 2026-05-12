#include "chess.h"

int main() 
{
	Board board;
	while (true) {
		board.printBoard();
		char ch;
		cout << "Do you want to exit?"<< endl;
		cin >> ch;
		cin.ignore();
		if (ch == 'y' || ch == 'Y') {
			cout << "Game exited!" << endl;
			break;
		}
		bool moved = board.movePiece();
		if (moved) {
			string turn = board.turnGetter();
			if (board.isCheckMate(turn)) 
			{
				board.printBoard();
				cout << "Checkmate! Game Over!" << endl;
				break;
			}
		}
	}
	system("pause");
	return 0;
}
