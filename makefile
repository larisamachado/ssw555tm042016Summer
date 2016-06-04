all: main.exe

clean:
	rm main2.o main.exe
	
main.exe: main.o
	g++ -g -o main main.o
	
main.o:
	g++ -c -g main.cpp