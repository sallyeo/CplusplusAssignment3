#include "assn3.h"

// Global variables to set the default filter and sorting options
string filterCriteria = "a";
string sortingCriteria = "a";
string sortingOrderCriteria = "a";

// Global variable counter to confirm user view data before storing
int counter = 0;

//Vectors to store the points and lines
vector<Point2D> point2d_vector;
vector<Point3D> point3d_vector;
vector<Line2D> line2d_vector;
vector<Line3D> line3d_vector;

// Function to clear screen
void resetScreen()
{
	system("clear");
} // End of resetScreen() ...

// Display the main menu
int mainMenu()
{
	int choice;
	
	cout << "Student ID 	: " << "4603229" << endl;
	cout << "Student Name 	: " << "SALLY" << endl;
	cout << "--------------------------------------" << endl;
	cout << "Welcome to Assn3 program!" << endl;
	cout << endl;
	cout << "1) 	Read in data" << endl;
	cout << "2) 	Specify filtering criteria (current: " << filterString(filterCriteria) << ")" << endl;
	cout << "3) 	Specify sorting criteria (current: " << sortString(sortingCriteria) << ")" << endl;
	cout << "4) 	Specify sorting order (current: " << sortOrderString(sortingOrderCriteria) << ")" << endl;
	cout << "5) 	View data" << endl;
	cout << "6) 	Store data" << endl;
	cout << "7) 	Quit" << endl;
	cout << endl;
	cout << "Please enter your choice: ";

	cin >> choice;

    // validate user input is in range
	while (cin.fail() || choice < 1 || choice > 7) 
	{
		cout << "Please enter a valid choice: ";
		cin.clear();
		cin.ignore(520, '\n');
		cin >> choice;
	}

	return choice;
} // End of mainMenu() ...

void processChoice(int choice)
{
	switch (choice)
	{
		case 1: 
			inputData();
			break;
		case 2: 
			filter();
			break;
		case 3:
			sort();
			break;
		case 4:
			sortOrder();
			break;
		case 5: 
			viewData();
			break;
		case 6:
			storeData();
			break;
		case 7:
			point2d_vector.clear();
			point3d_vector.clear();
			line2d_vector.clear();
			line3d_vector.clear();
			cout << "Exiting Program ... Success!" << endl;
			exit(0);
			break;
	}
} // End of processChoice() ...

// Option 1, loads a file and store accordingly in the vectors depending on their class type
void inputData()
{
	string infileName;
	fstream inFile;
	string aLine;
	
	cout << endl << "Please enter the filename : ";
	cin >> infileName;
	cout << endl;
	
	inFile.open(infileName.c_str(), fstream::in);

	while (getline (inFile, aLine))
	{	
		// Storing 2D-Point
		if (aLine.find("Point2D") != string::npos)
		{
			// There are 2 capturing groups, the x and y axis are in [1] and [2]
			regex integers(R"(Point2D, \[(\d*|-\d*), (\d*|-\d*)\])");
			smatch match;
			
			if (regex_search(aLine, match, integers))
			{
				// string to integer the matching string
				Point2D pointRead(stoi(match[1]), stoi(match[2])); 

				// operator overloading applied
				if (find(point2d_vector.begin(), point2d_vector.end(), pointRead) == point2d_vector.end())
				{
					point2d_vector.push_back(pointRead);
				}
			}
		}
		// Storing 3D-Point
		else if (aLine.find("Point3D") != string::npos)
		{
			Point3D pointRead;
			
			// Regular expression to extract the x and y axis
			regex integers(R"(Point3D, \[(\d*|-\d*), (\d*|-\d*), (\d*|-\d*)\])");
			smatch match;
			
			if (regex_search(aLine, match, integers))
			{	
				Point3D pointRead(stoi(match[1]), stoi(match[2]), stoi(match[3]));
			
				if (find(point3d_vector.begin(), point3d_vector.end(), pointRead) == point3d_vector.end())
				{
					point3d_vector.push_back(pointRead);
				}
			}
		}
		// Storing 2D-Line
		else if (aLine.find("Line2D") != string::npos)
		{
			regex integers(R"(Line2D, \[(\d*|-\d*), (\d*|-\d*)\], \[(\d*|-\d*), (\d*|-\d*)\])");
			smatch match;
			
			if (regex_search(aLine, match, integers))
			{
				Point2D pointRead2(stoi(match[1]), stoi(match[2]));
				Point2D pointRead3(stoi(match[3]), stoi(match[4]));

				Line2D pointRead1(pointRead2, pointRead3);
				
				if (find(line2d_vector.begin(), line2d_vector.end(), pointRead1) == line2d_vector.end())
				{
					line2d_vector.push_back(pointRead1);
				}
			}
		}
		// Storing 3D-Line
		else if (aLine.find("Line3D") != string::npos)
		{
			regex integers(R"(Line3D, \[(\d*|-\d*), (\d*|-\d*), (\d*|-\d*)\], \[(\d*|-\d*), (\d*|-\d*), (\d*|-\d*)\])");
			smatch match;
			
			if (regex_search(aLine, match, integers))
			{
				Point3D pointRead2(stoi(match[1]), stoi(match[2]), stoi(match[3]));
				Point3D pointRead3(stoi(match[4]), stoi(match[5]), stoi(match[6]));

				Line3D pointRead1(pointRead2, pointRead3);
				
				if (find(line3d_vector.begin(), line3d_vector.end(), pointRead1) == line3d_vector.end())
				{
					line3d_vector.push_back(pointRead1);
				}
			}
		}
	}
	
	// Adding all vectors size to get number of records read from messy.txt
	int recNum = point2d_vector.size() + point3d_vector.size() + line2d_vector.size() + line3d_vector.size();
	
	if (recNum > 0)
	{	
		//resetScreen();
		cout << recNum << " records read in successfully" << endl;
		cout << endl;
		cout << "Going back to main menu ..." << endl;
		cout << endl;
	}
	else
	{	
		//resetScreen();
		cout << "No records found, please try again" << endl;
		cout << endl;
	}
	
	processChoice(mainMenu());
} // End of inputData() ...

