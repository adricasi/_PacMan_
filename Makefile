chess: main.c
	gcc -c 	MainManager/MainManager.c -o CompiledFiles/MainManager.o
	gcc -c 	MainManager/TextureManager.c -o CompiledFiles/TextureManager.o

	g++ -c Classes/CommonFunctions/CommonFunctions.cc -o CompiledFiles/CommonFunctions.o

	g++ -c Classes/C_Player/Player.cc -o CompiledFiles/Player.o

	g++ -c Classes/C_PacMan/PacMan.cc -o CompiledFiles/PacMan.o

	g++ -c Classes/C_Enemies/EnemiesController.cc -o CompiledFiles/EnemiesController.o
	g++ -c Classes/C_Enemies/GhostEnemy.cc -o CompiledFiles/GhostEnemy.o

	g++ -c Classes/C_Food/Food.cc -o CompiledFiles/Food.o
	g++ -c Classes/C_Cell/Cell.cc -o CompiledFiles/Cell.o
	g++ -c Classes/C_Stack/Stack.cc -o CompiledFiles/Stack.o

	g++ -c Classes/C_Map/MapMainFunctions.cc -o CompiledFiles/MapMainFunctions.o
	g++ -c Classes/C_Map/MapConstruction.cc -o CompiledFiles/MapConstruction.o
	g++ -c Classes/C_Map/MapHomeConstruction.cc -o CompiledFiles/MapHomeConstruction.o
	g++ -c Classes/C_Map/MapGame.cc -o CompiledFiles/MapGame.o

	g++ -c Wrapper/Wrapper.cc -o CompiledFiles/Wrapper.o
	gcc -c main.c -o CompiledFiles/main.o

	g++ CompiledFiles/main.o CompiledFiles/Wrapper.o CompiledFiles/MapMainFunctions.o CompiledFiles/MapConstruction.o CompiledFiles/MapHomeConstruction.o CompiledFiles/MapGame.o CompiledFiles/Cell.o CompiledFiles/Stack.o CompiledFiles/CommonFunctions.o CompiledFiles/MainManager.o CompiledFiles/TextureManager.o CompiledFiles/Food.o CompiledFiles/PacMan.o CompiledFiles/EnemiesController.o CompiledFiles/Player.o CompiledFiles/GhostEnemy.o -o main -lglut -lGLU -lGL -lm -ljpeg

	./main
clean:
	rm main
	rm CompiledFiles/*o