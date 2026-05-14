#include "chess.h"

int main() 
{
	Board board;
	cout << "\tWELCOME TO OUR CHESS GAME!!" << endl;
	cout << "Capital letters are for WHITE PIECES and Small letters for BLACK PIECES" << endl;
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
		string turn = board.turnGetter();
		try {
			bool moved = board.movePiece();
			if (moved) {
				string opponent;
				if (turn == "white")  //checking checkmate for the player's who's about to play
				{
					opponent = "black";
				}
				else
				{
					opponent = "white";
				}
				if (board.isCheckMate(opponent))
				{
					board.printBoard();
					cout << "Checkmate! " << opponent << "  lose!! Game Over!" << endl;
					break;
				}
			}
		}
		catch(exception & e)
		{
			cout << "Error : " << e.what() << endl;
			cout << "Invalid input! Positions must be from 1a to 8h" << endl;
		}
	}
	system("pause");
	return 0;
}
