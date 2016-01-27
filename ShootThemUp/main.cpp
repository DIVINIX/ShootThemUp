#include <iostream>
#include "GameModel.h"
#include "GameView.h"

using namespace std;

int main()
{
	srand(time(NULL));
	GameModel jeu(VIEW_WIDTH, VIEW_HEIGHT);
	GameView ecran(&jeu);

	while (ecran.treatEvents())
	{
		jeu.nextStep();
		ecran.draw();
	}
}

