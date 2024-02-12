// Name: ±iºÍÅï
// Date: March, 10 , 2022  
// Last Update: March, 10 , 2022  
// Problem statement: Class Point in plane
#include "Point.h"

void Point::Set(int vertical, int horizontal)
{
	this->vertical = vertical;
	this->horizontal = horizontal;
}

void Point::Move(int x, int y)
{
	this->vertical += x;
	this->horizontal += y;
}
void Point::Rotate()
{
	int temp;
	temp = this->vertical;
	this->vertical = this->horizontal;
	this->horizontal = -temp;
}
