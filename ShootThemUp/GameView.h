#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "GameModel.h"
#include <string>
#include <SFML\Graphics.hpp>

class GameView
{
private:
	GameModel *_model;

	sf::RenderWindow * _window;

	//==============================================================================
	// Polices
	//==============================================================================

	sf::Font police;
	sf::String text;

	//==============================================================================
	// Horloge
	//==============================================================================

	sf::Clock _clockTransition;

	//==============================================================================
	// Images
	//==============================================================================

	sf::Image imgBouton;
	sf::Image imgLogo;
	sf::Image imgVaisseau;
	sf::Image imgFond;
	sf::Image imgVaisseauJoueur;
	sf::Image imgVaisseauEnnemi1;
	sf::Image imgVaisseauEnnemi2;
	sf::Image imgVaisseauEnnemi3;
	sf::Image imgExplosion;
	sf::Image imgTirJoueur1;
	sf::Image imgTirJoueur2;
	sf::Image imgTirJoueur3;
	sf::Image imgTirEnnemi;
	sf::Image imgBombe;

	//==============================================================================
	// Sprites
	//==============================================================================

	sf::Sprite bouton;
	sf::Sprite logo;
	sf::Sprite vaisseau;
	sf::Sprite fond;
	sf::Sprite vaisseauJoueur;
	sf::Sprite vaisseauEnnemi1;
	sf::Sprite vaisseauEnnemi2;
	sf::Sprite vaisseauEnnemi3;
	sf::Sprite explosion;
	sf::Sprite tirJoueur1;
	sf::Sprite tirJoueur2;
	sf::Sprite tirJoueur3;
	sf::Sprite tirEnnemi;
	sf::Sprite bombe;

	bool _survolPlay;
	bool _survolQuit;

public:
	GameView(GameModel *model);
	~GameView();

	void draw();
	void drawMenu();
	void drawJeu();
	void drawTransitionVie();
	void drawTransitionLvl();
	void drawPause();
	void drawGameOver();
	bool treatEvents();
	void deplacerVaisseau();
};

#endif

