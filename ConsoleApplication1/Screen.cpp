#include "stdafx.h"
#include "Screen.h"


Screen::Screen()
{
	this->dwBufferSize = { Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT };
	this->dwBufferCoord = { 0, 0 };
	this->rcRegion = { 0, 0, Screen::SCREEN_WIDTH - 1, Screen::SCREEN_HEIGHT - 1 };
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