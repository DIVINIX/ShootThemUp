#ifndef OBJETMOBILE_H
#define OBJETMOBILE_H

class ObjetMobile
{
protected:
	int _x;
	int _y;

	bool _aSupprimer;

public:
	ObjetMobile();
	ObjetMobile(int x, int y);
	~ObjetMobile();

	int getX();
	int getY();
	void setX(int n);
	void setY(int n);
	void setPositionX(int n);
	void setPositionY(int n);
	bool getaSupprimer() const;
	void setaSupprimer(bool n);
};
#endif
