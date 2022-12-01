#include "Matrix.h"

using std::vector;
using std::cout;

void Matrix::pushDownAllZeroRows(size_t currentRow) {

	for(size_t i{ currentRow }; i < matrix.size(); ++i) {

		// reset for each row
		bool allZeroRow{ true };

		// matrix[i].size() - 1 because the last column may be 0 = 5 (no solution) or 0 = 0 infinite solutions
		//   && !nonzeroFound for speed
		for(size_t j{ 0 }; j < matrix[i].size() - 1 && allZeroRow; ++j) {
			if(matrix[i][j] != 0) {
				allZeroRow = false;
			}
		}

		if(allZeroRow) {
			// Copy the all zero row and push it to the end
			matrix.push_back(matrix[i]);

			// Erase the original all zero row
			matrix.erase(matrix.begin() + i);
		}


	}
}

bool Matrix::nonZeroPivotAvailable(size_t currentRow) {

	// The pivot is a 0, this is a problem
	if(matrix[currentRow][currentRow] == 0) {

		bool swapSuccess{ false };
		size_t nextRowCounter{ 1 };


		while(matrix[currentRow][currentRow] == 0) {

			if(currentRow + nextRowCounter < matrix.size()) {

				std::swap(matrix[currentRow], matrix[currentRow + nextRowCounter]);

				++nextRowCounter;
			}
			// currentRow + nextRowCounter is longer than the matrix. There are no rows to swap with
			else {
				return false;
			}

		}

		// matrix[currentRow][currentRow] no longer equals 0
		return true;

	}
	// The pivot isn't zero, just move on
	else {
		return true;
	}
}

Matrix::Matrix(std::vector<std::vector<double>> v) : matrix(v) {

}

void Matrix::display() const {
	cout << std::fixed << std::setprecision(1);

	for(size_t i{ 0 }; i < matrix.size(); ++i) {
		for(size_t j{ 0 }; j < matrix[i].size(); ++j) {
			cout << std::setw(8) << matrix[i][j];
		}
		cout << "\n";
	}

	cout << "\n\n";
}

void Matrix::rowEchelonForm() {

	for(size_t i{ 0 }; i < matrix.size(); ++i) {
		pushDownAllZeroRows(i);

		if(nonZeroPivotAvailable(i)) {
			organizeRow(i);

			cout << "\nRow #" << i + 1 << " organized...\n";
			display();

		}
		else {
			infiniteOrNoSolution();
		}
	}
}

void Matrix::organizeRow(size_t pivot) {

	// "Force" the pivot equal to 1
	if(matrix[pivot][pivot] != 1) {
		double scalar{ 1 / matrix[pivot][pivot] };

		for(size_t i{ 0 }; i < matrix[pivot].size(); ++i) {
			matrix[pivot][i] *= scalar;
		}
	}

	// At this point, the pivot is equal to 1

	// Trying some multithreading
	// I think it's ill-advised to access the same data with two different threads, but
	// these shouldn't mess with each other.
	std::thread above(&Matrix::setZerosAbovePivot, this, pivot);
	std::thread below(&Matrix::setZerosBelowPivot, this, pivot);

	// as
	above.join();
	// so
	below.join();
}

void Matrix::setZerosAbovePivot(size_t pivot) {
	//============================================
	// Set the numbers above the pivot to zero
	//============================================
	// Apparently the "i >= 0 " conditiion is always true for the size_t data type, so
	// I need to cast to an int here
	for(int i = static_cast<int> (pivot - 1); i >= 0; --i) {
		double scalar{ matrix[i][pivot] };
		vector<double> scalarMultiplyRow;

		for(size_t j{ 0 }; j < matrix[i].size(); ++j) {
			scalarMultiplyRow.push_back(scalar * matrix[pivot][j]);
		}

		for(size_t j{ 0 }; j < matrix[i].size(); ++j) {
			matrix[i][j] = matrix[i][j] - scalarMultiplyRow[j];
		}

	}

}

void Matrix::setZerosBelowPivot(size_t pivot) {
	// ================================================
	// Set the numbers below the pivot to zero
	// ================================================
	for(size_t i{ pivot + 1 }; i < matrix.size(); ++i) {
		// The pivot is equal to 1, so the numbers under the pivot can be multiplied by the scalar, 
		// then subtracted by that.
		double scalar{ matrix[i][pivot]};
		vector<double> scalarMultiplyRow;

		// Make the scalar row to be subtracted to the row below to make the number below the pivot = 0
		for(size_t j{ 0 }; j < matrix[i].size(); ++j) {
			scalarMultiplyRow.push_back(scalar * matrix[pivot][j]);
		}

		for(size_t j{ 0 }; j < matrix[i].size(); ++j) {
			matrix[i][j] = matrix[i][j] - scalarMultiplyRow[j];
		}
	}
}

void Matrix::infiniteOrNoSolution() const {
	// The entire row should be zero: 0 = 0
	if(matrix[matrix.size() - 1][matrix[matrix.size()-1].size() - 1] == 0) {
		cout << "Infinitely many solutions.\n\n";
	}
	else {
		cout << "No solution.\n\n";
	}
}