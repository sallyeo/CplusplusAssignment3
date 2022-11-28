#include "assn3.h"

void Point2D::setDistFrOrigin()
{
	distFrOrigin = sqrt((x*x)+(y*y));
}

int Point2D::getX()
{
	return x;
}

int Point2D::getY()
{
	return y;
}

double Point2D::getScalarValue()
{
	return distFrOrigin;
}
		
void Point2D::setX(int x)
{
	this->x = x;
}

void Point2D::setY(int y)
{
	this->y = y;
}

bool operator==(Point2D p1, Point2D p2)
{
	if ((p1.getX() == p2.getX()) && (p1.getY() == p2.getY()))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

string Point2D::toString()
{
	stringstream string;
	string << "[" << right << setw(4) << getX() << ", " << setw(4) << getY() << "]" << setw(3) << " " << left << fixed << setprecision(3) << getScalarValue() << endl;
	
	return string.str();
}