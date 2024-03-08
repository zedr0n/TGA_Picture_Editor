#pragma once
#include "Header.h"
#include "Pixel.h"
#include <vector>
#include <string>
using namespace std;

class Picture
{
public:
	Header fileHeader;
	vector<Pixel> pixelArray;
	string pictureName;

	Picture(string);
	Picture(string, Header, vector<Pixel>);
	Picture();
	float Boundries(float);
	
	vector<Pixel> ImportDataPixels(string, vector<Pixel>);
	Header ImportDataHeader(string);
	void ImportData(string);
	void ExportData(string, const string& = "");

	Picture horizontalFlip(Picture&, const string& = "");
	Picture verticalFlip(Picture&, const string& = "");
	Picture diagonalFlip(Picture&, const string& = "");
	Picture multiplyBlend(Picture&, Picture&, const string& = "");
	Picture subtractBlend(Picture&, Picture&, const string& = "");
	Picture screenBlend(Picture&, Picture&, const string& = "");
	Picture overlayBlend(Picture&, Picture&, const string& = "");
	Picture AddChange(Picture&, string, int, int, int);
	Picture MultiplyChange(Picture&, string, int, int, int);
	Picture SplitRed(Picture&, string);
	Picture SplitBlue(Picture&, string);
	Picture SplitGreen(Picture&, string);
	Picture Merge(Picture&, Picture&, Picture&, string);
	Picture ExtraCredit(Picture&, Picture&, Picture&, Picture&, string);
	bool TestCompare(Picture&, Picture&);
};