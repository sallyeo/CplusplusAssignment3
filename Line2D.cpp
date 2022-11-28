#include "assn3.h"

void Line2D::setLength()
{
	length = sqrt(pow((pt1.getX() - pt2.getX()), 2) + pow((pt1.getY() - pt2.getY()), 2));
}
	
Point2D Line2D::getPt1()
{
	return pt1;
}

Point2D Line2D::getPt2()
{
	return pt2;
}

double Line2D::getScalarValue()
{
	return length;
}

void Line2D::setPt1(Point2D pt1)
{
	this->pt1 = pt1;
}

void Line2D::setPt2(Point2D pt2)
{
	this->pt2 = pt2;
}

bool operator==(Line2D line1, Line2D line2)
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

string Line2D::toString()
{
	stringstream string;
	string << "[" << right << setw(4) << pt1.getX() << ", " << setw(4) << pt1.getY() << "]" << setw(3) << " " << "[" << setw(4) << pt2.getX() << ", " << setw(4) << pt2.getY() << "]" << setw(3) << " " << left << fixed << setprecision(3) << length << endl;
	
	return string.str();
}