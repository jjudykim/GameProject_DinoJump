#pragma once
#include<iostream>
#include<Windows.h>
#include<string>

using namespace std;

#define SCR_WIDTH 80
#define SCR_HEIGHT 30

class ScreenBuffer
{
	//double buffering, ȭ�� ���� �Ÿ��� �ذ�,
	//���ݱ����� ȭ�鿡 �ٷ� �׷����� ���� ���ʹ� back_buffer�� ���� ���� �� front_buffer�� �ٸ� �κи� �׸�
private:
	char front_buffer[SCR_HEIGHT][SCR_WIDTH]; //���� ȭ�鿡 �������� ��
	char back_buffer[SCR_HEIGHT][SCR_WIDTH]; //������ ������ ������ ������ ��
	COORD loc = {0,0};
public:
	ScreenBuffer();
	void DinoLoc(COORD loc);
	void render();
	void drawToBackBuffer(const int x, const int y, const char image);
	void drawToBackBuffer(const int x, const int y, const string image);
};