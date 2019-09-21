#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std; 

class Pixel
{
public:
	unsigned char redAmount;
	unsigned char blueAmount;
	unsigned char greenAmount;

	Pixel(unsigned char, unsigned char, unsigned char);

	unsigned char getRedAmount();
	unsigned char getBlueAmount();
	unsigned char getGreenAmount();
};