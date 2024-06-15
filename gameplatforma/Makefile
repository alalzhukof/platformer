all: main

main: source.o
	g++ source.o -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
source.o: source.cpp
	g++ -c source.cpp
clean:
	rm -rf *.o