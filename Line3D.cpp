#include "assn3.h"

void Line3D::setLength()
{
	length = sqrt(pow((pt1.getX() - pt2.getX()), 2) + pow((pt1.getY() - pt2.getY()), 2) + pow((pt1.getZ() - pt2.getZ()), 2));
}
	
Point3D Line3D::getPt1()
{
	return pt1;
}

Point3D Line3D::getPt2()
{
	return pt2;
}

void Line3D::setPt1(Point3D pt1)
{
	this->pt1 = pt1;
}

void Line3D::setPt2(Point3D pt2)
{
	this->pt2 = pt2;
}

bool operator==(Line3D line1, Line3D line2)
{

	if ((line1.getPt1() == line2.getPt1()) && (line1.getPt2() == line2.getPt2()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

string Line3D::toString()
{
	stringstream string;
	string << right << "[" << setw(4) << pt1.getX() << ", " << setw(4) << pt1.getY() << ", " << setw(4) << pt1.getZ() << "]" << setw(3) << " " << "[" << setw(4) << pt2.getX() << ", " << setw(4) << pt2.getY() << ", " << setw(4) << pt2.getZ() << "]" << setw(3) << " " << left << setw(4) << fixed << setprecision(3) << length << endl;
	
	return string.str();
}