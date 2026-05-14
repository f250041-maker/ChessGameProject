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
		if (board.grid[rt][ct] == nullptr) // destination is free
		{
			if (ct != cf)  // column changed → not straight forward
				return false;
			if (isFirstMove) {
				if (rt - rf != 1 && rt - rf != 2)
					return false;
				if (rt - rf == 2 && board.grid[rf + 1][cf] != nullptr) // destination is empty but right in front of pawn there's a piece ( can't move )
					return false;
			}
			else {
				if (rt - rf != 1)
					return false;
			}
		}
		else { // diagonal capture 
			if (rt == rf + 1 && ct == cf - 1) {
				if (board.grid[rt][ct]->colorGetter() != clr) // enemy piece
					return true;
				return false;
			}
			if (rt == rf + 1 && ct == cf + 1) {
				if (board.grid[rt][ct]->colorGetter() != clr)  // enemy piece
					return true;
				return false;
			}
			return false;
		}
	}
	else if (clr == "white" || clr == "White" || clr == "WHITE")
	{
		if (rf == 6)
			isFirstMove = true;
		else
			isFirstMove = false;
		if (board.grid[rt][ct] == nullptr)
		{
			if (ct != cf)  // column changed → not straight forward
				return false;
			if (isFirstMove) {
				if (rf - rt != 1 && rf - rt != 2)
					return false;
				if (rf - rt == 2 && board.grid[rf - 1][cf] != nullptr)
					return false;
			}
			else {
				if (rf - rt != 1)
					return false;
			}
		}
		else {
			if (rt == rf - 1 && ct == cf - 1) {
				if (board.grid[rt][ct]->colorGetter() != clr)
					return true;
				return false;
			}
			if (rt == rf - 1 && ct == cf + 1) {
				if (board.grid[rt][ct]->colorGetter() != clr)
					return true;
				return false;
			}
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
	int rowDiff = tr - fr;
	int colDiff = tc - fc;    //for diagonal check 
	if (rowDiff != colDiff && rowDiff != -colDiff) {
		return false;  
	}
	if (Check ) {
		//diagonal moves
		int rowStep, colStep;
		if (tr > fr)
			rowStep = 1;
		else
			rowStep = -1;

		if (tc > fc)
			colStep = 1;
		else
			colStep = -1;
		int row = fr + rowStep;
		int col = fc + colStep;
		while (row != tr && col != tc) {
			if (board.grid[row][col] != nullptr) {
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
	int rowDiff = tr - fr;
	int colDiff = tc - fc;    //for diagonal check
	if (fr == tr && fc != tc)
		rookMove = true;
	else if (fc == tc && fr != tr)
		rookMove = true;
	else if (rowDiff == colDiff || rowDiff == -colDiff)
		bishopMove = true;
	else
		return false;
	if (Check)
	{
		if (rookMove)
		{
			//horizontal moves
			if (fr == tr) {
				int step;
				if (tc > fc)
					step = 1; //right move
				else
					step = -1;//left  move
				for (int j = fc + step; j != tc; j += step) {
					if (board.grid[fr][j] != nullptr)
						return false;
				}
			}
			//vertical moves
			else if (fc == tc)
			{
				int step;
				if (tr > fr)
					step = 1;//move up
				
				else
					step = -1;//move down
				for (int row = fr + step; row != tr; row += step) {
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
				rowStep = 1;
			else
				rowStep = -1;

			if (tc > fc)
				colStep = 1;
			else
				colStep = -1;
			int row = fr + rowStep;
			int col = fc + colStep;
			while (row != tr && col != tc) {
				if (board.grid[row][col] != nullptr) {
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
		for (int j = 0; j < 8; j++) {
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

Board::Board()
{
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			grid[i][j] = nullptr;
		}
	}
	currentTurn = "white";//first turn is of white
	setupBoard();//will create memory with new
}
piece::piece(string c, const char& s, const char p[])
{
	color = c;
	symbol = s;
	for (int i = 0;i < 3;i++)
	{
		position[i] = p[i];
	}
}
Pawn::Pawn(string c, const char& s, const char p[]) :piece(c, s, p)
{
	isFirstMove = true;
}
Rook::Rook(const string c, const char& s, const char p[]) :piece(c, s, p) {}
Bishop::Bishop(const string c, const char& s, const char p[]) :piece(c, s, p) {}
Queen::Queen(const string c, const char& s, const char p[]) :piece(c, s, p) {}
King::King(const string c, const char& s, const char p[]) :piece(c, s, p) {}
Knight::Knight(const string c, const char& s, const char p[]) :piece(c, s, p) {}
Board::~Board()
{
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			if (grid[i][j] != nullptr)
			{
				delete grid[i][j];
				grid[i][j] = nullptr;
			}
		}
	}
}
piece::~piece() {}//ensures the deletion of derived class objects
void Board::setupBoard()
{//Black pieces
	grid[0][0] = new Rook("black", 'r', "1a");
	grid[0][1] = new Knight("black", 'n', "1b"); //n used for knight
	grid[0][2] = new Bishop("black", 'b', "1c");
	grid[0][3] = new Queen("black", 'q', "1d");
	grid[0][4] = new King("black", 'k', "1e");
	grid[0][5] = new Bishop("black", 'b', "1f");
	grid[0][6] = new Knight("black", 'n', "1g");
	grid[0][7] = new Rook("black", 'r', "1h");

	grid[1][0] = new Pawn("black", 'p', "2a");
	grid[1][1] = new Pawn("black", 'p', "2b");
	grid[1][2] = new Pawn("black", 'p', "2c");
	grid[1][3] = new Pawn("black", 'p', "2d");
	grid[1][4] = new Pawn("black", 'p', "2e");
	grid[1][5] = new Pawn("black", 'p', "2f");
	grid[1][6] = new Pawn("black", 'p', "2g");
	grid[1][7] = new Pawn("black", 'p', "2h");
	//White pieces
	grid[6][0] = new Pawn("white", 'P', "7a");
	grid[6][1] = new Pawn("white", 'P', "7b");
	grid[6][2] = new Pawn("white", 'P', "7c");
	grid[6][3] = new Pawn("white", 'P', "7d");
	grid[6][4] = new Pawn("white", 'P', "7e");
	grid[6][5] = new Pawn("white", 'P', "7f");
	grid[6][6] = new Pawn("white", 'P', "7g");
	grid[6][7] = new Pawn("white", 'P', "7h");

	grid[7][0] = new Rook("white", 'R', "8a");
	grid[7][1] = new Knight("white", 'N', "8b");
	grid[7][2] = new Bishop("white", 'B', "8c");
	grid[7][3] = new Queen("white", 'Q', "8d");
	grid[7][4] = new King("white", 'K', "8e");
	grid[7][5] = new Bishop("white", 'B', "8f");
	grid[7][6] = new Knight("white", 'N', "8g");
	grid[7][7] = new Rook("white", 'R', "8h");
}
void Board::printBoard()const
{
	cout << "  a  b  c  d  e  f  g  h" << endl;
	for (int i = 0;i < 8;i++)
	{
		cout << i + 1 << " ";
		for (int j = 0;j < 8;j++)
		{
			if (grid[i][j] != nullptr)
			{
				cout << grid[i][j]->symbolGetter() << "  ";
			}
			else
				cout << "x  ";
		}
		cout << endl;
	}
	cout << "  a  b  c  d  e  f  g  h" << endl;
	cout << "\tcurrent turn: " << currentTurn << endl;
}
bool piece::isPawn() { return false; }
bool Pawn::isPawn() { return true; }
void piece::markAsMoved() {}
void Pawn::markAsMoved() { isFirstMove = false; }
string Board::turnGetter() // newly added
{
	return currentTurn;
}
bool Board::movePiece()
{
	cout << "Enter your inital position (row first column second) e.g 1a)" << endl;
	string from, to;
	cin >> from;
	cout << "Now enter your target position (row first column second) e.g 2a)" << endl;
	cin >> to;
	// added exception for wrong user input 
	if (from.length() != 2 || to.length() != 2)
		throw invalid_argument("Input must be exactly 2 characters like '2a' or '7e'");

	int fr, tr, fc, tc;
	fr = returnRowIndex(from[0]);
	tr = returnRowIndex(to[0]);
	fc = returnColIndex(from[1]);
	tc = returnColIndex(to[1]);
	if (fr == -1 || fc == -1 || tr == -1 || tc == -1) // newly added
		throw invalid_argument("Invalid position entered!");

	if (grid[fr][fc] == nullptr) {  
		cout << "No piece at that position!" << endl;
		return false;
	}
	if (grid[fr][fc]->colorGetter() != currentTurn)
	{
		cout << "Wrong piece! It's " << currentTurn << "'s turn" << endl;
		return false;
	}
	bool isValid = grid[fr][fc]->isValidMove(from[0], from[1], to[0], to[1], *this);//*this for Board&
	if (isValid)
	{
		if (grid[tr][tc] != nullptr) { // newly updated
			if (grid[tr][tc]->symbolGetter() == 'k' ||
				grid[tr][tc]->symbolGetter() == 'K')
			{
				cout << "King captured! Game Over!" << endl;
				delete grid[tr][tc];
				grid[tr][tc] = nullptr;
				exit(0);
			}
			delete grid[tr][tc];
		}
		piece* move = grid[fr][fc];
		grid[tr][tc] = move;
		grid[fr][fc] = nullptr;

		char newPos[3];
		newPos[0] = tr + '1';
		newPos[1] = tc + 'a';
		newPos[2] = '\0';
		move->positionSetter(newPos);  //position updated
		// specially for first move and promotion of pawn, rest of pieces simply skip this block
		if (move->isPawn()) { // newly added
			char choice=' ';
			if ((currentTurn == "white" && tr == 0) || (currentTurn == "black" && tr == 7)) {
				cout << "Pawn Promotion!" << endl;
				if (currentTurn == "white") {
					cout << "Knight - N \t Queen - Q \t Bishop - B \t Rook - R" << endl;
					cout << "Enter choice : ";
					cin >> choice;
					while (!(choice >= 'A' && choice <= 'Z')) {
						cout << "Re-enter : ";
						cin >> choice;
					}
					delete grid[tr][tc];
					grid[tr][tc] = nullptr;
					newPos[0] = tr + '1';
					newPos[1] = tc + 'a';
					newPos[2] = '\0';
				}
				else if (currentTurn == "black") {
					cout << "Knight - n \t Queen - q \t Bishop - b \t Rook - r" << endl;
					cout << "Enter choice : ";
					cin >> choice;
					while (!(choice >= 'a' && choice <= 'z')) {
						cout << "Re-enter : ";
						cin >> choice;
					}
					delete grid[tr][tc];
					grid[tr][tc] = nullptr;
					newPos[0] = tr + '1';
					newPos[1] = tc + 'a';
					newPos[2] = '\0';
				}
				char sym;
				if (choice == 'Q' || choice == 'q') {
					if (currentTurn == "white")
						sym = 'Q';
					else
						sym = 'q';
					grid[tr][tc] = new Queen(currentTurn, sym, newPos);
				}
				else if (choice == 'N' || choice == 'n') {
					if (currentTurn == "white")
						sym = 'N';
					else
						sym = 'n';
					grid[tr][tc] = new Knight(currentTurn, sym, newPos);
				}
				else if (choice == 'R' || choice == 'r') {
					if (currentTurn == "white")
						sym = 'R';
					else
						sym = 'r';
					grid[tr][tc] = new Rook(currentTurn, sym, newPos);
				}
				else if (choice == 'B' || choice == 'b') {
					if (currentTurn == "white")
						sym = 'B';
					else
						sym = 'b';
					grid[tr][tc] = new Bishop(currentTurn, sym, newPos);
				}
				move = grid[tr][tc];
			}
			else
				move->markAsMoved();
		}
		// swicth turning
		if (currentTurn == "white") {
			currentTurn = "black";
		}
		else
			currentTurn = "white";
		return true;
	}
	else {
		cout << "Invalid move ,try again" << endl;
		return false;
	}
}
