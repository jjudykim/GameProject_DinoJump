#include"GameHandler.h"

int main()
{
	GameObject Dino({ 8, 10 }, "��'<')��");
	vector<GameObject> hurdle;
	GameHandler game;

	bool gameContinue = false;
	game.initGameField();

	while (true)
	{
		//������ ����� ���� 4�ܰ�

		// 1. Game timing ===============================
		system("cls");

		// 2. Get Input ==================================
  		game.controlDino(Dino, gameContinue);

		// 3. Game Logic ==================================
		game.printScreen(Dino, hurdle);
		if (gameContinue == false) game.beforeGameStart();
		else
		{
			game.gameLogic(hurdle);
		}


		// 4. Render output =================================

	}
}