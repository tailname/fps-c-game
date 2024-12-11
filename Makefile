all:
	g++ -I "D:\Program Files\dependenses\SFML-2.6.2\include"  -L "D:\Program Files\dependenses\SFML-2.6.2\lib" -o main main.cpp -lsfml-graphics -lsfml-window -lsfml-system

tinyxml.o: src\tinyxml2.cpp
	g++ -c src\tinyxml2.cpp
