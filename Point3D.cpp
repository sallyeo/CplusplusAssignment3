#include "assn3.h"

void Point3D::setDistFrOrigin()
{
	distFrOrigin = sqrt((x*x)+(y*y)+(z*z));
}

int Point3D::getZ()
{
	return z;
}

void Point3D::setZ(int z)
{
	this->z = z;
}

bool operator==(Point3D p1, Point3D p2)
{
	if ((p1.getX() == p2.getX()) && (p1.getY() == p2.getY()) && (p1.getZ() == p2.getZ()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

string Point3D::toString()
{
	stringstream string;
	string << "[" << right << setw(4) << getX() << ", " << setw(4) << getY() << ", " << setw(4) << getZ() << "]" << setw(3) << " " << left << fixed << setprecision(3) << getScalarValue() << endl;
	
	return string.str();
}