// Option 2 - filtering criteria
void filter()
{
	string flagForChange = filterCriteria;	// default is "a"
	string temp = "";	// to initiate while-loop later on
	counter = 0;
		
	cout << "[ Specifying filtering criteria (current: " << filterString(filterCriteria) << ") ]" << endl;
	cout << endl;
	cout << "a) 	Point2D records" << endl;
	cout << "b) 	Point3D records" << endl;
	cout << "c) 	Line2D records" << endl;
	cout << "d) 	Line3D records" << endl;
	cout << endl;
	
	// while loop initiated since temp="" initially
	while (temp != "a" && temp != "b" && temp != "c" && temp != "d")
	{
		cout << "Please enter your criteria (a - d) : ";
		cin >> temp;
		cin.clear();
		cin.ignore(520,'\n');
		// user input is case insensitive by converting to lowercase
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	}
	
	// filterCriteria is now selected by user and assigned via temp value
	filterCriteria = temp;
	
	if (flagForChange != filterCriteria)
	{
		sortingCriteria = "a";
		sortingOrderCriteria = "a";
	}
	
	cout << "Filter criteria successfully set to '" << filterString(filterCriteria) << "'!" << endl;
	cout << endl;
	
	returnMainMenu();
}

string filterString(string filter)
{
	if (filter == "a")
	{
		return "Point2D";
	}
	else if (filter == "b")
	{
		return "Point3D";
	}
	else if (filter == "c")
	{
		return "Line2D";
	}
	else
	{
		return "Line3D";
	}
} // End of filter() ...

