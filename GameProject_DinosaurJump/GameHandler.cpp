#include<ctime>
#include"GameHandler.h"

GameHandler::GameHandler()
{
	CONSOLE_CURSOR_INFO cur_info;
	cur_info.dwSize = 1; //커서의 높이를 셀 높이의 1%로 설정
	cur_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);

	hurdlesImage[0].append("X.X");
	hurdlesImage[0].append(".XX");
	hurdlesImage[0].append("XXX");

	hurdlesImage[1].append("X..");
	hurdlesImage[1].append("X.X");
	hurdlesImage[1].append("XXX");

	hurdlesImage[2].append("...");
	hurdlesImage[2].append(".XX");
	hurdlesImage[2].append(".XX");

	hurdlesImage[3].append(".X.");
	hurdlesImage[3].append(".X.");
	hurdlesImage[3].append(".X.");

	currentHurdle = rand() % 4;
	currentX = feildWidth-3;
	currentY = 8;
	speed = INIT_SPEED;
	speedCounter = 0;
	fasterPlay = false;

	/*y = y_base;*/

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

void GameHandler::backgroundImage()
{

}

void GameHandler::controlDino(GameObject& Dino, bool& gameContinue)
{
	jumpProcess();
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (gameContinue == false) gameContinue = true;
		direction = 1;
	}
	COORD temp = Dino.getLoc();
	temp.Y = jumpY + Dino.getLoc().Y;
	Dino.setLoc(temp);
}

void GameHandler::jumpProcess()
{
	switch (direction)
	{
		case 0:
		{
			jumpPower = 0.6f;
			jumpY = y_base;
		}
		break;

		case 1: // up
		{
			jumpY = y_base;
			jumpY -= jumpPower; 
			if (jumpPower <= 0.0f) direction = 2;
			else 
			jumpPower -= gravity;
		}
		break;

		case 2: // down
		{
			jumpY += jumpPower;
			jumpPower += gravity;
			if (jumpPower > 0.7f) direction = 0;
		}
		break;
	}

}

void GameHandler::printScreen(GameObject& Dino, vector<GameObject>& hurdle)
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
				if (hurdlesImage[currentHurdle][x * 3 + y] == 'X')
				{
					const COORD testHurdlePos = { currentX + x, currentY + y };
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), testHurdlePos);
					cout << "■";
				}
			}

			if (x < 3 && y < 3)
			{
				for (auto i : hurdle)
				{
					if (i.getImage()[x * 3 + y] == 'X')
					{
						const COORD hurdlePos = i.getLoc();
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), hurdlePos);
						cout << "■";
					}
				}
			}

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 3});
			cout.width(6);
			cout.fill('0');
			cout << scoreNum;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 2, 17 });
			cout << "Dino Y : " << Dino.getLoc().Y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 2, 18 });
			cout << "jumpY : " << jumpY;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 2, 19 });
			cout << "jumpPower : " << jumpPower;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 2, 20 });
			cout << "gravity : " << gravity;
		}
	}
}

COORD GameHandler::moveHurdle(int i, vector<GameObject>& hurdle)
{
	COORD hurdlePosTemp = hurdle.at(i).getLoc();
	hurdlePosTemp.X--;

	return hurdlePosTemp;
}

void GameHandler::gameLogic(vector<GameObject>& hurdle)
{
	for (int i = 0; i < hurdle.size(); i++)
	{
		hurdle.at(i).setLoc(moveHurdle(i, hurdle));
	}
	if (fasterPlay)
	{
		speed--;
		speedCounter = 0;
	}
	if (scoreNum / 60 == rand() % 10)
	{
		GameObject hurdleTemp({ (SHORT)feildWidth - 3, (SHORT)8 }, hurdlesImage[rand() % 4]);
		hurdle.push_back(hurdleTemp);
	}
	currentX--;
	scoreNum++;
	
}

void GameHandler::gameTiming()
{
	Sleep(10); // Game tick
	speedCounter++;
	fasterPlay = (speedCounter >= speed);
}