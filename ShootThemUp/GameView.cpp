#include "GameView.h"

using namespace std;
using namespace sf;

#include <string>
#include <iostream>

GameView::GameView(GameModel *model) : _model{ model }
{
	_window = new RenderWindow(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT, 32), "Shoot Them Up");

	if (!imgBouton.LoadFromFile("images/buttons.png") ||
		!imgLogo.LoadFromFile("images/logo.jpeg") ||
		!imgVaisseau.LoadFromFile("images/revive.png") ||
		!imgFond.LoadFromFile("images/bg.png") ||
		!imgVaisseauJoueur.LoadFromFile("images/ship_all.png") ||
		!imgVaisseauEnnemi1.LoadFromFile("images/ennemy_0.png") ||
		!imgVaisseauEnnemi2.LoadFromFile("images/ennemy_1.png") ||
		!imgVaisseauEnnemi3.LoadFromFile("images/ennemy_2.png") ||
		!imgExplosion.LoadFromFile("images/explosion.png") ||
		!imgTirJoueur1.LoadFromFile("images/tir1.png") ||
		!imgTirJoueur2.LoadFromFile("images/tir2.png") ||
		!imgTirJoueur3.LoadFromFile("images/tir3.png") ||
		!imgTirEnnemi.LoadFromFile("images/shot.png") ||
		!imgBombe.LoadFromFile("images/bombe.png"))
	{
		// Erreur...
	}
	else
	{
		bouton.SetImage(imgBouton);
		logo.SetImage(imgLogo);
		vaisseau.SetImage(imgVaisseau);
		fond.SetImage(imgFond);
		vaisseauJoueur.SetImage(imgVaisseauJoueur);
		vaisseauEnnemi1.SetImage(imgVaisseauEnnemi1);
		vaisseauEnnemi2.SetImage(imgVaisseauEnnemi2);
		vaisseauEnnemi3.SetImage(imgVaisseauEnnemi3);
		explosion.SetImage(imgExplosion);
		tirJoueur1.SetImage(imgTirJoueur1);
		tirJoueur2.SetImage(imgTirJoueur2);
		tirJoueur3.SetImage(imgTirJoueur3);
		tirEnnemi.SetImage(imgTirEnnemi);
		bombe.SetImage(imgBombe);
	}

	if (!police.LoadFromFile("Police/Antique Olive.ttf", 50))
	{
		// Erreur...
	}
	text.SetFont(police);
}

GameView::~GameView()
{}

void GameView::draw()
{
	_window->Clear();

	switch (_model->getEtat())
	{
	case MENU:
		drawMenu();
		break;

	case ENJEU:
		drawJeu();
		break;

	case TRANSITIONLVL:
		drawTransitionLvl();
		break;

	case TRANSITIONVIE:
		drawTransitionVie();
		break;

	case PAUSE:
		drawPause();
		break;

	case GAMEOVER:
		drawGameOver();
		break;
	}

	_window->Display();
}

void GameView::drawMenu()
{
	Shape couleurFond = sf::Shape::Rectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, sf::Color::White);
	_window->Draw(couleurFond);

	logo.SetScale(0.6, 0.6);
	logo.SetPosition(0, 0);
	_window->Draw(logo);

	vaisseauEnnemi1.SetPosition(30, 600);
	_window->Draw(vaisseauEnnemi1);

	vaisseauEnnemi2.SetPosition(970, 30);
	_window->Draw(vaisseauEnnemi2);

	vaisseau.SetScale(2, 2);
	vaisseau.SetPosition(300, 200);
	_window->Draw(vaisseau);

	text.SetSize(65);
	text.SetColor(sf::Color::Black);

	text.SetText("Shoot Them Up");
	text.SetPosition(350, 0);
	_window->Draw(text);

	text.SetSize(50);
	text.SetColor(sf::Color::White);

	bouton.SetSubRect(sf::IntRect(0, 0, 150, 80));
	if (_survolPlay)
		bouton.SetSubRect(sf::IntRect(150, 0, 300, 80));
	bouton.SetPosition(100, VIEW_HEIGHT / 2 - 40);
	_window->Draw(bouton);
	text.SetText("Play");
	text.SetPosition(125, VIEW_HEIGHT / 2 - 35);
	_window->Draw(text);

	bouton.SetSubRect(sf::IntRect(0, 0, 150, 80));
	if (_survolQuit)
		bouton.SetSubRect(sf::IntRect(150, 0, 300, 80));
	bouton.SetPosition(950, VIEW_HEIGHT / 2 - 40);
	_window->Draw(bouton);
	text.SetText("Quit");
	text.SetPosition(975, VIEW_HEIGHT / 2 - 35);
	_window->Draw(text);
}

