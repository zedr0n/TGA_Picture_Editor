#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Header
{
public:
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bytesPerPixel;
	char imageDescriptor;

	Header();
	Header(char, char, char, short, short, char, short, short, short, short, char, char);

	char getIDLength() const;
	char getColorMapType() const;
	char getDataTypeCode() const;
	short getColorMapOrigin() const;
	short getColorMapLength() const;
	char getColorMapDepth() const;
	short getXOrigin() const;
	short getYOrigin() const;
	short getWidth() const;
	short getHeight() const;
	char getBytesPerPixel() const;
	char getImageDescriptor() const;
	void PrintHeader();
};