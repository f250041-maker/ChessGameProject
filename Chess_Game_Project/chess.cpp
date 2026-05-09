#include "chess.h"

void piece::symbolSetter(const char s) {
	symbol = s;
}

char piece::symbolGetter()
{
	return symbol;
}

void piece::positionSetter(const char* p) {
	position[0] = p[0];
	position[1] = p[1];
	position[2] = '\0';
}

char* piece::positionGetter()
{
	return position;
}

void piece::colorSetter(string c) { // newly added 
	color = c;
}

string piece::colorGetter() { // newly added 
	return color;
}
int returnRowIndex(char row) { // newly added
	int rowIndex = row - '1';
	return rowIndex;
}
int returnColIndex(char col) { // newly added
	return col - 'a';
}
bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board) // newly added
{
	// out of bound check
	int ct = returnColIndex(toCol);
	int rt = returnRowIndex(toRow);
	if (ct <= -1 || ct >= 8 || rt <= -1 || rt >= 8)
		return false;
	// empty square 
	if (board.grid[rt][ct] == nullptr)
		return true;
	// party check
	int cf = returnColIndex(fromCol);
	int rf = returnRowIndex(fromRow);
	if (board.grid[rt][ct]->colorGetter() == board.grid[rf][cf]->colorGetter())
		return false;
	return true;
}

bool Rook::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board)
{
	int fr = returnRowIndex(fromRow);
	int fc = returnColIndex(fromCol);
	int tr = returnRowIndex(toRow);
	int tc = returnColIndex(toCol);
	bool Check = doubleCheck(fromRow, fromCol, toRow, toCol, board);
	if (Check)
	{
		//vertical moves
		string cl = colorGetter();
		if (fc == tc && fr > tr) { //move up 
			for (int i = fr; i >= tr; i--) {
				if (board.grid[i][tc] == NULL) {
					return true;
				}
				else {
					if (i > tr && i != fr) {
						cout << "There is a piece in the path!" << endl;
						return false;
					}
					else
						return true;
				}
			}
		}
		//move down
		if (fc == tc && fr < tr) {
			for (int i = fr; i <= tr; i++) {
				if (board.grid[i][tc] == NULL)
					return true;
				else {
					if (i < tr && i != fr) {
						cout << "There is a piece in the path!" << endl;
						return false;
					}
					else
						return true;
				}
			}
		}
		//horizontal moves 
		//move right 0->7
		if (fr == tr && fc < tc) {
			if (fc < 7) {
				for (int i = fc;i <= tc;i++) {
					if (board.grid[tr][i] == NULL)
						return true;
					else {
						if (i == tc)
							return true;
						else if (i != fc && i < tc) {
							cout << "There is a piece in the path" << endl;
							return false;
						}
					}
				}
			}
			else {
				cout << "Cannot move further right" << endl;
				return false;
			}
		}
		//move left 7->0
		if (fr == tr && fc > tc) {
			if (fc < 0) {
				cout << "Cannot move further left" << endl;
				return false;
			}
			else {
				for (int i = fc; i >= tc; i--) {
					if (board.grid[tr][i] == NULL)
						return true;
					else {
						if (i == tc)
							return true;
						else if (i != fc && i > tc) {
							cout << "There is a piece in the path" << endl;
							return false;
						}
					}
				}
			}
		}

	}
	else
		return false;
}

bool Pawn::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) // newly added
{
	if (doubleCheck(fromRow, fromCol, toRow, toCol, board) == false)
		return false;
	// valid movement
	int ct = returnColIndex(toCol);
	int rt = returnRowIndex(toRow);
	int cf = returnColIndex(fromCol);
	int rf = returnRowIndex(fromRow);
	string clr = board.grid[rf][cf]->colorGetter();
	if (clr == "black" || clr == "Black" || clr == "Black") {
		if (rf == 1)
			isFirstMove = true;
		else
			isFirstMove = false;
		if (board.grid[rt][ct] == nullptr)
		{
			if (isFirstMove) {
				if (rt - rf != 1 && rt - rf != 2) {
					cout << "Pawn can move only 1 or 2 steps forward." << endl;
					return false;
				}
			}
			else
				if (rt - rf != 1) {
					cout << "Pawn can move only 1 step forward." << endl;
					return false;
				}	
		}
		// diagonal capture
		else {
			if (rt == rf + 1 && ct == cf - 1)
				return true;
			if (rt == rf + 1 && ct == cf + 1)
				return true;
			return false;
		}
	}
	else if (clr == "white" || clr == "White" || clr == "WHITE") {
		if (rf == 6)
			isFirstMove = true;
		else
			isFirstMove = false;
		if (board.grid[rt][ct] == nullptr)
		{
			if (isFirstMove) {
				if (rf - rt != 1 && rf - rt != 2) {
					cout << "Pawn can move only 1 or 2 steps forward." << endl;
					return false;
				}
			}
			else
				if (rf - rt != 1) {
					cout << "Pawn can move only 1 step forward." << endl;
					return false;
				}
		}
		// diagonal capture
		else {
			if (rt == rf - 1 && ct == cf - 1)
				return true;
			else if (rt == rf - 1 && ct == cf + 1)
				return true;
			return false;
		}
	}
	return true;
}

bool Knight::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) // newly added
{
	if (doubleCheck(fromRow, fromCol, toRow, toCol, board) == false)
		return false;
	// valid movement
	int ct = returnColIndex(toCol);
	int rt = returnRowIndex(toRow);
	int cf = returnColIndex(fromCol);
	int rf = returnRowIndex(fromRow);
	if (rt == rf + 2 && ct == cf - 1)
		return true;
	if (rt == rf + 2 && ct == cf + 1)
		return true;
	if (rt == rf + 1 && ct == cf + 2)
		return true;
	if (rt == rf - 1 && ct == cf + 2)
		return true;
	if (rt == rf - 2 && ct == cf + 1)
		return true;
	if (rt == rf - 2 && ct == cf - 1)
		return true;
	if (rt == rf + 1 && ct == cf - 2)
		return true;
	if (rt == rf - 1 && ct == cf - 2)
		return true;
	return false;
}

bool King::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) // newly added
{
	if (doubleCheck(fromRow, fromCol, toRow, toCol, board) == false)
		return false;
	// valid movement
	int ct = returnColIndex(toCol);
	int rt = returnRowIndex(toRow);
	int cf = returnColIndex(fromCol);
	int rf = returnRowIndex(fromRow);
	if (rt == rf - 1 && ct == cf)
		return true;
	if (rt == rf + 1 && ct == cf)
		return true;
	if (rt == rf && ct == cf - 1)
		return true;
	if (rt == rf && ct == cf + 1)
		return true;
	if (rt == rf - 1 && ct == cf - 1)
		return true;
	if (rt == rf + 1 && ct == cf + 1)
		return true;
	if (rt == rf + 1 && ct == cf - 1)
		return true;
	if (rt == rf - 1 && ct == cf + 1)
		return true;
	return false;
}

