chess: main.c

	g++ -c Cell.cc -o Cell.o
	g++ -c Stack.cc -o Stack.o
	g++ -c MapClass.cc -o MapClass.o
	g++ -c Wrapper.cc -o Wrapper.o
	gcc -c main.c -o main.o
	g++ main.o Wrapper.o MapClass.o Cell.o Stack.o -o main -lglut -lGLU -lGL -lm 
	./main
clean:
	rm main