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
	int scoreNum = 0;


	//�߷� ��������
	float y = 0.0f;
	float gravity = 0.0f; // �߷´�����
	int direction = 0; // 0:��������, 1: ������, 2: �ٿ���
	//������
	const float jump_speed = 0.2f; //���� �ӵ�
	const float jump_accell = 0.01f; //���� ����
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