void GameView::drawJeu()
{
	if (fond.GetPosition().x <= -fond.GetSize().x + 1200)
		fond.SetPosition(-0.5, 0);
	fond.Move(-0.5, 0);
	_window->Draw(fond);

	int nbVie = _model->getNombreDeVieJoeur();
	vaisseau.SetScale(0.2, 0.2);

	switch (nbVie)
	{
	case 1:
		vaisseau.SetPosition(200, 10);
		_window->Draw(vaisseau);
		break;
	case 2:
		vaisseau.SetPosition(200, 10);
		_window->Draw(vaisseau);
		vaisseau.SetPosition(250, 10);
		_window->Draw(vaisseau);
		break;
	case 3:
		vaisseau.SetPosition(200, 10);
		_window->Draw(vaisseau);
		vaisseau.SetPosition(250, 10);
		_window->Draw(vaisseau);
		vaisseau.SetPosition(300, 10);
		_window->Draw(vaisseau);
		break;
	}

	text.SetSize(30);
	text.SetColor(sf::Color::Black);

	text.SetText("Niveau : " + to_string(_model->getLevel()));
	text.SetPosition(10, 10);
	_window->Draw(text);

	text.SetText("Vie : " + to_string(_model->getPointDeVieVaisseauJoueur()));
	text.SetPosition(400, 10);
	_window->Draw(text);

	text.SetText("Score : " + to_string(_model->getScore()) + " / " + to_string(_model->getLevel() * 10000));
	text.SetPosition(550, 10);
	_window->Draw(text);

	if (_model->getJoueurBombe())
	{
		bombe.SetScale(0.6, 0.6);
		bombe.SetPosition(1100, 10);
		_window->Draw(bombe);
	}

	int x, y;
	_model->getJoueurPos(x, y);
	vaisseauJoueur.SetSubRect(sf::IntRect(0, 0, 300, 186));
	vaisseauJoueur.SetScale(0.4, 0.4);
	vaisseauJoueur.SetPosition(x, y);
	_window->Draw(vaisseauJoueur);

	int nbTirJoueur;
	int tx, ty;
	_model->getNombreTirJoueur(nbTirJoueur);

	for (int i = 0; i < nbTirJoueur; i++)
	{
		_model->getTirJoueurPos(tx, ty, i);

		if ((_model->getLvlVaisseauJoueur() >= 1) && (_model->getLvlVaisseauJoueur() < 4))
		{
			tirJoueur1.SetScale(0.7, 0.7);
			tirJoueur1.SetSubRect(sf::IntRect(0, 0, 46, 20));
			tirJoueur1.SetPosition(tx, ty);
			_window->Draw(tirJoueur1);
		}

		if ((_model->getLvlVaisseauJoueur() >= 4) && (_model->getLvlVaisseauJoueur() < 7))
		{
			tirJoueur2.SetScale(0.7, 0.7);
			tirJoueur2.SetSubRect(sf::IntRect(0, 0, 46, 20));
			tirJoueur2.SetPosition(tx, ty);
			_window->Draw(tirJoueur2);
		}

		if ((_model->getLvlVaisseauJoueur() >= 7) && (_model->getLvlVaisseauJoueur() < 10))
		{
			tirJoueur3.SetScale(0.7, 0.7);
			tirJoueur3.SetSubRect(sf::IntRect(0, 0, 46, 20));
			tirJoueur3.SetPosition(tx, ty);
			_window->Draw(tirJoueur3);
		}
	}

	int nbEnnemi;
	_model->getNombreEnnemi(nbEnnemi);
	int ex, ey;

	for (int i = 0; i < nbEnnemi; i++)
	{
		_model->getEnnemiPos(ex, ey, i);

		switch (_model->getNiveauEnnemi(i))
		{
		case 1:
			vaisseauEnnemi1.SetScale(0.5, 0.5);
			vaisseauEnnemi1.SetPosition(ex, ey);
			_window->Draw(vaisseauEnnemi1);
			break;

		case 2:
			vaisseauEnnemi2.SetScale(0.5, 0.5);
			vaisseauEnnemi2.SetPosition(ex, ey);
			_window->Draw(vaisseauEnnemi2);
			break;

		case 3:
			vaisseauEnnemi3.SetScale(0.5, 0.5);
			vaisseauEnnemi3.SetPosition(ex, ey);
			_window->Draw(vaisseauEnnemi3);
			break;
		}
	}

	int nbTirEnnemi;
	int tex, tey;
	_model->getNombreTirEnnemi(nbTirEnnemi);

	for (int i = 0; i < nbTirEnnemi; i++)
	{
		_model->getTirEnnemiPos(tex, tey, i);

		tirEnnemi.SetScale(0.7, 0.7);
		tirEnnemi.SetSubRect(sf::IntRect(0, 0, 46, 20));
		tirEnnemi.SetPosition(tex, tey);
		tirEnnemi.SetRotation(180);
		_window->Draw(tirEnnemi);
	}
}

void GameView::drawTransitionVie()
{
	_model->resetEcran(); //on remet a jour l'écran
	_clockTransition.Reset();

	while (_clockTransition.GetElapsedTime() < 5.f)
	{
		_window->Clear();

		Shape couleurFond = sf::Shape::Rectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, sf::Color::Black);

		text.SetSize(50);
		text.SetColor(sf::Color::White);

		text.SetText("Vous avez perdu une vie !");
		text.SetPosition(300, 300);
		_window->Draw(text);

		text.SetSize(30);
		text.SetText("Réaparition dans : " + to_string(5 - (int)_clockTransition.GetElapsedTime()));
		text.SetPosition(450, 500);
		_window->Draw(text);

		_window->Display();
	}

	_model->setEtat(ENJEU);
}

