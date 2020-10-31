chess: main.c
	gcc -c CommonFunctions/CommonFunctionsC.c -o CompiledFiles/CommonFunctionsC.o
	g++ -c CommonFunctions/CommonFunctionsC++.cc -o CompiledFiles/CommonFunctionsC++.o

	g++ -c PacMan/PacMan.cc -o CompiledFiles/PacMan.o

	g++ -c Enemies/EnemiesController.cc -o CompiledFiles/EnemiesController.o
	g++ -c Enemies/GhostEnemy.cc -o CompiledFiles/GhostEnemy.o

	g++ -c MapConstruction/Food.cc -o CompiledFiles/Food.o
	g++ -c MapConstruction/Cell.cc -o CompiledFiles/Cell.o
	g++ -c MapConstruction/Stack.cc -o CompiledFiles/Stack.o

	g++ -c MapConstruction/MapClassMainFunctions.cc -o CompiledFiles/MapClassMainFunctions.o
	g++ -c MapConstruction/MapClassConstruction.cc -o CompiledFiles/MapClassConstruction.o
	g++ -c MapConstruction/MapClassHomeConstruction.cc -o CompiledFiles/MapClassHomeConstruction.o
	g++ -c MapConstruction/MapClassGame.cc -o CompiledFiles/MapClassGame.o

	g++ -c Wrapper/Wrapper.cc -o CompiledFiles/Wrapper.o
	gcc -c main.c -o CompiledFiles/main.o

	g++ CompiledFiles/main.o CompiledFiles/Wrapper.o CompiledFiles/MapClassMainFunctions.o CompiledFiles/MapClassConstruction.o CompiledFiles/MapClassHomeConstruction.o CompiledFiles/MapClassGame.o CompiledFiles/Cell.o CompiledFiles/Stack.o CompiledFiles/CommonFunctionsC.o CompiledFiles/CommonFunctionsC++.o CompiledFiles/Food.o CompiledFiles/PacMan.o CompiledFiles/EnemiesController.o CompiledFiles/GhostEnemy.o -o main -lglut -lGLU -lGL -lm 

	./main
clean:
	rm main
	rm CompiledFiles/*o