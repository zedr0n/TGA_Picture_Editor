#include "TGAPicture.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void PrintMenuFiles();
void PrintOptions();
bool Test1();
bool Test2();
bool Test3();
bool Test4();
bool Test5();
bool Test6();
bool Test7();
bool Test8();
bool Test9();
bool Test10();
bool TestEC();

int main()
{
	int totalScore = 0;
	cout << "Makefile created!" << endl;
	totalScore += 10;
	if (Test1())
		totalScore += 11;
	if (Test2())
		totalScore += 11;
	if (Test3())
		totalScore += 11;
	if (Test4())
		totalScore += 11;
	if (Test5())
		totalScore += 11;
	if (Test6())
		totalScore += 11;
	if (Test7())
		totalScore += 11;
	if (Test8())
		totalScore += 11;
	if (Test9())
		totalScore += 11;
	if (Test10())
		totalScore += 11;
	if (TestEC())
		totalScore += 5;
	cout << "Testing Complete! ";
	totalScore += 15;
	cout << totalScore << "/135";
	return 0;
}

bool Test1()
{
	Picture picture;
	picture.ImportData("input\\layer1.tga");
	Picture picture2;
	picture2.ImportData("input\\pattern1.tga");
	Picture picture3;
	picture3 = picture3.multiplyBlend(picture, picture2, "test1");
	Picture picture4;
	picture4.ImportData("examples\\EXAMPLE_part1.tga");
	if (picture.TestCompare(picture3, picture4))
	{
		cout << "Test 1 is a success!" << endl;
		picture4.ExportData("test1.tga");
		return true;
	}
	else
		cout << "Test 1 is a failure!" << endl;
	return false;
}

bool Test2()
{
	Picture picture;
	picture.ImportData("input\\layer2.tga");
	Picture picture2;
	picture2.ImportData("input\\car.tga");
	Picture picture3;
	picture3 = picture3.subtractBlend(picture2, picture, "test2");
	Picture picture4;
	picture4.ImportData("examples\\EXAMPLE_part2.tga");
	if (picture.TestCompare(picture3, picture4))
	{
		cout << "Test 2 is a success!" << endl;
		picture4.ExportData("test2.tga");
		return true;
	}
	else
		cout << "Test 2 is a failure!" << endl;
	return false;
}

bool Test3()
{
	Picture picture;
	picture.ImportData("input\\layer1.tga");
	Picture picture2;
	picture2.ImportData("input\\pattern2.tga");
	Picture picture3;
	picture3 = picture3.multiplyBlend(picture, picture2, "test4");
	Picture picture4;
	picture4.ImportData("input\\text.tga");
	Picture picture5;
	picture5 = picture5.screenBlend(picture3, picture4, "test4_1.tga");
	Picture picture6;
	picture6.ImportData("examples\\EXAMPLE_part3.tga");
	if (picture.TestCompare(picture5, picture6))
	{
		cout << "Test 3 is a success!" << endl;
		picture5.ExportData("test3.tga");
		return true;
	}
	else
	{
		cout << "Test 3 is a failure!" << endl;
		picture5.ExportData("test3.tga");
	}
	return false;
}

bool Test4()
{
	Picture picture;
	picture.ImportData("input\\layer2.tga");
	Picture picture2;
	picture2.ImportData("input\\car.tga");
	Picture picture3;
	picture3 = picture3.multiplyBlend(picture2, picture, "test4");
	Picture picture4;
	picture4.ImportData("examples\\EXAMPLE_part4.tga");
	Picture picture5;
	picture5.ImportData("input\\pattern2.tga");
	Picture picture6;
	picture6 = picture6.subtractBlend(picture3, picture5, "test2");
	if (picture.TestCompare(picture3, picture4))
	{
		cout << "Test 4 is a success!" << endl;
		picture4.ExportData("test4.tga");
		return true;
	}
	else
		cout << "Test 4 is a failure!" << endl;
	return false;
}

bool Test5()
{
	Picture picture;
	picture.ImportData("input\\layer1.tga");
	Picture picture2;
	picture2.ImportData("input\\pattern1.tga");
	Picture picture3;
	picture3 = picture3.overlayBlend(picture, picture2, "test5.tga");
	Picture picture4;
	picture4.ImportData("examples\\EXAMPLE_part5.tga");
	if (picture.TestCompare(picture3, picture4))
	{
		cout << "Test 5 is a success!" << endl;
		picture3.ExportData("test5.tga");
		return true;
	}
	else
	{
		cout << "Test 5 is a failure!" << endl;
		picture3.ExportData("test5.tga");
	}
	return false;
}