// Option 3  - sorting criteris
void sort()
{
	string flagForChange = sortingCriteria;
	string temp = "";	// To initiate while-loop later on
	counter = 0;

	// Initial sortingCriteria is "a"	
	cout << "[ Specifying sorting criteria (current: " << sortString(sortingCriteria) << ") ]" << endl;
	cout << endl;
	
	// If filter Point2D
	if (filterCriteria == "a")
	{
		cout << "a) 	X ordinate value" << endl;
		cout << "b) 	Y ordinate value" << endl;
		cout << "c) 	Dist. Fr Origin value" << endl;
		cout << endl;
		
		while (temp != "a" && temp != "b" && temp != "c")
		{
			cout << "Please enter your criteria (a - c) : ";
			cin >> temp;
			cin.clear();
			cin.ignore(520,'\n');
			// user input is case insensitive by converting to lowercase
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		}
	}
	// If filter Point3D
	else if (filterCriteria == "b")
	{
		cout << "a) 	X ordinate value" << endl;
		cout << "b) 	Y ordinate value" << endl;
		cout << "c) 	Z ordinate value" << endl;
		cout << "d) 	Dist. Fr Origin value" << endl;
		cout << endl;
		
		while (temp != "a" && temp != "b" && temp != "c" && temp != "d")
		{
			cout << "Please enter your criteria (a - d) : ";
			cin >> temp;
			cin.clear();
			cin.ignore(100,'\n');
			// user input is case insensitive by converting to lowercase
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		}
	}
	// If filter Line2D
	else if (filterCriteria == "c")
	{
		cout << "a) 	Pt. 1's (x, y) values" << endl;
		cout << "b) 	Pt. 2's (x, y) values" << endl;
		cout << "c) 	Length" << endl;
		cout << endl;
		
		while (temp != "a" && temp != "b" && temp != "c")
		{
			cout << "Please enter your criteria (a - c) : ";
			cin >> temp;
			cin.clear();
			cin.ignore(100,'\n');
			// user input is case insensitive by converting to lowercase
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		}	
	}
	// If filter Line3D
	else
	{
		cout << "a) 	Pt. 1's (x, y, z) values" << endl;
		cout << "b) 	Pt. 2's (x, y, z) values" << endl;
		cout << "c) 	Length" << endl;
		cout << endl;
		
		while (temp != "a" && temp != "b" && temp != "c")
		{
			cout << "Please enter your criteria (a - c) : ";
			cin >> temp;
			cin.clear();
			cin.ignore(100,'\n');
			// user input is case insensitive by converting to lowercase
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		}	
	}
	
	// sortingCriteria is now selected by user and assigned via temp value
	sortingCriteria = temp;
	
	
	if (flagForChange != sortingCriteria)
	{
		sortingOrderCriteria = "a";
	}

	cout << "Sorting criteria successfully set to '" << sortString(sortingCriteria) << "'!" << endl;
	cout << endl;

	returnMainMenu();
} // End of sort()

// Nested if-else to display the user selection
string sortString(string sort)
{	
	// If filter Point2D
	if (filterCriteria == "a")
	{
		// If sort x-axis value
		if (sort == "a")
		{
			return "X";
		}
		// If sort y-axis value
		else if (sort == "b")
		{
			return "Y";
		}
		// If sort distance from origin value
		else
		{
			return "Dist. Fr Origin";
		}
	}
	// If filter Point3D
	else if (filterCriteria == "b")
	{
		// If sort x-axis value
		if (sort == "a")
		{
			return "X";
		}
		// If sort y-axis value
		else if (sort == "b")
		{
			return "Y";
		}
		// If sort z-axis value
		else if (sort == "c")
		{
			return "Z";
		}
		// If sort distance from origin value
		else
		{
			return "Dist. Fr Origin";
		}
	}
	// If filter Line2D or Line3D
	else
	{
		// If sort X & Y axis of Point 1
		if (sort == "a")
		{
			return "Pt. 1";
		}
		// If sort X & Y axis of Point 2
		else if (sort == "b")
		{
			return "Pt. 2";
		}
		// If sort length
		else
		{
			return "Length";
		}
	}	
} // End of sortString()

// Option 4
void sortOrder()
{
	string temp = "";	// To initiate while-loop later on
	counter = 0;
		
	cout << "[ Specifying sorting order (current: " << sortOrderString(sortingOrderCriteria) << ") ]" << endl;
	cout << endl;
	cout << "a) 	ASC (Ascending order)" << endl;
	cout << "b) 	DSC (Descending order)" << endl;
	cout << endl;
	
	while (temp != "a" && temp != "b")
	{
		cout << "Please enter your criteria (a - b) : ";
		cin >> temp;
		cin.clear();
		cin.ignore(100,'\n');
		// user input is case insensitive by converting to lowercase
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	}
	
	// sortingOrderCriteria is now selected by user and assigned via temp value
	sortingOrderCriteria = temp;
	cout << "Sorting order successfully set to '" << sortOrderString(sortingOrderCriteria) << "'!" << endl;
	cout << endl;
	
	returnMainMenu();
} // End of sortOrder() ...

