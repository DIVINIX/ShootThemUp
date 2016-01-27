#include "GameModel.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;
using namespace sf;

//==============================================================================
// Constructeurs
//==============================================================================

GameModel::GameModel()
: _width{ VIEW_WIDTH }, _height{ VIEW_HEIGHT }
{
	_joueur = new Joueur();
	_level = 1;
	_score = _level * 1000 - 1000;
	_etat = 1;
	_nbEnnemiTuer = 0;
}

GameModel::GameModel(int w, int h)
: _width{ w }, _height{ h }
{
	_joueur = new Joueur(POS_JOUEUR_X, POS_JOUEUR_Y, VIE_VAISSEAU, NB_VIE_JOUEUR, false);
	_level = 1;
	_score = _level * 1000 - 1000;
	_etat = 1;
	_nbEnnemiTuer = 0;
}

//==============================================================================
// Destructeur
//==============================================================================

GameModel::~GameModel()
{}

//==============================================================================
// Accesseurs de lecture
//==============================================================================

//Accesseurs pour le joueur
void GameModel::getJoueurPos(int &x, int &y) const
{
	x = _joueur->getX();
	y = _joueur->getY();
}

void GameModel::getTirJoueurPos(int &x, int &y, int i) const
{
	x = _tirsJoueur[i]->getX();
	y = _tirsJoueur[i]->getY();
}

void GameModel::getNombreTirJoueur(int &n) const
{
	if (_tirsJoueur.size() != 0)
		n = _tirsJoueur.size();
	else
		n = 0;
}

int GameModel::getNombreDeVieJoeur() const
{
	return _joueur->getNombreDeVie();
}

int GameModel::getDegatTirJoueur(int i) const
{
	return _tirsJoueur[i]->getDegat();
}

int GameModel::getPointDeVieVaisseauJoueur() const
{
	return _joueur->getPointDeVie();
}

bool GameModel::getJoueurBombe() const
{
	return _joueur->getBombe();
}

int GameModel::getLvlVaisseauJoueur() const
{
	return _joueur->getLvlVaisseau();
}

//Accesseurs pour les ennemis
void GameModel::getNombreEnnemi(int &n) const
{
	if (_ennemis.size() != 0)
		n = _ennemis.size();
	else
		n = 0;
}

void GameModel::getNombreTirEnnemi(int &n) const
{
	if (_tirsEnnemis.size() != 0)
		n = _tirsEnnemis.size();
	else
		n = 0;
}

void GameModel::getEnnemiPos(int &x, int &y, int i) const
{
	x = _ennemis[i]->getX();
	y = _ennemis[i]->getY();
}

void GameModel::getTirEnnemiPos(int &x, int &y, int i) const
{
	x = _tirsEnnemis[i]->getX();
	y = _tirsEnnemis[i]->getY();
}

int GameModel::getPointDeVieVaisseauEnnemi(int i) const
{
	return _ennemis[i]->getPointDeVie();
}

int GameModel::getNiveauEnnemi(int i) const
{
	return _ennemis[i]->getLvlVaisseau();
}

// Accesseurs pour le déroulement du jeu
int GameModel::getLevel() const
{
	return _level;
}

int GameModel::getScore() const
{
	return _score;
}

int GameModel::getEtat() const
{
	return _etat;
}

//==============================================================================
// Accesseurs d'écriture
//==============================================================================

void GameModel::setEtat(int e)
{
	_etat = e;
}

void GameModel::setBombeJoueur(bool b)
{
	_joueur->setBombe(b);
}

void GameModel::setLvl(int n)
{
	_level = n;
}
//==============================================================================
// Méthodes pour le déroulement du jeu
//==============================================================================

//Méthodes pour le joueur

void GameModel::deplacerJoueurHaut()
{
	if (_joueur->getY() > 50)
		_joueur->setY(-3);
}

void GameModel::deplacerJoueurBas()
{
	if (_joueur->getY() < VIEW_HEIGHT - JOUEUR_HEIGHT)
		_joueur->setY(3);
}

void GameModel::deplacerJoueurDroite()
{
	if (_joueur->getX() + JOUEUR_WIDTH < VIEW_WIDTH)
		_joueur->setX(3);
}

void GameModel::deplacerJoueurGauche()
{
	if (_joueur->getX() > 0)
		_joueur->setX(-3);
}

