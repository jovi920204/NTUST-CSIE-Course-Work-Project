#pragma once
//************************************************************
// The location in the board
//************************************************************

// Transfer Position change to overloading functions here
/*Please implement your code here*/
struct Position {
	int x; // X, y Coordinate
	int y;
	inline Position& operator-(int const steps) {
		if (y + 1 < 9) {
			y += steps;
			return *this;
		}
		else {
			std::cout << "Invalid location\n";
			return *this;
		}
	}
	inline Position& operator+(int const steps) {
		if (y - 1 >= 1) {
			y -= steps;
			return *this;
		}
		else {
			std::cout << "Invalid location\n";
			return *this;
		}
	}
};

/************************************************************************/
