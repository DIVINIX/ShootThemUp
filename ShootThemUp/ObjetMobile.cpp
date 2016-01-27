#include "ObjetMobile.h"

ObjetMobile::ObjetMobile(int x, int y) :_x{ x }, _y{ y }, _aSupprimer{false}
{
}

ObjetMobile::ObjetMobile()
{}


ObjetMobile::~ObjetMobile()
{}


int ObjetMobile::getX()
{
	return _x;
}

int ObjetMobile::getY()
{
	return _y;
}

void ObjetMobile::setX(int n)
{
	_x = _x + n;
}

void ObjetMobile::setY(int n)
{
	_y = _y + n;
}

bool ObjetMobile::getaSupprimer() const
{
	return _aSupprimer;
}

void ObjetMobile::setaSupprimer(bool n)
{
	_aSupprimer = n;
}

void ObjetMobile::setPositionX(int n)
{
	_x = n;
}

void ObjetMobile::setPositionY(int n)
{
	_y = n;
}