void GameModel::ajouterTirJoueur()
{
	if (_clockJoueur.GetElapsedTime() > 1 / 8.f)
	{
		if ((_joueur->getLvlVaisseau() >= 1) && (_joueur->getLvlVaisseau() < 4))
			_tirsJoueur.push_back(new Tir(_joueur->getX() + 110, _joueur->getY() + 25, TIR_DMG_JOUEUR_LVL1));
		if ((_joueur->getLvlVaisseau() >= 4) && (_joueur->getLvlVaisseau() < 7))
			_tirsJoueur.push_back(new Tir(_joueur->getX() + 110, _joueur->getY() + 25, TIR_DMG_JOUEUR_LVL2));
		if ((_joueur->getLvlVaisseau() >= 7) && (_joueur->getLvlVaisseau() <10))
			_tirsJoueur.push_back(new Tir(_joueur->getX() + 110, _joueur->getY() + 25, TIR_DMG_JOUEUR_LVL3));
		_clockJoueur.Reset();
	}
}

void GameModel::avancerTirsJoueur()
{
	int tx, ty;

	if (_tirsJoueur.size() != 0)
	{
		for (unsigned int i = 0; i < _tirsJoueur.size(); i++) // Pour tous les tirs du joueur
		{
			getTirJoueurPos(tx, ty, i); // On récupère la position des tirs du joueur
			if (tx >= VIEW_WIDTH)
				_tirsJoueur[i]->setaSupprimer(true);
			_tirsJoueur[i]->setX(3);
		}
	}
}

void GameModel::ajouterBombeJoueur()
{
	if (_clockBombe.GetElapsedTime() > 20.f)
	{
		_joueur->setBombe(true);
		_clockBombe.Reset();
	}
}

//Méthodes pour les enemis

void GameModel::ajouterEnnemi()
{
	if (_clockEnnemis.GetElapsedTime() > 3.f) // Toute les 3 secondes
	{
		int Random = Randomizer::Random(40, (VIEW_HEIGHT - ENNEMI_HEIGHT)); // Rand pour la position de l'ennemi
		int randNiveau = Randomizer::Random(0, 100); // Rand Pour le niveau de l'ennemi

		if (randNiveau >= 0 && randNiveau < 40)
			_ennemis.push_back(new Ennemi(VIEW_WIDTH + 50, Random, VIE_ENNEMI1, 1, VALEUR_ENNEMI_LVL1));

		if (randNiveau >= 40 && randNiveau < 75)
			_ennemis.push_back(new Ennemi(VIEW_WIDTH + 50, Random, VIE_ENNEMI2, 2, VALEUR_ENNEMI_LVL2));

		if (randNiveau >= 75 && randNiveau <100)
			_ennemis.push_back(new Ennemi(VIEW_WIDTH + 50, Random, VIE_ENNEMI3, 3, VALEUR_ENNEMI_LVL3));
		_clockEnnemis.Reset(); //on remet a jour l'horloge
	}
}

void GameModel::ajouterTirEnnemi()
{
	int x, y; // Poour récupérer la position des ennemis

	if (_clockTirEnnemis.GetElapsedTime() > 2.f)  // Toute les 2 secondes
	{
		if (_ennemis.size() != 0) // Si il y a des ennemis
		{
			for (unsigned int i = 0; i < _ennemis.size(); i++) // Pour tous les ennemis
			{
				getEnnemiPos(x, y, i); // On récupère la position de l'ennemi

				switch (_ennemis[i]->getLvlVaisseau()) // On rajoute des tirs selon le niveau de l'ennemi
				{
				case 1:
					_tirsEnnemis.push_back(new Tir(x - 5, y + (ENNEMI_HEIGHT / 2), TIR_DMG_ENNEMI_LVL1));
					break;
				case 2:
					_tirsEnnemis.push_back(new Tir(x - 5, y + (ENNEMI_HEIGHT / 2), TIR_DMG_ENNEMI_LVL2));
					break;
				case 3:
					_tirsEnnemis.push_back(new Tir(x - 5, y + (ENNEMI_HEIGHT / 2), TIR_DMG_ENNEMI_LVL3));
					break;
				}
			}
		}
		_clockTirEnnemis.Reset(); //on remet a jour l'horloge
	}
}

