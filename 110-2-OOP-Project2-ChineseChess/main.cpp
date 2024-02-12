#include "GameManager.h"
int main()
{
	
	GameManager game;
	
	while (game.isRunning())
	{
		game.update();
		game.render();
	}
	return EXIT_SUCCESS;
	

}