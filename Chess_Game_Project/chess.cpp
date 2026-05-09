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