void GameView::drawTransitionLvl()
{
	_model->resetEcran(); //on remet a jour l'écran
	_clockTransition.Reset();

	while (_clockTransition.GetElapsedTime() < 5.f)
	{
		_window->Clear();

		Shape couleurFond = sf::Shape::Rectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, sf::Color::Black);

		text.SetSize(50);
		text.SetColor(sf::Color::White);

		text.SetText("Vous passez au niveau suivant !");
		text.SetPosition(250, 300);
		_window->Draw(text);

		text.SetSize(30);
		text.SetText("Réaparition dans : " + to_string(5 - (int)_clockTransition.GetElapsedTime()));
		text.SetPosition(450, 500);
		_window->Draw(text);

		_window->Display();
	}
	_model->setEtat(ENJEU);
}

void GameView::drawPause()
{
	Shape couleurFond = sf::Shape::Rectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, sf::Color::Black);

	text.SetSize(70);
	text.SetColor(sf::Color::White);

	text.SetText("Pause");
	text.SetPosition(500, 100);
	_window->Draw(text);

	text.SetSize(40);

	text.SetText("Pour reprendre appuyer sur R");
	text.SetPosition(320, 300);
	_window->Draw(text);

	text.SetText("Pour revenir au menu appuyer sur Q");
	text.SetPosition(280, 500);
	_window->Draw(text);
}

void GameView::drawGameOver()
{
	_model->resetJeu();
	_clockTransition.Reset();

	while (_clockTransition.GetElapsedTime() < 5.f)
	{
		_window->Clear();

		Shape couleurFond = sf::Shape::Rectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, sf::Color::Black);

		text.SetSize(50);
		text.SetColor(sf::Color::White);

		text.SetText("Vous avez perdu !");
		text.SetPosition(420, 300);
		_window->Draw(text);

		text.SetSize(30);
		text.SetText("Retour au menu dans: " + to_string(5 - (int)_clockTransition.GetElapsedTime()));
		text.SetPosition(450, 500);
		_window->Draw(text);

		_window->Display();
	}

	_model->setEtat(MENU);
}

bool GameView::treatEvents()
{
	bool resultat = true;
	if (_window->IsOpened())
	{
		Event event;

		deplacerVaisseau();

		while (_window->GetEvent(event))
		{
			/*if ((event.Type == Event::Closed) || (event.Key.Code == sf::Key::Escape))
			{
				resultat = false;
				_window->Close();
			}*/

			if (_model->getEtat() == MENU)
			{
				if (event.Type == Event::MouseMoved)
				{
					if ((event.MouseMove.X > 125 && event.MouseMove.X < 275) && (event.MouseMove.Y > 365 && event.MouseMove.Y < 445))
						_survolPlay = true;
					else if ((event.MouseMove.X > 950 && event.MouseMove.X < 1100) && (event.MouseMove.Y > 365 && event.MouseMove.Y < 445))
						_survolQuit = true;
					else
					{
						_survolPlay = false;
						_survolQuit = false;
					}
				}

				if (event.Type == Event::MouseButtonPressed && event.MouseButton.Button == Mouse::Left)
				{
					if ((event.MouseButton.X > 125 && event.MouseButton.X < 275) && (event.MouseButton.Y > 365 && event.MouseButton.Y < 445))
						_model->setEtat(ENJEU);

					/*if ((event.MouseButton.X > 950 && event.MouseButton.X < 1100) && (event.MouseButton.Y > 365 && event.MouseButton.Y < 445))
					{
						resultat = false;
						_window->Close();
					}*/
				}
			}

			if (_model->getEtat() == ENJEU)
			{
				if (event.Type == Event::KeyPressed)
				{
					if (event.Key.Code == Key::Space)
					{
						_model->ajouterTirJoueur();
					}

					if (event.Key.Code == Key::P)
					{
						_model->setEtat(PAUSE);
					}

					if (event.Key.Code == Key::B)
					{
						if (_model->getJoueurBombe())
						{
							_model->supprimerEnnemi();
							_model->setBombeJoueur(false);
						}
					}
				}
			}

			if (_model->getEtat() == PAUSE)
			{
				if (event.Type == Event::KeyPressed)
				{
					if (event.Key.Code == Key::R)
					{
						_model->setEtat(ENJEU);
					}

					if (event.Key.Code == Key::Q)
					{
						_model->resetJeu();
						_model->setEtat(MENU);
					}
				}
			}
		}
	}
	return resultat;
}

void GameView::deplacerVaisseau()
{
	if (_model->getEtat() == ENJEU)
	{
		if (_window->GetInput().IsKeyDown(sf::Key::Z)) _model->deplacerJoueurHaut();
		if (_window->GetInput().IsKeyDown(sf::Key::S)) _model->deplacerJoueurBas();
		if (_window->GetInput().IsKeyDown(sf::Key::D)) _model->deplacerJoueurDroite();
		if (_window->GetInput().IsKeyDown(sf::Key::Q)) _model->deplacerJoueurGauche();
	}
}