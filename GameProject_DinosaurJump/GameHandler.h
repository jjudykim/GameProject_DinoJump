#pragma once
#include"GameObject.h"
#include"ScreenBuffer.h"
#include<iomanip>
#include<ctime>
#include<cstdlib>


class GameHandler
{

private:
	const int fieldWidth = 80;
	const int fieldHeigth = 13;
	const int INIT_SPEED = 20;

	ScreenBuffer screenBuffer;
	char* gameField = nullptr;

	int speed; // 게임 스피드, 값이 작을 수록 빠르고 어려움
	int speedCounter; //Counting game ticks
	string hurdlesImage[4];

	int currentHurdle;
	bool fasterPlay;
	int scoreNum = 0;
	string scoreString = "000000";

	//중력 물리엔진
	float jumpY = 0.0f;
	float jumpPower = 0.6f; // 점프속도
	int direction = 0; // 0:정지상태, 1: 점프중, 2: 다운중
	//설정값
	const float gravity = 0.08f; //중력
	const float y_base = 0.0f;

public:
	GameHandler();
	void initGameField();
	void beforeGameStart();
	void backgroundImage();
	void controlDino(GameObject& Dino, bool& gameContinue);
	void jumpProcess();
	void printScreen(GameObject& Dino, vector<GameObject>& hurdle);
	void gameLogic(vector<GameObject>& hurdle);
	void gameTiming();
	void createHurdle(vector<GameObject>& hurdle);
	void moveHurdle(vector<GameObject>& hurdle);

};
