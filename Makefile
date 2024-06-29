all: clean run

run :
	g++ -c *.cpp
	g++ *.o -o app -lsfml-graphics -lsfml-window -lsfml-system

clean : 
	rm *.o app | echo ""

