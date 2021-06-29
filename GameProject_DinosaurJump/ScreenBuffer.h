#pragma once
#include<iostream>
#include<Windows.h>
#include<string>

using namespace std;

#define SCR_WIDTH 80
#define SCR_HEIGHT 30

class ScreenBuffer
{
	//double buffering, 화면 깜빡 거림을 해결,
	//지금까지는 화면에 바로 그렸으나 이제 부터는 back_buffer에 먼저 저장 후 front_buffer와 다른 부분만 그림
private:
	char front_buffer[SCR_HEIGHT][SCR_WIDTH]; //현재 화면에 보여지는 곳
	char back_buffer[SCR_HEIGHT][SCR_WIDTH]; //앞으로 보여질 내용을 저장할 곳
	COORD loc = {0,0};
public:
	ScreenBuffer();
	void DinoLoc(COORD loc);
	void render();
	void drawToBackBuffer(const int x, const int y, const char image);
	void drawToBackBuffer(const int x, const int y, const string image);
};