string sortOrderString(string sortOrder)
{
	if (sortOrder == "a")
	{
		return "ASC";
	}
	else
	{
		return "DSC";
	}
} // End of sortOrderString() ...

// Option 5 - View Data
void viewData()
{
	cout << endl << "[ View data ... ]" << endl;
	cout << "Filtering Criteria : " << filterString(filterCriteria) << endl;
	cout << "Sorting Criteria : " << sortString(sortingCriteria) << endl;
	cout << "Sorting Order : " << sortOrderString(sortingOrderCriteria) << endl;
	cout << endl;
	
	// If filter Point2D
	if (filterCriteria == "a")
	{
		// Print header
		cout << right << setw(5) << "X" << " " << setw(5) << "Y" << setw(4) << " " << left << "Dist. Fr Origin" << endl;
		cout << "----------------------------------------" << endl;

		// If sort x-axis
		if (sortingCriteria == "a")
		{
			// If sort x-axis ascending
			if (sortingOrderCriteria == "a")
			{
				sort(point2d_vector.begin(), point2d_vector.end(), xAscending<Point2D>);
			}
			// If sort x-axis descending
			else
			{
				sort(point2d_vector.begin(), point2d_vector.end(), xDescending<Point2D>);
			}
		}
		// If sort y-axis
		else if (sortingCriteria == "b")
		{
			// If sort y-axis ascending
			if (sortingOrderCriteria == "a")
			{
				sort(point2d_vector.begin(), point2d_vector.end(), yAscending<Point2D>);
			}
			// If sort y-axis descending
			else
			{
				sort(point2d_vector.begin(), point2d_vector.end(), yDescending<Point2D>);
			}
		}
		// If sort distance from the origin value
		else
		{
			// If sort distance ascending
			if (sortingOrderCriteria == "a")
			{
				sort(point2d_vector.begin(), point2d_vector.end(), distanceAscending<Point2D>);
			}
			// If sort distance descending
			else
			{
				sort(point2d_vector.begin(), point2d_vector.end(), distanceDescending<Point2D>);
			}
		}
		
		// Display the Point2D via toString()
		for (int i = 0; i < point2d_vector.size(); i++)
		{
			cout << point2d_vector[i].toString();
		}
		cout << "----------------------------------------" << endl;
		cout << endl;
		
		// Verify there's element in the vector, for storing data later on
		if (point2d_vector.size() > 0)
		{
			counter = 1;
		}
	}
	// If filter Point3D
	else if (filterCriteria == "b")
	{
		// Print header
		cout << right << setw(5) << "X" << " " << setw(5) << "Y" << " " << setw(5) << "Z" << setw(4) << " " << left << "Dist. Fr Origin" << endl;
		cout << "----------------------------------------" << endl;
		
		// If sort x-axis
		if (sortingCriteria == "a")
		{
			// If sort x-axis ascending
			if (sortingOrderCriteria == "a")
			{
				sort(point3d_vector.begin(), point3d_vector.end(), xAscending<Point3D>);
			}
			// If sort x-axis descending
			else
			{
				sort(point3d_vector.begin(), point3d_vector.end(), xDescending<Point3D>);
			}
		}
		else if (sortingCriteria == "b")
		{
			// If sort y-axis ascending
			if (sortingOrderCriteria == "a")
			{
				sort(point3d_vector.begin(), point3d_vector.end(), yAscending<Point3D>);
			}
			// If sort y-axis descending
			else
			{
				sort(point3d_vector.begin(), point3d_vector.end(), yDescending<Point3D>);
			}
		}
		else if (sortingCriteria == "c")
		{
			// If sort z-axis ascending
			if (sortingOrderCriteria == "a")
			{
				sort(point3d_vector.begin(), point3d_vector.end(), zAscending<Point3D>);
			}
			// If sort z-axis descending
			else
			{
				sort(point3d_vector.begin(), point3d_vector.end(), zDescending<Point3D>);
			}
		}
		// If sort distance from origin value
		else
		{
			// If sort distance ascending
			if (sortingOrderCriteria == "a")
			{
				sort(point3d_vector.begin(), point3d_vector.end(), distanceAscending<Point3D>);
			}
			// If sort distance descending
			else
			{
				sort(point3d_vector.begin(), point3d_vector.end(), distanceDescending<Point3D>);
			}
		}
		
		// Displat Point3D via overriding super class Point2D toString()
		for (int i = 0; i < point3d_vector.size(); i++)
		{
			cout << point3d_vector[i].toString();
		}
		cout << "----------------------------------------" << endl;
		cout << endl;
		
		// Verify there's element in the vector, for storing data later on
		if (point3d_vector.size() > 0)
		{
			counter = 1;
		}
	}
	// If filter Line2D
	else if (filterCriteria == "c")
	{
		// Print header
		cout << right << setw(5) << "P1-X" << " " << setw(5) << "P1-Y" << setw(4) << " " << setw(5) << "P2-X" << " " << setw(5) << "P2-Y" << setw(4) << " " << left << "Length" << endl;
		cout << "----------------------------------------" << endl;
		
		// If sort point 1
		if (sortingCriteria == "a")
		{	
			// If sort point 1 ascending x and y axis
			if (sortingOrderCriteria == "a")
			{
				sort(line2d_vector.begin(), line2d_vector.end(), pt1Ascending<Line2D>);
			}
			// If sort point 1 descending x and y axis
			else
			{
				sort(line2d_vector.begin(), line2d_vector.end(), pt1Descending<Line2D>);
			}
		}
		// If sort point 2
		else if (sortingCriteria == "b")
		{
			// If sort point 2 ascending x and y axis
			if (sortingOrderCriteria == "a")
			{
				sort(line2d_vector.begin(), line2d_vector.end(), pt2Ascending<Line2D>);
			}
			// If sort point 2 descending x and y axis
			else
			{
				sort(line2d_vector.begin(), line2d_vector.end(), pt2Descending<Line2D>);
			}
		}
		// If sort Line2D length
		else if (sortingCriteria == "c")
		{
			// If sort Line2D length ascending
			if (sortingOrderCriteria == "a")
			{
				sort(line2d_vector.begin(), line2d_vector.end(), lengthAscending<Line2D>);
			}
			// If sort Line2D length descending
			else
			{
				sort(line2d_vector.begin(), line2d_vector.end(), lengthDescending<Line2D>);
			}
		}
		
		// Display Line2D info via toString()
		for (int i = 0; i < line2d_vector.size(); i++)
		{
			cout << line2d_vector[i].toString();
		}
		cout << "----------------------------------------" << endl;
		cout << endl;
		
		// Verify there's element in the vector, for storing data later on
		if (line2d_vector.size() > 0)
		{
			counter = 1;
		}
	}
	// If filter Line3D
	else
	{
		// Print header
		cout << right << setw(5) << "P1-X" << " " << setw(5) << "P1-Y" << " " << setw(5) << "P1-Z" << setw(4) << " " << setw(5) << "P2-X" << " " << setw(5) << "P2-Y" << " " << setw(5) << "P2-Z" << setw(4) << " " << left << "Length" << endl;
		cout << "--------------------------------------------------" << endl;
		
		// If sort point 1
		if (sortingCriteria == "a")
		{
			// If sort point 1 x, y, z ascending
			if (sortingOrderCriteria == "a")
			{
				sort(line3d_vector.begin(), line3d_vector.end(), pt1Ascending<Line3D>);
			}
			// If sort point 1 x, y, z descending
			else
			{
				sort(line3d_vector.begin(), line3d_vector.end(), pt1Descending<Line3D>);
			}
		}
		// If sort point 2
		else if (sortingCriteria == "b")
		{
			// If sort point 2 x, y, z ascending
			if (sortingOrderCriteria == "a")
			{
				sort(line3d_vector.begin(), line3d_vector.end(), pt2Ascending<Line3D>);
			}
			// If sort point 2 x, y, z descending
			else
			{
				sort(line3d_vector.begin(), line3d_vector.end(), pt2Descending<Line3D>);
			}
		}
		// If sort Line3D length
		else
		{
			// if sort Line3D length ascending
			if (sortingOrderCriteria == "a")
			{
				sort(line3d_vector.begin(), line3d_vector.end(), lengthAscending<Line3D>);
			}
			// if sort Line3D length descending
			else
			{
				sort(line3d_vector.begin(), line3d_vector.end(), lengthDescending<Line3D>);
			}
		}
		
		// Display Line3D info via overriding super class Line2D toString()
		for (int i = 0; i < line3d_vector.size(); i++)
		{
			cout << line3d_vector[i].toString();
		}
		cout << "--------------------------------------------------" << endl;
		cout << endl;
		
		// Verify there's element in the vector, for storing data later on
		if (line3d_vector.size() > 0)
		{
			counter = 1;
		}
	}
		
	returnMainMenu();
} // End of viewData() ...

