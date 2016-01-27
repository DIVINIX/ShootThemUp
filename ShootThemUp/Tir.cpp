#include "Tir.h"


Tir::Tir(int x, int y, int degat) : ObjetMobile(x, y), _degat{ degat }
{}

Tir::Tir()
{
	_x = 0;
	_y = 0;
	_degat = 0;
}

Tir::~Tir()
{}

int Tir::getDegat() const
{
	return _degat;
}