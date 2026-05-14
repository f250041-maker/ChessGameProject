#pragma once
#include<iostream>
#include<string>
#include <exception>
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
	void colorSetter(string c);
	string colorGetter();
	piece(string c, const char& s, const char p[]); //newly added
	virtual ~piece(); //newly added
	virtual bool isPawn(); //newly added
	virtual void markAsMoved();  // Empty for non-pawns
};
class Pawn : public piece {
public:
	bool isFirstMove;
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override;
	friend int returnRowIndex(char row);
	friend int returnColIndex(char col);
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board);//newly added
	Pawn(const string c, const char& s, const char p[]); //newly added
	bool isPawn() override;//newly added
	void markAsMoved() override; //newly added
};
class Rook : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override;
	friend int returnRowIndex(char row);
	friend int returnColIndex(char col);
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board);
	Rook(const string c, const char& s, const char p[]);
};
class Knight : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override;
	friend int returnRowIndex(char row);
	friend int returnColIndex(char col);
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board);
	Knight(const string c, const char& s, const char p[]);
};
class Bishop : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override;
	friend int returnRowIndex(char row);
	friend int returnColIndex(char col);
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board);
	Bishop(const string c, const char& s, const char p[]);
};
class Queen : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override;
	friend int returnRowIndex(char row);
	friend int returnColIndex(char col);
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board);
	Queen(const string c, const char& s, const char p[]);
};
class King : public piece {
public:
	bool isValidMove(char fromRow, char fromCol, char toRow, char toCol, Board& board) override;
	friend int returnRowIndex(char row);
	friend int returnColIndex(char col);
	friend bool doubleCheck(char fromRow, char fromCol, char toRow, char toCol, Board& board);
	King(const string c, const char& s, const char p[]);
};
class Board {
	string currentTurn;//used in movePiece,printBoard and checkMate
public:
	Board();//new added
	~Board();//new added
	piece* grid[row][col];
	string turnGetter(); //newly added
	bool movePiece();
	void setupBoard();
	void printBoard()const;
	bool isInCheck(char toRow, char toCol, string clr);
	bool isCheckMate(string clr);
	friend int returnRowIndex(char row);
	friend int returnColIndex(char col);
};
