#include "Header.h"

Header::Header()
{

}

Header::Header(char idLengthIN, char colorMapTypeIN, char dataTypeCodeIN, short colorMapOriginIN, short colorMapLengthIN,
	char colorMapDepthIN, short xOriginIN, short yOriginIN, short widthIN, short heightIN, char bytesPerPixelIN, char imageDescriptorIN)
{
	this->idLength = idLengthIN;
	this->colorMapType = colorMapTypeIN;
	this->dataTypeCode = dataTypeCodeIN;
	this->colorMapOrigin = colorMapOriginIN;
	this->colorMapLength = colorMapLengthIN;
	this->colorMapDepth = colorMapDepthIN;
	this->xOrigin = xOriginIN;
	this->yOrigin = yOriginIN;
	this->width = widthIN;
	this->height = heightIN;
	this->bytesPerPixel = bytesPerPixelIN;
	this->imageDescriptor = imageDescriptorIN;
}

char Header::getIDLength() const
{
	return this->idLength;
}

char Header::getColorMapType() const
{
	return this->colorMapType;
}

char Header::getDataTypeCode() const
{
	return this->dataTypeCode;
}

short Header::getColorMapOrigin() const
{
	return this->colorMapOrigin;
}

short Header::getColorMapLength() const
{
	return this->colorMapLength;
}

char Header::getColorMapDepth() const
{
	return this->colorMapDepth;
}

short Header::getXOrigin() const
{
	return this->xOrigin;
}

short Header::getYOrigin() const
{
	return this->yOrigin;
}

short Header::getWidth() const
{
	return this->width;
}

short Header::getHeight() const
{
	return this->height;
}

char Header::getBytesPerPixel() const
{
	return this->bytesPerPixel;
}

char Header::getImageDescriptor() const
{
	return this->imageDescriptor;
}

void Header::PrintHeader()
{
	cout << "ID Length: " << this->idLength << endl;
	cout << "Color Map Type: " << this->colorMapType << endl;
	cout << "Data type code: " << this->dataTypeCode << endl;
	cout << "Color Map Origin: " << this->colorMapOrigin << endl;
	cout << "Color Map Length: " << this->colorMapLength << endl;
	cout << "Color Map Depth: " << this->colorMapDepth << endl;
	cout << "X Origin: " << this->xOrigin << endl;
	cout << "Y Origin: " << this->yOrigin << endl;
	cout << "Width: " << this->width << endl;
	cout << "Height: " << this->height << endl;
	cout << "Bits per pixel: " << this->bytesPerPixel << endl;
	cout << "Image Description: " << this->imageDescriptor << endl;
}