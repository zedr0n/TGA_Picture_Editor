#include "TGAPicture.h"

Picture::Picture()
{

}

Picture::Picture(string fileName)
{
	this->pictureName = fileName;
}

Picture::Picture(string fileName, Header headerIN, vector<Pixel> pixelsIN)
{
	this->pictureName = fileName;
	this->fileHeader = headerIN;
	this->pixelArray = pixelsIN;
}

float Picture::Boundries(float input)
{
	if (input < 0)
	{
		return 0;
	}
	else if (input > 255)
	{
		return 255;
	}
	return input;
}

Header Picture::ImportDataHeader(string fileName)
{
	char idLengthIN;
	char colorMapTypeIN;
	char dataTypeCodeIN;
	short dataMapOriginIN;
	short dataMapLengthIN;
	char colorMapDepthIN;
	short xOriginIN;
	short yOriginIN;
	short widthIN;
	short heightIN;
	char bytesPerPixelIN;
	char imageDescriptorIN;

	ifstream infile(fileName, ios_base::binary);
	infile.read(&idLengthIN, sizeof(idLengthIN));
	infile.read(&colorMapTypeIN, sizeof(colorMapTypeIN));
	infile.read(&dataTypeCodeIN, sizeof(dataTypeCodeIN));
	infile.read((char *)&dataMapOriginIN, sizeof(dataMapOriginIN));
	infile.read((char *)&dataMapLengthIN, sizeof(dataMapLengthIN));
	infile.read(&colorMapDepthIN, sizeof(colorMapDepthIN));
	infile.read((char *)&xOriginIN, sizeof(xOriginIN));
	infile.read((char *)&yOriginIN, sizeof(yOriginIN));
	infile.read((char *)&widthIN, sizeof(widthIN));
	infile.read((char *)&heightIN, sizeof(heightIN));
	infile.read(&bytesPerPixelIN, sizeof(bytesPerPixelIN));
	infile.read(&imageDescriptorIN, sizeof(imageDescriptorIN));

	Header createdHeader(idLengthIN, colorMapTypeIN, dataTypeCodeIN, dataMapOriginIN, dataMapLengthIN, colorMapDepthIN,
		xOriginIN, yOriginIN, widthIN, heightIN, bytesPerPixelIN, imageDescriptorIN);
	infile.close();
	return createdHeader;
}

vector<Pixel> Picture::ImportDataPixels(string fileName, vector<Pixel> pixelVector)
{
	
	istream& seekg(streampos pos);
	istream& seekg(streamoff off, ios_base::seek_dir way);
	ifstream infile(fileName, ios_base::binary);
	infile.seekg(18);

	char redIN;
	char blueIN;
	char greenIN;
	char alphaIN = 0;
	int numberPixels = (this->fileHeader.getHeight()) * (this->fileHeader.getWidth());
	int bitsPerPixel = this->fileHeader.bytesPerPixel;

	for (int i = 0; i < numberPixels; i++)
	{
		infile.read(&blueIN, sizeof(blueIN));
		infile.read(&greenIN, sizeof(greenIN));
		infile.read(&redIN, sizeof(redIN));
		if(bitsPerPixel == 32) {
			infile.read(&alphaIN, sizeof(alphaIN));
		}

		Pixel createdPixel((unsigned)redIN, (unsigned)blueIN, (unsigned)greenIN, (unsigned)alphaIN);
		pixelVector.push_back(createdPixel);
	}
	infile.close();
	return pixelVector;
}

void Picture::ImportData(string fileName)
{
	this->pictureName = fileName;
	this->fileHeader = ImportDataHeader(fileName);
	this->pixelArray = ImportDataPixels(fileName, this->pixelArray);
}

void Picture::ExportData(string fileName, const string& folder)
{
	string outFileName = fileName;
	if(!folder.empty())
		outFileName = folder + "\\" + outFileName;
	ofstream outFile(outFileName, ios_base::binary);
	outFile.write(&this->fileHeader.idLength, 1);
	outFile.write(&this->fileHeader.colorMapType, 1);
	outFile.write(&this->fileHeader.dataTypeCode, 1);
	outFile.write((char *)&this->fileHeader.colorMapOrigin, 2);
	outFile.write((char *)&this->fileHeader.colorMapLength, 2);
	outFile.write(&this->fileHeader.colorMapDepth, 1);
	outFile.write((char *)&this->fileHeader.xOrigin, 2);
	outFile.write((char *)&this->fileHeader.yOrigin, 2);
	outFile.write((char *)&this->fileHeader.width, 2);
	outFile.write((char *)&this->fileHeader.height, 2);
	outFile.write(&this->fileHeader.bytesPerPixel, 1);
	outFile.write(&this->fileHeader.imageDescriptor, 1);
	for (int i = 0; i < (this->fileHeader.width)*(this->fileHeader.height); i++)
	{
		outFile.write((const char *)&this->pixelArray[i].blueAmount, 1);
		outFile.write((const char *)&this->pixelArray[i].greenAmount, 1);
		outFile.write((const char *)&this->pixelArray[i].redAmount, 1);
		if(this->fileHeader.bytesPerPixel == 32)
			outFile.write((const char *)&this->pixelArray[i].alphaAmount, 1);
	}
	outFile.close();

}

