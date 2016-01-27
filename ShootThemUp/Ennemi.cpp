#include "Ennemi.h"

Ennemi::Ennemi(int x, int y, int vieVaisseau, int niveauEnnemi, int valeur) 
: Vaisseau(x, y, vieVaisseau, niveauEnnemi), _valeur{ valeur }
{}

Ennemi::~Ennemi()
{}

int Ennemi::getValeur() const
{
	return _valeur;
}
