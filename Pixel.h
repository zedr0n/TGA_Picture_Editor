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
	unsigned char alphaAmount;

	//Pixel(unsigned char, unsigned char, unsigned char);
	Pixel(unsigned char, unsigned char, unsigned char, unsigned char = 0);

	unsigned char getRedAmount();
	unsigned char getBlueAmount();
	unsigned char getGreenAmount();
	unsigned char getAlphaAmount();
};