bool Test6()
{
	Picture picture;
	picture.ImportData("input\\car.tga");
	Picture picture2;
	picture2 = picture2.AddChange(picture, "test6.tga", 0, 0, 200);
	Picture picture3;
	picture3.ImportData("examples\\EXAMPLE_part6.tga");
	if (picture.TestCompare(picture2, picture3))
	{
		cout << "Test 6 is a success!" << endl;
		picture2.ExportData("test6.tga");
		return true;
	}
	else
	{
		cout << "Test 6 is a failure!" << endl;
		picture2.ExportData("test6.tga");
	}
	return false;
}

bool Test7()
{
	Picture picture;
	picture.ImportData("input\\car.tga");
	Picture picture2;
	picture2 = picture2.MultiplyChange(picture, "test6.tga", 4, 0, 1);
	Picture picture3;
	picture3.ImportData("examples\\EXAMPLE_part7.tga");
	if (picture.TestCompare(picture2, picture3))
	{
		cout << "Test 7 is a success!" << endl;
		picture2.ExportData("test7.tga");
		return true;
	}
	else
	{
		cout << "Test 7 is a failure!" << endl;
		picture2.ExportData("test7.tga");
	}
	return false;
}

bool Test8()
{
	Picture picture;
	picture.ImportData("input\\car.tga");
	Picture picture2;
	picture2 = picture2.SplitRed(picture, "test8_r.tga");
	Picture picture3;
	picture3 = picture3.SplitBlue(picture, "test8_b.tga");
	Picture picture4;
	picture4 = picture4.SplitGreen(picture, "test8_g.tga");
	Picture picture5;
	picture5.ImportData("examples\\EXAMPLE_part8_r.tga");
	Picture picture6;
	picture6.ImportData("examples\\EXAMPLE_part8_b.tga");
	Picture picture7;
	picture7.ImportData("examples\\EXAMPLE_part8_g.tga");
	if (picture.TestCompare(picture2, picture5) && picture.TestCompare(picture3, picture6) && picture.TestCompare(picture4, picture7))
	{
		cout << "Test 8 is a success!" << endl;
		picture2.ExportData("test8_r.tga");
		picture3.ExportData("test8_b.tga");
		picture4.ExportData("test8_g.tga");
		return true;
	}
	else
	{
		cout << "Test 8 is a failure!" << endl;
		picture2.ExportData("test8_r.tga");
		picture3.ExportData("test8_b.tga");
		picture4.ExportData("test8_g.tga");
	}
	return false;
}

bool Test9()
{
	Picture picture;
	picture.ImportData("input\\layer_red.tga");
	Picture picture2;
	picture2.ImportData("input\\layer_blue.tga");
	Picture picture3;
	picture3.ImportData("input\\layer_green.tga");
	Picture picture4;
	picture4 = picture4.Merge(picture, picture2, picture3, "test9.tga");
	Picture picture5;
	picture5.ImportData("examples\\EXAMPLE_part9.tga");
	if (picture.TestCompare(picture4, picture5))
	{
		cout << "Test 9 is a success!" << endl;
		picture4.ExportData("test9.tga");
		return true;
	}
	else
	{
		cout << "Test 9 is a failure!" << endl;
		picture4.ExportData("test9.tga");
	}
	return false;
}

bool Test10()
{
	Picture picture;
	picture.ImportData("input\\text2.tga");
	Picture picture2;
	picture2 = picture2.verticalFlip(picture, "test10");
	Picture picture3;
	picture3.ImportData("examples\\EXAMPLE_part10.tga");
	if (picture.TestCompare(picture2, picture3))
	{
		cout << "Test 10 is a success!" << endl;
		picture2.ExportData("test10.tga");
		return true;
	}
	else
	{
		cout << "Test 10 is a failure!" << endl;
		picture2.ExportData("test10.tga");
	}
	return false;
}

bool TestEC()
{
	Picture picture;
	picture.ImportData("input\\car.tga");
	Picture picture2;
	picture2.ImportData("input\\circles.tga");
	Picture picture3;
	picture3.ImportData("input\\text.tga");
	Picture picture4;
	picture4.ImportData("input\\pattern1.tga");
	Picture picture5;
	picture5 = picture5.ExtraCredit(picture3, picture4, picture, picture2, "testEC.tga");
	Picture picture6;
	picture6.ImportData("examples\\EXAMPLE_extraCredit.tga");
	if (picture.TestCompare(picture5, picture6))
	{
		cout << "EC Test is a success!" << endl;
		picture5.ExportData("extracredit.tga");
	}
	else
	{
		picture5.ExportData("extracredit.tga");
		cout << "EC Test is a failure!" << endl;
	}
	return false;
}