#include<ctime>
#include"GameHandler.h"

GameHandler::GameHandler()
{
	CONSOLE_CURSOR_INFO cur_info;
	cur_info.dwSize = 1; //커서의 높이를 셀 높이의 1%로 설정
	cur_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);

	hurdles[0].append("X.X");
	hurdles[0].append(".XX");
	hurdles[0].append("XXX");

	hurdles[1].append("X..");
	hurdles[1].append("X.X");
	hurdles[1].append("XXX");

	hurdles[2].append("...");
	hurdles[2].append(".XX");
	hurdles[2].append(".XX");

	hurdles[3].append(".X.");
	hurdles[3].append(".X.");
	hurdles[3].append(".X.");

	currentHurdle = rand() % 4;
	currentX = feildWidth-3;
	currentY = 8;
	speed = INIT_SPEED;
	speedCounter = 0;
	fasterPlay = false;

	y = y_base;

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
	jumpProcess();
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (gameContinue == false) gameContinue = true;
		doJump();
	}
	COORD temp = Dino.getLoc();
	temp.Y = y + Dino.getLoc().Y;
	Dino.setLoc(temp);


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

// ====================== 점프 내일 다시 하자.... ===========================
// https://m.blog.naver.com/push1104/220861525013
// 참조해서 물리엔진 다시 구현해보기
// =========================================================================

void GameHandler::doJump()
{
	direction = 1;
	gravity = jump_speed; // gravity = 0.2f;
}

void GameHandler::jumpProcess()
{
	switch (direction)
	{
		case 0:
		{
			y = y_base;
		}

		case 1: // up
		{
			y -= gravity; 
			/*if (gravity <= 0.0f) direction = 2; */
			//else 
			gravity -= jump_accell;
		}
		break;

		//case 2: // down
		//{
		//	y += gravity;
		//	if (y < y_base)	gravity -= jump_accell;
		//	else
		//	{
		//		y = y_base;
		//	}	
		//}
		//break;
	}

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
					const COORD hurdlePos = { currentX + x, currentY + y };
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), hurdlePos);
					cout << "■";
				}
			}

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2, 3});
			cout.width(6);
			cout.fill('0');
			cout << scoreNum;
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
	scoreNum++;
}

void GameHandler::gameTiming()
{
	Sleep(10); // Game tick
	speedCounter++;
	fasterPlay = (speedCounter >= speed);
}