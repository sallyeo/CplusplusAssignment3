#ifndef ASSN3_H
#define ASSN3_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <math.h>
#include <cmath>
#include "MyTemplates.h"

using namespace std;

// Point2D super class of Point3D class
class Point2D
{
	// Operator overloading
	friend bool operator==(Point2D, Point2D);

	protected:
		int x;
		int y;
		double distFrOrigin;
		
		virtual void setDistFrOrigin();
	
	public:	
		// Constructors
		Point2D(){};
		Point2D (int x, int y)
		{
			setX(x);
			setY(y);
			setDistFrOrigin();
		}
		
		// Accessor methods
		int getX();
		int getY();
		double getScalarValue();	// get distFrOrigin value
		
		// Mutator methods
		void setX(int x);
		void setY(int y);
		
		virtual string toString();
};

// Point3D sub class of Point2D class
class Point3D : public Point2D
{
	// Operator overloading
	friend bool operator==(Point3D, Point3D);

	protected:
		int z;

		// Overriding Point2D super class setDistFrOrigin()
		virtual void setDistFrOrigin() override;
		
	public:
		// Constructors
		Point3D(){};
		Point3D (int x, int y, int z) : Point2D (x, y)
		{
			this->z = z;
			setDistFrOrigin();
		}
		
		// Accessor methods
		int getZ();

		// Mutator methods
		void setZ(int z);
		
		// Inherits super class toString()
		virtual string toString() override;
};

// Line2D super class of Line3D class
class Line2D
{
	// Operator overloading 
	friend bool operator==(Line2D, Line2D);
	private:
		Point2D pt1;
		Point2D pt2;
		
	protected:
		double length;

		virtual void setLength();

	public:
		// Constructors
		Line2D(){};
		Line2D (Point2D pt1, Point2D pt2)
		{
			setPt1(pt1);
			setPt2(pt2);
			setLength();
		}
		
		// Accessr methods
		Point2D getPt1();
		Point2D getPt2();
		double getScalarValue();	// get length value

		// Mutator methods
		void setPt1(Point2D);
		void setPt2(Point2D);
		
		virtual string toString();
};

// Line3D sub class of Line2D class
class Line3D : public Line2D
{
	// Operator overloading
	friend bool operator==(Line3D, Line3D);

	private:
		Point3D pt1;
		Point3D pt2;
		
	protected:
		// Overriding Line2D super class setLength()
		virtual void setLength() override;
		
	public:
		// Constructors
		Line3D(){};
		Line3D (Point3D pt1, Point3D pt2)
		{
			setPt1(pt1);
			setPt2(pt2);
			setLength();
		}
		
		// Accessor methods
		Point3D getPt1();
		Point3D getPt2();
		
		// Mutator methods
		void setPt1(Point3D);
		void setPt2(Point3D);
		
		// Overriding Line2D super class toString()
		virtual string toString() override;
};	

// Function prototypes
int mainMenu();
void processChoice(int);
void resetScreen();
void returnMainMenu();
void inputData();
void filter();
void sort();
void sortOrder();
void viewData();
void storeData();
void outputSuccessMsg();
string filterString(string);
string sortString(string);
string sortOrderString(string);
// End of function prototypes

#endif