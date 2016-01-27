#ifndef TIR_H
#define TIR_H

#include "ObjetMobile.h"

class Tir : public ObjetMobile
{
private:
	int _degat;
public:
	Tir(int x, int y, int degat);
	Tir();
	~Tir();

	int getDegat() const;
};
#endif

