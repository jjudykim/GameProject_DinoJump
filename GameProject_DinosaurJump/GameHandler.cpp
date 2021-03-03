#include<ctime>
#include"GameHandler.h"

GameHandler::GameHandler()
{
	CONSOLE_CURSOR_INFO cur_info;
	cur_info.dwSize = 1; //커서의 높이를 셀 높이의 1%로 설정
	cur_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);

	hurdles[0].append(".X..");
	hurdles[0].append(".X.X");
	hurdles[0].append(".XXX");

	hurdles[1].append("X..X");
	hurdles[1].append("X.XX");
	hurdles[1].append(".XXX");

	hurdles[2].append("....");
	hurdles[2].append(".XX.");
	hurdles[2].append(".XX.");

	hurdles[3].append(".X..");
	hurdles[3].append(".X..");
	hurdles[3].append(".X..");

	currentHurdle = rand() % 4;
	currentX = feildWidth;
	currentY = 10;
	speed = INIT_SPEED;
	speedCounter = 0;
	fasterPlay = false;

}

void GameHandler::beforeGameStart()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 17, 3 });
	cout << "==========Welcome to Dino Jump!!=============";

}

void GameHandler::initGameField()
{
	gameField = new char[feildWidth * feildHeigth];

	for (int x = 0; x < feildWidth; x++)
	{
		for (int y = 0; y < feildHeigth; y++)
		{
			if (x == 0)
			{
				if (y == 0) gameField[y * feildWidth + x] = 1;
				else if (y == feildHeigth - 1) gameField[y * feildWidth + x] = 3;
				else gameField[y * feildWidth + x] = 5;
			}
			else if (x == feildWidth - 1)
			{
				if (y == 0) gameField[y * feildWidth + x] = 2;
				else if (y == feildHeigth - 1) gameField[y * feildWidth + x] = 4;
				else gameField[y * feildWidth + x] = 5;
			}
			else if (y == feildHeigth - 3)
			{
				if (x != 0 && x != feildWidth) gameField[y * feildWidth + x] = 6;
			}
			else
			{
				if (y == 0 || y == feildHeigth - 1) gameField[y * feildWidth + x] = 6;
				else gameField[y * feildWidth + x] = 0;
			}
		}
	}
}

//void createHurdle(vector<GameObject>& Hurdle)
//{
//	GameObject temp({ 8, 20 }, "▲");
//	Hurdle.push_back(temp);
//
//}

void GameHandler::backgroundImage()
{

}

void GameHandler::controlDino(GameObject& Dino, bool& gameContinue)
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (gameContinue == false) gameContinue = true;
	}


	/*if (GetAsyncKeyState(VK_SPACE))
	{
		JumpHeight = JumpTime * JumpTime - JumpPower * JumpTime;

		JumpTime += 0.05f;

		if (JumpTime >= JumpPower)
		{
			JumpTime = 0.f;
			JumpHeight = 0.f;
		}
	}*/
}

void GameHandler::printScreen(GameObject& Dino)
{
	for (int x = 0; x < feildWidth; x++)
	{
		for (int y = 0; y < feildHeigth; y++)
		{
			const COORD pos = { x, y };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			if (gameField[y * feildWidth + x] != 0) cout << gameField[y * feildWidth + x];

			const COORD dinoPos = Dino.getLoc();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dinoPos);
			cout << Dino.getImage();

			if (x < 3 && y < 3)
			{
				if (hurdles[currentHurdle][x * 3 + y] == 'X')
				{
					const COORD hurdlePos = { currentX, currentY };
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), hurdlePos);
					cout << "■";
				}
			}

		}
	}
}

void GameHandler::gameLogic()
{
	if (fasterPlay)
	{
		speed--;
		speedCounter = 0;
	}
	currentX--;
}

void GameHandler::gameTiming()
{
	Sleep(10); // Game tick
	speedCounter++;
	fasterPlay = (speedCounter >= speed);
}