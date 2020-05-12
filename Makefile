main:
	g++ -std=c++11 -o Project2.o main.cpp TGAPicture.cpp Pixel.cpp Header.cpp 

clean:
	del ImageProcessing.exe
	del *.o
