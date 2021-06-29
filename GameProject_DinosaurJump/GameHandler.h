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

	int speed; // ���� ���ǵ�, ���� ���� ���� ������ �����
	int speedCounter; //Counting game ticks
	string hurdlesImage[4];

	int currentHurdle;
	bool fasterPlay;
	int scoreNum = 0;
	string scoreString = "000000";

	//�߷� ��������
	float jumpY = 0.0f;
	float jumpPower = 0.6f; // �����ӵ�
	int direction = 0; // 0:��������, 1: ������, 2: �ٿ���
	//������
	const float gravity = 0.08f; //�߷�
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
