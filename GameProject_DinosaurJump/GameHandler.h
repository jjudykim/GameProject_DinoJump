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
	string hurdlesImage[4];

	int currentHurdle, currentX, currentY;
	bool fasterPlay;
	int scoreNum = 0;


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
	COORD moveHurdle(int i, vector<GameObject>& hurdle);
	void gameLogic(vector<GameObject>& hurdle);
	void gameTiming();
	void createHurdle(vector<GameObject>& hurdle);

};
