#include "Pixel.h"

Pixel::Pixel(unsigned char redIN, unsigned char blueIN, unsigned char greenIN)
{
	this->redAmount = redIN;
	this->blueAmount = blueIN;
	this->greenAmount = greenIN;
}

unsigned char Pixel::getBlueAmount()
{
	return this->blueAmount;
}

unsigned char Pixel::getRedAmount()
{
	return this->redAmount;
}

unsigned char Pixel::getGreenAmount()
{
	return this->greenAmount;
}