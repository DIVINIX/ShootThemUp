#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <SFML/System.hpp>
#include "constantes.h"
#include "ObjetMobile.h"
#include "Joueur.h"
#include "Ennemi.h"
#include "Tir.h"
#include <vector>

enum EtatJeu
{
	MENU = 1,
	ENJEU = 2,
	TRANSITIONVIE = 3,
	TRANSITIONLVL = 4,
	PAUSE = 5,
	GAMEOVER = 6,
};

class GameModel
{
private:
	int _width;
	int _height;
	int _score;
	int _level;
	int _etat;
	int _nbEnnemiTuer;

	Joueur * _joueur;
	std::vector<Ennemi *> _ennemis;
	std::vector<Tir *> _tirsJoueur;
	std::vector<Tir *> _tirsEnnemis;
	
	sf::Clock _clockJoueur;
	sf::Clock _clockEnnemis;
	sf::Clock _clockTirEnnemis;
	sf::Clock _clockBombe;
	
public:
	GameModel();
	GameModel(int w, int h);
	~GameModel();
	
	//==============================================================================
	// Méthodes concernant le joueur
	//==============================================================================

	void deplacerJoueurHaut();
	void deplacerJoueurBas();
	void deplacerJoueurDroite();
	void deplacerJoueurGauche();

	void ajouterTirJoueur();

	void getJoueurPos(int &x, int &y) const;
	void getTirJoueurPos(int &x, int &y, int i) const;
	void getNombreTirJoueur(int &n) const;
	int getNombreDeVieJoeur() const;
	int getDegatTirJoueur(int i) const;
	int getPointDeVieVaisseauJoueur() const;
	int getLvlVaisseauJoueur() const;
	bool getJoueurBombe() const;
	
	void setBombeJoueur(bool b);

	void ajouterBombeJoueur();
	void avancerTirsJoueur();

	//==============================================================================
	// Méthodes concernant les ennemis
	//==============================================================================

	void ajouterEnnemi();
	void ajouterTirEnnemi();
	void deplacerEnnemi();

	void getNombreEnnemi(int &n) const;
	void getNombreTirEnnemi(int &n) const;
	void getEnnemiPos(int &x, int &y, int i) const;
	void getTirEnnemiPos(int &x, int &y, int i) const;	
	int getPointDeVieVaisseauEnnemi(int i) const;
	int getNiveauEnnemi(int i) const;

	void supprimerEnnemi();
	void avancerTirsEnnemis();

	//==============================================================================
	// Méthodes pour le déroulement du jeu
	//==============================================================================

	void collisionJoueur();
	void collisionEnnemi();
	void collisionJoueurEnnemi();
	void supprimerElements();	
	void nextLevel();
	void setLvl(int n);
	void setEtat(int e);

	int getLevel() const;
	int getScore() const;
	int getEtat() const;
	
	void resetEcran();
	void resetJeu();
	
	void nextStep();
};

#endif
