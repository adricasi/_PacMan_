chess: main.c
	gcc -c CommonFunctions/CommonFunctions.c -o CompiledFiles/CommonFunctions.o
	g++ -c MapConstruction/Food.cc -o CompiledFiles/Food.o
	g++ -c MapConstruction/Cell.cc -o CompiledFiles/Cell.o
	g++ -c MapConstruction/Stack.cc -o CompiledFiles/Stack.o
	g++ -c MapConstruction/MapClassMainFunctions.cc -o CompiledFiles/MapClassMainFunctions.o
	g++ -c MapConstruction/MapClassConstruction.cc -o CompiledFiles/MapClassConstruction.o
	g++ -c MapConstruction/MapClassHomeConstruction.cc -o CompiledFiles/MapClassHomeConstruction.o
	g++ -c Wrapper/Wrapper.cc -o CompiledFiles/Wrapper.o
	gcc -c main.c -o CompiledFiles/main.o

	g++ CompiledFiles/main.o CompiledFiles/Wrapper.o CompiledFiles/MapClassMainFunctions.o CompiledFiles/MapClassConstruction.o CompiledFiles/MapClassHomeConstruction.o CompiledFiles/Cell.o CompiledFiles/Stack.o CompiledFiles/CommonFunctions.o CompiledFiles/Food.o -o main -lglut -lGLU -lGL -lm 

	./main
clean:
	rm main
	rm CompiledFiles/*o