all:
	g++ -w -c src/*.cpp
	g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	rm *.o