Picture Picture::horizontalFlip(Picture &pic, const string& fileName)
{
	vector<Pixel> pixelsFlipped;
	for(int i = pic.fileHeader.height - 1 ; i >= 0; i--)
	{
		for(int j = 0; j < pic.fileHeader.width; j++)
		{
			pixelsFlipped.push_back(pic.pixelArray[i*pic.fileHeader.width + j]);			
		}
	}
	Picture flippedPic(fileName, pic.fileHeader, pixelsFlipped);
	return flippedPic;
}


Picture Picture::verticalFlip(Picture &pic, const string& fileName)
{
	vector<Pixel> pixelsFlipped;
	for(int i = 0 ; i < pic.fileHeader.height; i++)
	{
		for(int j = pic.fileHeader.width-1; j >= 0; j--)
		{
			pixelsFlipped.push_back(pic.pixelArray[i*pic.fileHeader.width + j]);			
		}
	}
	Picture flippedPic(fileName, pic.fileHeader, pixelsFlipped);
	return flippedPic;
}

Picture Picture::diagonalFlip(Picture &pic, const string& fileName)
{
	vector<Pixel> pixelsFlipped;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		pixelsFlipped.push_back(pic.pixelArray[pic.pixelArray.size()-i-1]);
	}
	Picture flippedPic(fileName, pic.fileHeader, pixelsFlipped);
	return flippedPic;
}

Picture Picture::multiplyBlend(Picture &pic,Picture &pic2, const string& fileName)
{
	vector<Pixel> pixelsMultiplyBlend;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		unsigned char redAmount = (((int)(pic.pixelArray[i].getRedAmount())*((int)pic2.pixelArray[i].getRedAmount())) / 255.0f) + 0.5f;
		unsigned char blueAmount = (((int)(pic.pixelArray[i].getBlueAmount())*((int)pic2.pixelArray[i].getBlueAmount())) / 255.0f) +0.5f;
		unsigned char greenAmount = (((int)(pic.pixelArray[i].getGreenAmount())*((int)pic2.pixelArray[i].getGreenAmount())) / 255.0f) +0.5f;
		Pixel newPixel(redAmount, blueAmount, greenAmount, pic.pixelArray[i].getAlphaAmount());
		pixelsMultiplyBlend.push_back(newPixel);
	}
	Picture multiplyPic(fileName, pic.fileHeader, pixelsMultiplyBlend);
	return multiplyPic;
}

Picture Picture::subtractBlend(Picture &pic, Picture &pic2, const string& fileName)
{
	vector<Pixel> pixelsSubtractBlend;
	unsigned char redAmount = '0';
	unsigned char blueAmount = '0';
	unsigned char greenAmount = '0';
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		char redAmount = Boundries(((((int)pic.pixelArray[i].getRedAmount() / 255.0f) - ((int)pic2.pixelArray[i].getRedAmount() / 255.0f)) * 255) + 0.5f);
		char blueAmount = Boundries(((((int)pic.pixelArray[i].getBlueAmount() / 255.0f) - ((int)pic2.pixelArray[i].getBlueAmount() / 255.0f)) * 255) + 0.5f);
		char greenAmount = Boundries(((((int)pic.pixelArray[i].getGreenAmount() / 255.0f) - ((int)pic2.pixelArray[i].getGreenAmount() / 255.0f)) * 255) + 0.5f);
		Pixel newPixel(redAmount, blueAmount, greenAmount, pic.pixelArray[i].getAlphaAmount());
		pixelsSubtractBlend.push_back(newPixel);
	}
	Picture subtractPic(fileName, pic.fileHeader, pixelsSubtractBlend);
	return subtractPic;
}