void GameModel::collisionJoueur()
{
	int jx, jy; // Pour la position du joueur
	int tx, ty; // Pour la position des tirs des ennemis
	getJoueurPos(jx, jy); // On récupère la position du joueur

	if (_tirsEnnemis.size() != 0) // Si il y a des tirs ennemis
	{
		for (unsigned int i = 0; i < _tirsEnnemis.size(); i++) // Pour tous les tirs ennemis
		{
			getTirEnnemiPos(tx, ty, i); // On recupère la position des tirs ennemis
			if (((tx < jx + JOUEUR_WIDTH) && (tx > jx) && (ty > jy) && (ty < jy + JOUEUR_HEIGHT))
				|| ((tx < jx + JOUEUR_WIDTH) && (tx > jx) && (ty + 14 > jy) && (ty + 14 < jy + JOUEUR_HEIGHT)))
			{
				_joueur->decrementerVieVaisseau(_tirsEnnemis[i]->getDegat()); // Le joueur perd de la vie en fonction du degat du tir
				if (_joueur->getPointDeVie() <= 0) // Si les points de vie du vaisseau sont en dessous ou égale à 0
				{
					_joueur->decrementerVie(); // On enlève une vie au joueur
					_joueur->setVieVaisseau(VIE_VAISSEAU); // On remet la vie du vaisseau au maximum
					_etat = TRANSITIONVIE; // On passe en écran de transition
				}
				_tirsEnnemis[i]->setaSupprimer(true); // Le tir sera supprimé à la fin du tour
			}
		}
	}
}

void GameModel::collisionEnnemi()
{
	int ex, ey;
	int jx, jy;
	int tx, ty;

	getJoueurPos(jx, jy); // On récupère la position du joueur

	if (_tirsJoueur.size() != 0) // Si il y a des tirs du joueur
	{
		for (unsigned int j = 0; j < _tirsJoueur.size(); j++) // Pour tous les tirs du joueur
		{
			getTirJoueurPos(tx, ty, j); // On récupère la position des tirs du joueur
			for (unsigned int i = 0; i < _ennemis.size(); i++) // Pour tous les ennemis
			{
				getEnnemiPos(ex, ey, i); // On récupère la position de l'ennemi
				if ((tx >= ex) && (ty >= ey) && (ty <= ey + 71))
				{
					_tirsJoueur[i]->setaSupprimer(true); // Le tir sera supprimer à la fin du tour
					_ennemis[i]->decrementerVieVaisseau(_tirsJoueur[j]->getDegat()); // L'ennemi perd de la vie en fonction des dégats du tir du joueur
					if (_ennemis[i]->getPointDeVie() <= 0) // Si les points de vie de l'ennemi sont en dessous ou égale à 0
					{
						_score += _ennemis[i]->getValeur(); // Le score augmente en fonction de la valeur de l'ennemi
						_ennemis[i]->setaSupprimer(true); // L'ennemi sera supprimé a la fin du tour
						_nbEnnemiTuer++;
					}
				}
			}
		}
	}
}

void GameModel::collisionJoueurEnnemi()
{
	int ex, ey, ew;
	int jx, jy;
	getJoueurPos(jx, jy);

	// Collision avec entre le joueur et les ennemis
	if (_ennemis.size() != 0) // Si il y a des ennemis
	{
		for (unsigned int i = 0; i < _ennemis.size(); i++) // Pour tous les ennemis
		{
			getEnnemiPos(ex, ey, i); // On récupère la position de l'ennemi

			if (getNiveauEnnemi(i) == 1)
				ew = ENNEMI1_WIDHT;
			else if (getNiveauEnnemi(i) == 2)
				ew = ENNEMI2_WIDHT;
			else if (getNiveauEnnemi(i) == 3)
				ew = ENNEMI3_WIDHT;

			if (
				(((ex < jx + JOUEUR_WIDTH) &&
				(ex > jx) &&
				(ey > jy) &&
				(ey < jy + JOUEUR_HEIGHT)))
				||
				(((ex + ew < jx + JOUEUR_WIDTH) &&
				(ex + ew > jx) &&
				(ey > jy) &&
				(ey < jy + JOUEUR_HEIGHT)))
				||
				(((ex < jx + JOUEUR_WIDTH) &&
				(ex > jx) &&
				(ey + ENNEMI_HEIGHT > jy) &&
				(ey + ENNEMI_HEIGHT < jy + JOUEUR_HEIGHT)))
				||
				((ex + ew < jx + JOUEUR_WIDTH) &&
				(ex + ew > jx) &&
				(ey + ENNEMI_HEIGHT > jy) &&
				(ey + ENNEMI_HEIGHT < jy + JOUEUR_HEIGHT)))
			{
				_ennemis[i]->setaSupprimer(true); // L'ennemi sera supprimé a la fin du tour
				_joueur->decrementerVie(); // On enlève une vie au joueur
				_joueur->setVieVaisseau(VIE_VAISSEAU); // On remet la vie du vaisseau au maximum
				_etat = TRANSITIONVIE;
			}
		}
	}
}

