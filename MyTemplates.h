#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

// absolute value difference in the scalar values btw parameter 1 and 2
template <class T>
double scalar_difference(T a, T b)
{
	return fabs(a.getScalarValue() - b.getScalarValue());
}

// given in the question
template <class T>
bool equals(T a, T b)
{
	return (a == b);
}

template <class T>
bool xAscending(T a, T b)
{ 
	return a.getX() < b.getX() || a.getX() == b.getX() && a.getY() < b.getY();
}

template <class T>
bool xDescending(T a, T b)
{ 
	return a.getX() > b.getX() || (a.getX() == b.getX() && a.getY() > b.getY());
}

template <class T>
bool yAscending(T a, T b)
{ 
	return a.getY() < b.getY() || (a.getY() == b.getY() && a.getX() < b.getX());
}

template <class T>
bool yDescending(T a, T b)
{ 
	return a.getY() > b.getY() || (a.getY() == b.getY() && a.getX() > b.getX());
}

template <class T>
bool zAscending(T a, T b)
{ 
	return a.getZ() < b.getZ() || (a.getZ() == b.getZ() && a.getY() < b.getY()) || (a.getZ() == b.getZ() && a.getY() == b.getY() && a.getX() < b.getX());
}

template <class T>
bool zDescending(T a, T b)
{ 
	return a.getZ() > b.getZ() || (a.getZ() == b.getZ() && a.getY() > b.getY()) || (a.getZ() == b.getZ() && a.getY() == b.getY() && a.getX() > b.getX());
}

template <class T>
bool distanceAscending(T a, T b)
{ 
	return a.getScalarValue() < b.getScalarValue() || (a.getScalarValue() == b.getScalarValue() && a.getX() < b.getX());
}

template <class T>
bool distanceDescending(T a, T b)
{ 
	return a.getScalarValue() > b.getScalarValue() || (a.getScalarValue() == b.getScalarValue() && a.getX() > b.getX());
}

template <class T>
bool pt1Ascending(T a, T b)
{
	return a.getPt1().getX() < b.getPt1().getX() || (a.getPt1().getX() == b.getPt1().getX() && a.getPt1().getY() < b.getPt1().getY());
}

template <class T>
bool pt1Descending(T a, T b)
{
	return a.getPt1().getX() > b.getPt1().getX() || (a.getPt1().getX() == b.getPt1().getX() && a.getPt1().getY() > b.getPt1().getY());
}

template <class T>
bool pt2Ascending(T a, T b)
{
	return a.getPt2().getX() < b.getPt2().getX() || (a.getPt2().getX() == b.getPt2().getX() && a.getPt2().getY() < b.getPt2().getY());
}

template <class T>
bool pt2Descending(T a, T b)
{
	return a.getPt2().getX() > b.getPt2().getX() || (a.getPt2().getX() == b.getPt2().getX() && a.getPt2().getY() > b.getPt2().getY());
}

template <class T>
bool lengthAscending(T a, T b)
{
	return a.getScalarValue() < b.getScalarValue() || a.getScalarValue() == b.getScalarValue() && a.getPt1().getX() < b.getPt1().getX();
}

template <class T>
bool lengthDescending(T a, T b)
{
	return a.getScalarValue() > b.getScalarValue() || a.getScalarValue() == b.getScalarValue() && a.getPt1().getX() > b.getPt1().getX();
}

#endif