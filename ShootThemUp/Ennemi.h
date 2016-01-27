#ifndef ENNEMI_H
#define ENNEMI_h

#include "Vaisseau.h"

class Ennemi : public Vaisseau
{

private:
	int _valeur;

public:

	Ennemi();
	Ennemi(int x, int y, int vieVaisseau, int niveauEnnemi, int valeur);
	~Ennemi();

	int getValeur() const;
};
#endif


