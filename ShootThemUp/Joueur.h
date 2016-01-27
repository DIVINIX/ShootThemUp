#ifndef JOUEUR_H
#define JOUER_H

#include "Vaisseau.h"

class Joueur : public Vaisseau
{
private:
	int _nombreDeVie;
	bool _avoirBombre;

public:
	Joueur();
	Joueur(int x, int y, int vieVaisseau, int nombreDeVie,bool avoirBombe);
	~Joueur();

	int getNombreDeVie() const;
	void setNombreDeVie(int n);
	void decrementerVie();

	bool getBombe() const;
	void setBombe(bool b);
};
#endif

