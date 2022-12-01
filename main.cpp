#include <iostream>
#include <vector>
#include <string>

#include "Matrix.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;


int main() {

	// Format example:
	//    
	//      x   y   z   =  constant
	//     __________________________
	//      1   5   6   |    63
	//      3   4   5   |    25

	vector<vector<double>> test{ {1, 2, -2},
							     {3, 2, 6} };

	Matrix myMatrix = Matrix(test);
	myMatrix.rowEchelonForm();

	cout << "==========================================================" << endl;

	vector <vector<double>> test2{ {1, -6, -4, 0, 22},
								  {4, -22, -2, 2, 0},
								  {1, -6, -5, 3, 5},
								  {0, -3, -22, 0, 6} };

	Matrix myMatrix2 = Matrix(test2);
	myMatrix2.rowEchelonForm();

	cout << "==========================================================" << endl;

	vector<vector<double>> test3{ {1, -3, 5, 8, -2},
								  {4, -8, 4, 4, -44},
								  {3, 5, -16, 1, 18},
								  {-1, 1, -3, 1, 6} };

	Matrix myMatrix3 = Matrix(test3);
	myMatrix3.rowEchelonForm();

	cout << "==========================================================" << endl;

	vector<vector<double>> test4 { {1, 1, -1, 2, 7},
								   {0, -2, -2, -6, -12},
								   {0, 4, 4, 12, 24},
								   {0, 0, 3, 5, 15} };

	Matrix myMatrix4 = Matrix(test4);
	myMatrix4.rowEchelonForm();


	string quit;
	cout << "\nPress any key to exit... \n\n";
	getline(cin, quit);
	cin.clear();


	return 0;
}
