#include "Vaisseau.h"
using namespace std;

Vaisseau::Vaisseau(int x, int y, int vieVaisseau, int lvlVaisseau) 
:ObjetMobile(x, y), _pointDeVie{ vieVaisseau }, _lvlVaisseau{lvlVaisseau}
{}

Vaisseau::Vaisseau()
{
	_x = 0;
	_y = 0;
	_pointDeVie = 0;
}

Vaisseau::~Vaisseau()
{}

int Vaisseau::getPointDeVie() const
{
	return _pointDeVie;
}

int Vaisseau::getLvlVaisseau() const
{
	return _lvlVaisseau;
}

void Vaisseau::setLvlVaisseau(int n)
{
	_lvlVaisseau = n;
}

void Vaisseau::decrementerVieVaisseau(int n)
{
_pointDeVie = _pointDeVie-n;
}

void Vaisseau::setVieVaisseau(int n)
{
	_pointDeVie = n;
}