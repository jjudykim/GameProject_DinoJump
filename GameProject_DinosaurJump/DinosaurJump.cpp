#include"GameHandler.h"

int main()
{
	GameObject Dino({ 10, 10 }, "/ '<')/");
	vector<GameObject> hurdle;
	GameHandler game;

	bool gameContinue = false;
	game.initGameField();

	while (true)
	{
		//게임을 만들기 위한 4단계

		// 1. Game timing ===============================
		game.gameTiming();

		// 2. Get Input ==================================
  		game.controlDino(Dino, gameContinue);

		// 3. Game Logic ==================================
		if (gameContinue == false) game.beforeGameStart();
		else
		{
			game.gameLogic(hurdle);
		}

		// 4. Render output =================================
		game.printScreen(Dino, hurdle);
	}
}