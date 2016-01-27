#include "Joueur.h"

Joueur::Joueur(int x, int y, int vieVaisseau, int nombreDeVie, bool avoirbombe) 
: Vaisseau(x, y, vieVaisseau, 1), _nombreDeVie{ nombreDeVie }, _avoirBombre{avoirbombe}
{}

Joueur::Joueur() : Vaisseau()
{}

Joueur::~Joueur()
{}

int Joueur::getNombreDeVie() const
{
	return _nombreDeVie;
}

void Joueur::decrementerVie()
{
	_nombreDeVie--;
}

void Joueur::setNombreDeVie(int n)
{
	_nombreDeVie = n;
}

bool Joueur::getBombe() const
{
	return _avoirBombre;
}

void Joueur::setBombe(bool b)
{
	_avoirBombre = b;
}