// Option 6 - user can only store data after viewing the data
void storeData()
{
	string fileName;
	
	// If user have viewed data
	if (counter == 1)
	{
		cout << endl << "Please enter filename: ";
		cin >> fileName;
		ofstream cout(fileName);
		
		// If filter Point2D
		if (filterCriteria == "a")
		{
			// Print header
			cout << right << setw(5) << "X" << " " << setw(5) << "Y" << setw(4) << " " << left << "Dist. Fr Origin" << endl;
			cout << "----------------------------------------" << endl;
			
			// Output Point2D to output file
			for (int i = 0; i < point2d_vector.size(); i++)
			{
				cout << point2d_vector[i].toString();
			}
			cout << "----------------------------------------" << endl;
			cout << endl;
		}
		// If filter Point3D
		else if (filterCriteria == "b")
		{
			// Print header
			cout << right << setw(5) << "X" << " " << setw(5) << "Y" << " " << setw(5) << "Z" << setw(4) << " " << left << "Dist. Fr Origin" << endl;
			cout << "----------------------------------------" << endl;
			
			// Output Point3D to output file
			for (int i = 0; i < point3d_vector.size(); i++)
			{
				cout << point3d_vector[i].toString();
			}
			cout << "----------------------------------------" << endl;
			cout << endl;
		}
		// If filter Line2D
		else if (filterCriteria == "c")
		{
			// Print header
			cout << right << setw(5) << "P1-X" << " " << setw(5) << "P1-Y" << setw(4) << " " << setw(5) << "P2-X" << " " << setw(5) << "P2-Y" << setw(4) << " " << left << "Length" << endl;
			cout << "----------------------------------------" << endl;
			
			// Output Line2D to output file
			for (int i = 0; i < line2d_vector.size(); i++)
			{
				cout << line2d_vector[i].toString();
			}
			cout << "----------------------------------------" << endl;
			cout << endl;
		}
		// If filter Line3D
		else
		{
			// Print header
			cout << right << setw(5) << "P1-X" << " " << setw(5) << "P1-Y" << " " << setw(5) << "P1-Z" << setw(4) << " " << setw(5) << "P2-X" << " " << setw(5) << "P2-Y" << " " << setw(5) << "P2-Z" << setw(4) << " " << left << "Length" << endl;
			cout << "--------------------------------------------------" << endl;
		
			// Output Line3D to output file
			for (int i = 0; i < line3d_vector.size(); i++)
			{
				cout << line3d_vector[i].toString();
			}
			cout << "--------------------------------------------------" << endl;
			cout << endl;
		}
		
		cout.close();
		outputSuccessMsg();
	}
	// If user haven't view data
	else
	{
		resetScreen();
		cout << endl << "Please view the data first before storing it." << endl;
		cout << endl << "Going back to main menu ..." << endl;
		cout << endl;
	}
	
	processChoice(mainMenu());
} // End of storeData() ...

void outputSuccessMsg()
{
	resetScreen();
	cout << endl;
	
	// If filter Point2D
	if (filterCriteria == "a")
	{
		cout << point2d_vector.size() << " records output successfully!" << endl;
	}
	// If filter Point3D
	else if (filterCriteria == "b")
	{
		cout << point3d_vector.size() << " records output successfully!" << endl;
	}
	// If filter Line2D
	else if (filterCriteria == "c")
	{
		cout << line2d_vector.size() << " records output successfully!" << endl;
	}
	// If filter Line3D
	else
	{
		cout << line3d_vector.size() << " records output successfully!" << endl;
	}
	
	cout << endl;		
} // End of outputSuccessMsg() ...

//For proper transitions between options
void returnMainMenu()
{
	char enter = 'a';
	cout << endl;

	while (enter != '\n') 
    {
        cout << "Press <enter> to go back to main menu";
        cin.get(enter);
        cin.ignore();
        cin.clear();
    }
    
    cout << endl;
	
	//resetScreen();
	processChoice(mainMenu());
} // End of returnMainMenu() ...