Picture Picture::screenBlend(Picture &pic, Picture &pic2, const string& fileName)
{
	vector<Pixel> pixelsScreenBlend;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		unsigned char redAmount = Boundries(((1 - ((1 - (pic.pixelArray[i].getRedAmount() / 255.0f))*(1 - (pic2.pixelArray[i].getRedAmount() / 255.0f)))) * 255)+0.5f);
		unsigned char blueAmount = Boundries(((1 - ((1 - (pic.pixelArray[i].getBlueAmount() / 255.0f))*(1 - (pic2.pixelArray[i].getBlueAmount() / 255.0f)))) * 255)+0.5f);
		unsigned char greenAmount = Boundries(((1 - ((1 - (pic.pixelArray[i].getGreenAmount() / 255.0f))*(1 - (pic2.pixelArray[i].getGreenAmount() / 255.0f)))) * 255)+0.5f);
		Pixel newPixel(redAmount, blueAmount, greenAmount, pic.pixelArray[i].getAlphaAmount());
		pixelsScreenBlend.push_back(newPixel);
	}
	Picture multiplyPic(fileName, pic.fileHeader, pixelsScreenBlend);
	return multiplyPic;
}

Picture Picture::overlayBlend(Picture &pic, Picture &pic2, const string& fileName)
{
	vector<Pixel> pixelsOverlayBlend;
	unsigned char redAmount = '0';
	unsigned char blueAmount = '0';
	unsigned char greenAmount = '0';
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		if ((float)pic2.pixelArray[i].redAmount <= 127.5)
			redAmount = Boundries(((2 * (pic.pixelArray[i].getRedAmount() / 255.0f)*(pic2.pixelArray[i].getRedAmount() / 255.0f)) * 255) + 0.5f);
		else
			redAmount = Boundries(((1 - (2 * (1 - (pic.pixelArray[i].getRedAmount() / 255.0f))*(1 - (pic2.pixelArray[i].getRedAmount() / 255.0f)))) * 255) + 0.5f);

		if ((float)pic2.pixelArray[i].blueAmount <= 127.5)
			blueAmount = Boundries(((2 * (pic.pixelArray[i].getBlueAmount() / 255.0f)*(pic2.pixelArray[i].getBlueAmount() / 255.0f)) * 255) + 0.5f);
		else
			blueAmount = Boundries(((1 - (2 * (1 - (pic.pixelArray[i].getBlueAmount() / 255.0f))*(1 - (pic2.pixelArray[i].getBlueAmount() / 255.0f)))) * 255) + 0.5f);

		if ((float)pic2.pixelArray[i].greenAmount <= 127.5)
			greenAmount = Boundries(((2 * (pic.pixelArray[i].getGreenAmount() / 255.0f)*(pic2.pixelArray[i].getGreenAmount() / 255.0f)) * 255) + 0.5f);
		else
			greenAmount = Boundries(((1 - (2 * (1 - (pic.pixelArray[i].getGreenAmount() / 255.0f))*(1 - (pic2.pixelArray[i].getGreenAmount() / 255.0f)))) * 255) + 0.5f);

		Pixel newPixel(redAmount, blueAmount, greenAmount, pic.pixelArray[i].alphaAmount);
		pixelsOverlayBlend.push_back(newPixel);
	}
	Picture overlayPic(fileName, pic.fileHeader, pixelsOverlayBlend);
	return overlayPic;
}

Picture Picture::AddChange(Picture &pic, string fileName, int red, int blue, int green)
{
	vector<Pixel> pixelsAddChange;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		unsigned char redAmount = Boundries((float)(pic.pixelArray[i].getRedAmount()) + red);
		unsigned char blueAmount = Boundries((float)(pic.pixelArray[i].getBlueAmount()) + blue);
		unsigned char greenAmount = Boundries((float)(pic.pixelArray[i].getGreenAmount()) + green);
		Pixel newPixel(redAmount, blueAmount, greenAmount);
		pixelsAddChange.push_back(newPixel);
	}
	Picture addPic(fileName, pic.fileHeader, pixelsAddChange);
	return addPic;
}

Picture Picture::MultiplyChange(Picture &pic, string fileName, int red, int blue, int green)
{
	vector<Pixel> pixelsMultiplyChange;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		unsigned char redAmount = Boundries((int)(pic.pixelArray[i].getRedAmount()) * red);
		unsigned char blueAmount = Boundries((int)(pic.pixelArray[i].getBlueAmount()) * blue);
		unsigned char greenAmount = Boundries((int)(pic.pixelArray[i].getGreenAmount()) * green);
		Pixel newPixel(redAmount, blueAmount, greenAmount);
		pixelsMultiplyChange.push_back(newPixel);
	}
	Picture multiplyPic(fileName, pic.fileHeader, pixelsMultiplyChange);
	return multiplyPic;
}

Picture Picture::SplitRed(Picture &pic, string fileName)
{
	vector<Pixel> pixelsRed;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		unsigned char redAmount = pic.pixelArray[i].getRedAmount();
		Pixel newPixel(redAmount, redAmount, redAmount);
		pixelsRed.push_back(newPixel);
	}
	Picture RedPic(fileName, pic.fileHeader, pixelsRed);
	return RedPic;
}

