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
	//biundary check
	//color check
	//move check
	bool Check = doubleCheck(fromRow, fromCol, toRow, toCol, board);
	if (Check)
	{
		//vertical moves
		string cl = colorGetter();
		if (fc == tc && fr > tr) //move up
		{
			for (int i = fr;i <= tr;i--)
			{
				if ((cl == "black" || cl == "BLACK" || cl == "Black") && fr == 0)
				{
					return false; //boundary check for black
				}
				if (grid[i][tc] == NULL)
				{
					return true;
				}
				else
				{
					if (i != tr && i != fr)
					{
						cout << "there is a piece in the path!" << endl;
						return false;
					}
					else
						return true;
				}
			}
		}
		//move down
		if (fc == tc && fr < tr)
		{
			for (int i = fr;i <= tr;i++)
			{
				if ((cl == "white" || cl == "WHITE" || cl == "White") && fr == 7)
				{
					return false;
				}
				if (grid[i][tc] == NULL)
				{
					return true;
				}
				else
				{
					if (i != tr && i != fr)
					{
						cout << "there is a piece in the path!" << endl;
						return false;
					}
					else
						return true;
				}
			}

		}
		//horizontal moves 
		//move right 0->7
		if (fr == tr && fc < tc)
		{
			if (fc < 7)
			{
				for (int i = fc;i <= tc;i++)
				{
					if (grid[tr][i] == NULL)
					{
						return true;
					}
					else
					{
						if (i == tc)
						{
							return true;
						}
						else if (i != fc && i < tc)
						{
							cout << "there is a piece in the path" << endl;
							return false;
						}
					}
				}
			}
			else
			{
				cout << "cannot move further right" << endl;
				return false;
			}
		}
		//move left 7->0
		if (fr == tr && fc > tc)
		{
			if (fc < 0)
			{
				cout << "cannot move further left" << endl;
				return false;
			}
			else
			{
				for (int i = fc;i <= tc;i--)
				{
					if (grid[tr][i] == NULL)
					{
						return true;
					}
					else
					{
						if (i == tc)
						{
							return true;
						}
						else if (i != fc && i < tc)
						{
							cout << "there is a piece in the path" << endl;
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