void GameModel::deplacerEnnemi()
{
	if (_ennemis.size() != 0)
	{
		for (unsigned int i = 0; i < _ennemis.size(); i++) // Pour tous les ennmis on les déplace
		{
			_ennemis[i]->setX(-1);
			if (_ennemis[i]->getX() <= 0)
				_ennemis[i]->setaSupprimer(true); // Si l'ennemi a atteint un x de 0 on le supprimera à la fin du tour
		}
	}
}

void GameModel::supprimerElements()
{
	if (_ennemis.size() != 0)
	{
		for (unsigned int i = 0; i < _ennemis.size(); i++)
		{
			if (_ennemis[i]->getaSupprimer())
				_ennemis.erase(_ennemis.begin() + i);
		}
	}

	// Suppressions des tirs ennemis
	if (_tirsEnnemis.size() != 0)
	{
		for (unsigned int i = 0; i < _tirsEnnemis.size(); i++)
		{
			if (_tirsEnnemis[i]->getaSupprimer())
				_tirsEnnemis.erase(_tirsEnnemis.begin() + i);
		}
	}

	// Suppression des tirs du joueur
	if (_tirsJoueur.size() != 0)
	{
		for (unsigned int i = 0; i < _tirsJoueur.size(); i++)
		{
			if (_tirsJoueur[i]->getaSupprimer())
				_tirsJoueur.erase(_tirsJoueur.begin() + i);
		}
	}
}

void GameModel::avancerTirsEnnemis()
{
	int tx, ty;

	if (_tirsEnnemis.size() != 0)
	{
		for (unsigned int i = 0; i < _tirsEnnemis.size(); i++) // Pour tous les tirs du joueur
		{
			getTirEnnemiPos(tx, ty, i); // On récupère la position des tirs du joueur
			if (tx <= 0)
				_tirsEnnemis[i]->setaSupprimer(true);
			_tirsEnnemis[i]->setX(-3);
		}
	}
}

void GameModel::supprimerEnnemi()
{
	if (_ennemis.size() != 0) // Si il y a des ennemis
	{
		for (unsigned int i = 0; i < _ennemis.size(); i++) // Pour tous les ennemis
		{
			_score += _ennemis[i]->getValeur();
		}
		_ennemis.clear();
	}
}

//Méthodes pour lee déroulement du jeu

void GameModel::resetEcran()
{
	_ennemis.clear(); //supprime tous les ennemis
	_tirsJoueur.clear(); //supprime tous les tirs
	_tirsEnnemis.clear(); //supprime tous les tirs
	_joueur->setPositionX(POS_JOUEUR_X);
	_joueur->setPositionY(POS_JOUEUR_Y);
}

void GameModel::resetJeu()
{
	setLvl(1);
	_score = 0;
	_joueur->setLvlVaisseau(1);
	_joueur->setVieVaisseau(VIE_VAISSEAU);
	_joueur->setNombreDeVie(NB_VIE_JOUEUR);
	resetEcran();
}

void GameModel::nextLevel()
{
	if (_score >= (_level * 10000))
	{
		_score = 0;
		_level++;
		_joueur->setLvlVaisseau(_level);
		_joueur->setVieVaisseau(VIE_VAISSEAU);
		resetEcran(); //on remet a jour l'écran
		_etat = TRANSITIONLVL;
	}
}

void GameModel::nextStep()
{
	if (_etat == PAUSE)
	{
	}

	if (_etat == ENJEU)
	{
		avancerTirsJoueur();
		avancerTirsEnnemis(); 
		deplacerEnnemi();

		ajouterEnnemi();
		ajouterTirEnnemi();

		collisionJoueur();
		collisionEnnemi();
		collisionJoueurEnnemi();

		ajouterBombeJoueur();
		nextLevel();

		if (getNombreDeVieJoeur() == 0)
			setEtat(GAMEOVER);

		supprimerElements();
	}
}