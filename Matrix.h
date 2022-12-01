#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <thread>

class Matrix {
private:
	std::vector <char> variables;
	std::vector <std::vector <double>> matrix;

	// Row Operations
	// 1.) Swap rows : std::swap()
	// 2.) Multiply by a non-zero scalar
	// 3.) Add the scalar multiple of one row to another row

	void pushDownAllZeroRows(size_t currentRow);
	bool nonZeroPivotAvailable(size_t currentRow);
	void organizeRow(size_t currentRow);
	void setZerosAbovePivot(size_t pivot);
	void setZerosBelowPivot(size_t pivot);
	void infiniteOrNoSolution() const;

public:
	Matrix(std::vector <std::vector<double>> v);
	
	void display() const;
	void rowEchelonForm();
	
};

