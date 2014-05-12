all:
	g++ -w -c src/*.cpp -I /home/chris/lib/SFML-2.1/include/
	g++ *.o -o physics-app -L /home/chris/lib/SFML-2.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lGLU
	rm *.o
