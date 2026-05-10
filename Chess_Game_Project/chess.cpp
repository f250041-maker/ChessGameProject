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

void piece::colorSetter(string c) { 
	color = c;
}

string piece::colorGetter() { 
	return color;
}
int returnRowIndex(char row) { //newly added 
	if (row < '1' || row > '8')
		return -1;
	return row - '1';
}

int returnColIndex(char col) {// newly added                      
	if (col < 'a' || col> 'h') 
		return -1;
	return col - 'a';
}

bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board) 
{
	int ct = returnColIndex(toCol);
	int rt = returnRowIndex(toRow);
	int cf = returnColIndex(fromCol);
	int rf = returnRowIndex(fromRow);
	//boundary check
	if (ct <= -1 || ct >= 8 || rt <= -1 || rt >= 8) 
		return false;
	//same square check 
	if (rf == rt && cf == ct) 
		return false;
	// empty starting position check (if user enters something by mistake)
	if (board.grid[rf][cf] == nullptr)
		return false;
	// checking if destination is empty 
	if (board.grid[rt][ct] == nullptr)
		return true;  
	// party check (same or enemy)
	if (board.grid[rt][ct]->colorGetter() == board.grid[rf][cf]->colorGetter())
		return false;
	return true; // if block is not empty and of enemy then yess we'll move there
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
bool Pawn::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) 
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
			else {
				if (rt - rf != 1) {
					cout << "Pawn can move only 1 step forward." << endl;
					return false;
				}
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
			else {
				if (rf - rt != 1) {
					cout << "Pawn can move only 1 step forward." << endl;
					return false;
				}
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

bool Knight::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) 
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

bool King::isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board)
{
	if (doubleCheck(fromRow, fromCol, toRow, toCol, board) == false)
		return false;
	// valid movement
	int ct = returnColIndex(toCol);
	int rt = returnRowIndex(toRow);
	int cf = returnColIndex(fromCol);
	int rf = returnRowIndex(fromRow);
	bool Valid = false;
	if (rt == rf - 1 && ct == cf)
		Valid = true;
	if (rt == rf + 1 && ct == cf)
		Valid = true;
	if (rt == rf && ct == cf - 1)
		Valid = true;
	if (rt == rf && ct == cf + 1)
		Valid = true;
	if (rt == rf - 1 && ct == cf - 1)
		Valid = true;
	if (rt == rf + 1 && ct == cf + 1)
		Valid = true;
	if (rt == rf + 1 && ct == cf - 1)
		Valid = true;
	if (rt == rf - 1 && ct == cf + 1)
		Valid = true;
	// if can't pass any of these 8 checks, have no right to move to InCheck condition :)
	if (Valid == false)
		return false;
	else {
		// check if destination is safe for king
		bool notSafe = board.isInCheck(toRow, toCol, this->colorGetter()); // newly added
		if (notSafe) {
			cout << "ALERT !! King can't move into check" << endl;
			return false;
		}
		else
			return true;
	}
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

bool Board::isInCheck(char toRow, char toCol, string clr) // newly added
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; i < 8; j++) {
			if (grid[i][j] != nullptr && grid[i][j]->colorGetter() != clr) { // ensures square isn't empty and it's from enemy's color
				char fromRow = i + '1';
				char fromCol = 'a' + j;
				bool isValid = grid[i][j]->isValidMove(fromRow, fromCol, toRow, toCol, *this);
				if (isValid) {
					return true; // opponent may capture king, so nope king can't move there
				}
			}
		}
	}
	return false; // only if all enemy pieces in 8 by 8 grid can't capture king 
}

bool Board::isCheckMate(string clr) // newly added
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (grid[i][j] != nullptr && grid[i][j]->colorGetter() == clr) {
				char fromRow = i + '1';
				char fromCol = 'a' + j;
				for (int x = 0; x < 8; x++) {
					for (int y = 0; y < 8; y++) {
						char toRow = '1' + x;
						char toCol = 'a' + y;
						bool Valid = grid[i][j]->isValidMove(fromRow, fromCol, toRow, toCol, *this);
						if (Valid) {
							return false; // there's atleast one possible move 
						}
					}
				}
			}
		}
	}
	return true; // no escape (Check Mate)
}
