chess: main.c

	g++ -c MapClass.cc -o MapClass.o
	g++ -c Wrapper.cc -o Wrapper.o
	gcc -c main.c -o main.o
	g++ main.o Wrapper.o MapClass.o -o main -lglut -lGLU -lGL -lm 
	./main
clean:
	rm main