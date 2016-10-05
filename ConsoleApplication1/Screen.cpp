#include "stdafx.h"
#include "Screen.h"


Screen::Screen()
{
	this->hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleScreenBufferSize(this->hOutput, this->dwBufferSize);
	SetConsoleWindowInfo(this->hOutput, TRUE, &this->rcRegion);
}


Screen::~Screen()
{
}

void Screen::read() {
	ReadConsoleOutput(this->hOutput, (CHAR_INFO *)this->buffer, this->dwBufferSize, this->dwBufferCoord, &this->rcRegion);
}

void Screen::display() {
	WriteConsoleOutput(this->hOutput, (CHAR_INFO *)this->buffer, this->dwBufferSize, this->dwBufferCoord, &this->rcRegion);
}