all: compile link clean

#REMEMBER TO CHANGE PATHS
compile:
	g++ -c src/main.cpp src/grid.cpp src/shape.cpp src/line.cpp src/algorithm.cpp src/isOnVerts.cpp -I"D:\OCHKO\SFML-2.6.1\include" -DSFML_STATIC
link:
	g++ main.o grid.o isOnVerts.o shape.o line.o algorithm.o -o main -L"D:\OCHKO\SFML-2.6.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
clean:
	del -f main *.o