Picture Picture::SplitBlue(Picture &pic, string fileName)
{
	vector<Pixel> pixelsBlue;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		unsigned char blueAmount = pic.pixelArray[i].getBlueAmount();
		Pixel newPixel(blueAmount, blueAmount, blueAmount);
		pixelsBlue.push_back(newPixel);
	}
	Picture BluePic(fileName, pic.fileHeader, pixelsBlue);
	return BluePic;
}

Picture Picture::SplitGreen(Picture &pic, string fileName)
{
	vector<Pixel> pixelsGreen;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		unsigned char greenAmount = pic.pixelArray[i].getGreenAmount();
		Pixel newPixel(greenAmount, greenAmount, greenAmount);
		pixelsGreen.push_back(newPixel);
	}
	Picture GreenPic(fileName, pic.fileHeader, pixelsGreen);
	return GreenPic;
}

Picture Picture::Merge(Picture &pic, Picture &pic2, Picture &pic3, string fileName)
{
	vector<Pixel> pixelsMerge;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		unsigned char redAmount = pic.pixelArray[i].getRedAmount();
		unsigned char blueAmount = pic2.pixelArray[i].getBlueAmount();
		unsigned char greenAmount = pic3.pixelArray[i].getGreenAmount();
		Pixel newPixel(redAmount, blueAmount, greenAmount);
		pixelsMerge.push_back(newPixel);
	}
	Picture mergePic(fileName, pic.fileHeader, pixelsMerge);
	return mergePic;
}

Picture Picture::ExtraCredit(Picture &pic, Picture &pic2, Picture &pic3, Picture &pic4, string fileName)
{
	int TopHalf = pic.pixelArray.size() + pic2.pixelArray.size();
	int BottomHalf = pic3.pixelArray.size() + pic4.pixelArray.size();
	int counter = 0;
	int row = 0;
	int j = 0;
	int k = 0;
	vector<Pixel> EC;
	for (int i = 0; i < BottomHalf; i++)
	{
		counter++;
		if (counter == pic.fileHeader.width+1)
		{
			counter = 1;
			row++;
		}
		if (row % 2 == 0)
		{
			EC.push_back(pic.pixelArray[j]);
			j++;
		}
		else
		{
			EC.push_back(pic2.pixelArray[k]);
			k++;
		}
	}
	counter = 0;
	row = 0;
	j = 0;
	k = 0;
	for (int i = 0; i < TopHalf; i++)
	{
		counter++;
		if (counter == pic3.fileHeader.width + 1)
		{
			counter = 1;
			row++;
		}
		if (row % 2 == 0)
		{
			EC.push_back(pic3.pixelArray[j]);
			j++;
		}
		else
		{
			EC.push_back(pic4.pixelArray[k]);
			k++;
		}
	}
	Picture ECPic(fileName, pic.fileHeader, EC);
	ECPic.fileHeader.width = pic.fileHeader.width + pic2.fileHeader.width;
	ECPic.fileHeader.height = (pic.fileHeader.height + pic2.fileHeader.height);
	return ECPic;
}

bool Picture::TestCompare(Picture& pic, Picture& pic2)
{
	if (pic.fileHeader.idLength != pic2.fileHeader.idLength)
		return false;
	else if (pic.fileHeader.bytesPerPixel != pic2.fileHeader.bytesPerPixel)
		return false;
	else if (pic.fileHeader.colorMapDepth != pic2.fileHeader.colorMapDepth)
		return false;
	else if (pic.fileHeader.colorMapLength != pic2.fileHeader.colorMapLength)
		return false;
	else if (pic.fileHeader.colorMapOrigin != pic2.fileHeader.colorMapOrigin)
		return false;
	else if (pic.fileHeader.colorMapType != pic2.fileHeader.colorMapType)
		return false;
	else if (pic.fileHeader.dataTypeCode != pic2.fileHeader.dataTypeCode)
		return false;
	else if (pic.fileHeader.height != pic2.fileHeader.height)
		return false;
	else if (pic.fileHeader.width != pic2.fileHeader.width)
		return false;
	else if (pic.fileHeader.xOrigin != pic2.fileHeader.xOrigin)
		return false;
	else if (pic.fileHeader.yOrigin != pic2.fileHeader.yOrigin)
		return false;
	else if (pic.fileHeader.imageDescriptor != pic2.fileHeader.imageDescriptor)
		return false;
	for (int i = 0; i < pic.pixelArray.size(); i++)
	{
		if (pic.pixelArray[i].getRedAmount() != pic2.pixelArray[i].getRedAmount())
			return false;
		else if (pic.pixelArray[i].getRedAmount() != pic2.pixelArray[i].getRedAmount())
			return false;
		else if (pic.pixelArray[i].getRedAmount() != pic2.pixelArray[i].getRedAmount())
			return false;
	}
	return true;
}