#pragma once
#include"GameObject.h"

class GameHandler
{

private:
	const int feildWidth = 80;
	const int feildHeigth = 13;
	const int INIT_SPEED = 20;

	char* gameField = nullptr;

	int speed; // ���� ���ǵ�, ���� ���� ���� ������ �����
	int speedCounter; //Counting game ticks
	string hurdles[4];

	int currentHurdle, currentX, currentY;
	bool fasterPlay;


public:
	GameHandler();
	void initGameField();
	void beforeGameStart();
	void backgroundImage();
	void controlDino(GameObject& Dino, bool& gameContinue);
	void printScreen(GameObject& Dino);
	void gameLogic();
	void gameTiming();
	void createHurdle(vector<GameObject>& Hurdle);

};
