#include<ctime>
#include"GameHandler.h"

GameHandler::GameHandler()
{
	CONSOLE_CURSOR_INFO cur_info;
	cur_info.dwSize = 1; //커서의 높이를 셀 높이의 1%로 설정
	cur_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);

	hurdlesImage[0].append("..X");
	hurdlesImage[0].append(".XX");
	hurdlesImage[0].append("XXX");

	hurdlesImage[1].append("X..");
	hurdlesImage[1].append("XXX");
	hurdlesImage[1].append("XXX");

	hurdlesImage[2].append("..X");
	hurdlesImage[2].append(".XX");
	hurdlesImage[2].append(".XX");

	hurdlesImage[3].append("XXX");
	hurdlesImage[3].append(".XX");
	hurdlesImage[3].append(".X.");

	srand((unsigned int)time(nullptr));
	currentHurdle = rand() % 4;
	speed = INIT_SPEED;
	speedCounter = 0;
	fasterPlay = false;

	/*y = y_base;*/

}

void GameHandler::beforeGameStart()
{
	screenBuffer.drawToBackBuffer(17, 2, "==========Welcome to Dino Jump!!=============");
}

void GameHandler::initGameField()
{
	gameField = new char[fieldWidth * fieldHeigth];

	for (int x = 0; x < fieldWidth; x++)
	{
		for (int y = 0; y < fieldHeigth; y++)
		{
			if (x == 0)
			{
				if (y == 0) gameField[y * fieldWidth + x] = 1;                                   // 1 : ┌
				else if (y == fieldHeigth - 1) gameField[y * fieldWidth + x] = 3;                // 3 : └
				else gameField[y * fieldWidth + x] = 5;                                          // 5 : │
			}
			else if (x == fieldWidth - 1)
			{
				if (y == 0) gameField[y * fieldWidth + x] = 2;                                   // 2 : ┐
				else if (y == fieldHeigth - 1) gameField[y * fieldWidth + x] = 4;                // 4 : ┘
				else gameField[y * fieldWidth + x] = 5;
			}
			else if (y == fieldHeigth - 3)
			{
				if (x != 0 && x != fieldWidth) gameField[y * fieldWidth + x] = 6;                // 6 : ─
			}
			else
			{
				if (y == 0 || y == fieldHeigth - 1) gameField[y * fieldWidth + x] = 6;            
				else gameField[y * fieldWidth + x] = 0;                                           // 0 :  
			}
		}
	}
}

void GameHandler::backgroundImage()
{

}

void GameHandler::controlDino(GameObject& Dino, bool& gameContinue)
{
	COORD temp = Dino.getLoc();
	jumpProcess();
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (gameContinue == false) gameContinue = true;
		direction = 1;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if(temp.X+1 != fieldWidth) temp.X++;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if(temp.X-1 != 0) temp.X--;
	}
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
	for (int x = 0; x < fieldWidth; x++)
	{
		for (int y = 0; y < fieldHeigth; y++)
		{
			if (gameField[y * fieldWidth + x] != 0) screenBuffer.drawToBackBuffer(x, y, gameField[y * fieldWidth + x]);
			screenBuffer.drawToBackBuffer(Dino.getLoc().X, Dino.getLoc().Y, Dino.getImage());
			screenBuffer.DinoLoc(Dino.getLoc());
			
			scoreString.replace(scoreString.length() - to_string(scoreNum).length(), to_string(scoreNum).length(), to_string(scoreNum));
			screenBuffer.drawToBackBuffer(2, 2, scoreString);

			// jump test
			/*screenBuffer.drawToBackBuffer(2, 17, "Dino Y : " + ('0' + Dino.getLoc().Y));
			screenBuffer.drawToBackBuffer(2, 18, "jumpY : " + ('0' + jumpY));
			screenBuffer.drawToBackBuffer(2, 19, "jumpPower : " + ('0' + jumpPower));
			screenBuffer.drawToBackBuffer(2, 20, "gravity : " + ('0' + gravity));*/
		}
	}
	
	for (int i = 0; i < hurdle.size(); i++)
	{
		for (int px = 0; px < 3; px++)
			for (int py = 0; py < 3; py++)
				if (hurdle.at(i).getImage()[px * 3 + py] == 'X')
					screenBuffer.drawToBackBuffer(hurdle.at(i).getLoc().X + px, hurdle.at(i).getLoc().Y + py, "X");
	}
	
	screenBuffer.render();
}

void GameHandler::createHurdle(vector<GameObject>& hurdle)
{
	GameObject hurdleTemp({ (SHORT)fieldWidth - 3, (SHORT)8 }, hurdlesImage[currentHurdle]);
	hurdle.push_back(hurdleTemp);
	currentHurdle = rand() % 4;
}

void GameHandler::moveHurdle(vector<GameObject>& hurdle)
{
	for (int i = 0; i < hurdle.size(); i++)
	{
		COORD hurdleLocTemp{ hurdle.at(i).getLoc().X - 1, hurdle.at(i).getLoc().Y };
		if (hurdleLocTemp.X != 0) hurdle.at(i).setLoc(hurdleLocTemp);
		else hurdle.erase(hurdle.begin() + i);
	}
}

void GameHandler::gameLogic(vector<GameObject>& hurdle)
{
	if (rand() % 25 == 1) createHurdle(hurdle);
	moveHurdle(hurdle);

	if (fasterPlay)
	{
		speed--;
		speedCounter = 0;
	}
	scoreNum++;
}

void GameHandler::gameTiming()
{
	Sleep(0); // Game tick
	speedCounter++;
	fasterPlay = (speedCounter >= speed);
}