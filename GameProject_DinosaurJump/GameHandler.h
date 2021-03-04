#pragma once
#include"GameObject.h"

class GameHandler
{

private:
	const int feildWidth = 80;
	const int feildHeigth = 13;
	const int INIT_SPEED = 20;

	char* gameField = nullptr;

	int speed; // 게임 스피드, 값이 작을 수록 빠르고 어려움
	int speedCounter; //Counting game ticks
	string hurdles[4];

	int currentHurdle, currentX, currentY;
	bool fasterPlay;
	int scoreNum = 0;


	//중력 물리엔진
	float y = 0.0f;
	float gravity = 0.0f; // 중력느낌용
	int direction = 0; // 0:정지상태, 1: 점프중, 2: 다운중
	//설정값
	const float jump_speed = 0.2f; //점프 속도
	const float jump_accell = 0.01f; //점프 가속
	const float y_base = 0.0f;


public:
	GameHandler();
	void initGameField();
	void beforeGameStart();
	void backgroundImage();
	void controlDino(GameObject& Dino, bool& gameContinue);
	void doJump();
	void jumpProcess();
	void printScreen(GameObject& Dino);
	void gameLogic();
	void gameTiming();
	void createHurdle(vector<GameObject>& Hurdle);

};
