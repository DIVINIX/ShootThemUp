#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <vector>
#include "ObjetMobile.h"

class Vaisseau : public ObjetMobile
{
protected:
	int  _pointDeVie;
	int _lvlVaisseau;

public:
	Vaisseau(int x, int y, int vieVaisseau, int lvlVaisseau);
	Vaisseau();
	~Vaisseau();

	// Accesseurs de lecture
	int getPointDeVie() const;
	int getLvlVaisseau() const;

	// Accesseurs d'éciture
	void setLvlVaisseau(int l);
	void decrementerVieVaisseau(int n);
	void setVieVaisseau(int n);
};

#endif
