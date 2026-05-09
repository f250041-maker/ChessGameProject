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
int returnRowIndex(char row) //check added
{
	if (row < '1' || row > '8')
	{
		return -1;
	}
	return 8 - (row- '0');
} 

int returnColIndex(char col) 
{                              // newly added //check added
	if (col < 'a' || col> 'h') {
		return -1;
	}
	return col - 'a';
}
bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board) // newly added
{
	// out of bound check
	int ct = returnColIndex(toCol);
	int rt = returnRowIndex(toRow);
	int cf = returnColIndex(fromCol);
	int rf = returnRowIndex(fromRow);
	if (ct <= -1 || ct >= 8 || rt <= -1 || rt >= 8) //boundary check
		return false;

	if (rf == rt && cf == ct) //same square check (newly added)
		return false;
	// empty starting position check 
	if (board.grid[rf][cf] == nullptr)
		return false;

	if (board.grid[rt][ct] == nullptr)
		return true;  // Empty square is valid to move to
	// party check
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
	bool rookMove = false;
	if (fc == tc && fr != tr)
	{
		rookMove = true;
	}
	else if (fr == tr && fc != tc)
	{
		rookMove = true;
	}
	else
		return false;
	bool Check = doubleCheck(fromRow, fromCol, toRow, toCol, board);
	if (Check && rookMove)
	{
		//horizontal moves
		if (fr == tr)
		{
			int step;
			if (tc > fc)
			{
				step = 1; //right move
			}
			else
			{
				step = -1;//left  move
			}
			for (int j = fc + step; j != tc; j += step)
			{
				if (board.grid[fr][j] != nullptr)
					return false;
			}
		}
		//vertical moves
		else if (fc == tc)
		{
			int step;
			if (tr > fr)
			{
				step = 1;//move up
			}
			else
			{
				step = -1;//move down
			}
			for (int row = fr + step; row != tr; row += step)
			{
				if (board.grid[row][fc] != nullptr)
					return false;
			}
		}
		else
			return false;
		return true;
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
	if (clr == "black" || clr == "Black" || clr == "BLACK") {
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

bool Bishop::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board)
{
	int fr = returnRowIndex(fromRow);
	int fc = returnColIndex(fromCol);
	int tr = returnRowIndex(toRow);
	int tc = returnColIndex(toCol);
	//boundary check
	//color check
	//move check
	bool Check = doubleCheck(fromRow, fromCol, toRow, toCol, board);

	bool isDiagonal = false;
	if (fr != tr && fc != tc)
	{
		isDiagonal = true;
	}
	else
	{
		isDiagonal = false;
		return false;
	}

	if (Check && isDiagonal)
	{
		//diagonal moves

		int rowStep, colStep;
		if (tr > fr)
		{
			rowStep = 1;
		}
		else
			rowStep = -1;

		if (tc > fc)
		{
			colStep = 1;
		}
		else
			colStep = -1;
		int row = fr + rowStep;
		int col = fc + colStep;
		while (row != tr && col != tc)
		{
			if (board.grid[row][col] != nullptr)
			{
				return false;
			}
			row += rowStep;
			col += colStep;
		}
		return true;
	}
	else
		return false;
}
bool Queen::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board)
{

	int fr = returnRowIndex(fromRow);
	int fc = returnColIndex(fromCol);
	int tr = returnRowIndex(toRow);
	int tc = returnColIndex(toCol);
	//boundary check
	//color check
	//move check
	bool Check = doubleCheck(fromRow, fromCol, toRow, toCol, board);
	if (fr == tr && fc == tc) //same square check
		return false;
	bool bishopMove = false;
	bool rookMove = false;
	if (fr != tr && fc != tc)
	{
		bishopMove = true;
		rookMove = false;
	}
	else if (fr == tr && fc != tc)
	{
		bishopMove = false;
		rookMove = true;
	}
	else if (fc == tc && fr != tr)
	{
		bishopMove = false;
		rookMove = true;
	}
	else
		return false;
	if (Check)
	{
		if (rookMove)
		{
			//horizontal moves
			if (fr == tr)
			{
				int step;
				if (tc > fc)
				{
					step = 1; //right move
				}
				else
				{
					step = -1;//left  move
				}
				for (int j = fc + step; j != tc; j += step)
				{
					if (board.grid[fr][j] != nullptr)
						return false;
				}
			}
			//vertical moves
			else if (fc == tc)
			{
				int step;
				if (tr > fr)
				{
					step = 1;//move up
				}
				else
				{
					step = -1;//move down
				}
				for (int row = fr + step; row != tr; row += step)
				{
					if (board.grid[row][fc] != nullptr)
						return false;
				}
			}
			else
				return false;
			return true;
		}
		else if (bishopMove)
		{
			int rowStep, colStep;
			if (tr > fr)
			{
				rowStep = 1;
			}
			else
				rowStep = -1;

			if (tc > fc)
			{
				colStep = 1;
			}
			else
				colStep = -1;
			int row = fr + rowStep;
			int col = fc + colStep;
			while (row != tr && col != tc)
			{
				if (board.grid[row][col] != nullptr)
				{
					return false;
				}
				row += rowStep;
				col += colStep;
			}
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
