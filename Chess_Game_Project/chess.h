#pragma once
#include<iostream>
#include<string>
using namespace std;

const int col = 8;
const int row = 8;
class Board; 
class piece {
	string color;
	char symbol;
	char position[3];
public:
	virtual bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) = 0;
	void symbolSetter(const char s);
	char symbolGetter();
	void positionSetter(const char* p);
	char* positionGetter();
	void colorSetter(string c); // newly added 
	string colorGetter(); // newly added
};
class Pawn : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override; 
	friend int returnRowIndex(char row);  // newly added 
	friend int returnColIndex(char col);  // newly added 
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board); // newly added
};
class Rook : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override;
	friend int returnRowIndex(char row);  // newly added 
	friend int returnColIndex(char col);  // newly added 
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board); // newly added
};
class Knight : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override; 
	friend int returnRowIndex(char row);  // newly added 
	friend int returnColIndex(char col);  // newly added 
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board); // newly added
};
class Bishop : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override; 
	friend int returnRowIndex(char row);  // newly added 
	friend int returnColIndex(char col);  // newly added 
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board); // newly added
};
class Queen : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override; 
	friend int returnRowIndex(char row);  // newly added 
	friend int returnColIndex(char col);  // newly added 
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board); // newly added
};
class King : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override; 
	friend int returnRowIndex(char row);  // newly added 
	friend int returnColIndex(char col);  // newly added 
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board); // newly added
};
class Board {
public:
	piece* grid[row][col]; 
	bool movePiece(); 
	void setupBoard();
	void printBoard();
	bool isInCheck();
	bool isCheckMate();
};
