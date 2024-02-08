all: compile link clean

#REMEMBER TO CHANGE PATHS
compile:
	g++ -c src/main.cpp src/grid.cpp src/shape.cpp src/line.cpp -I"D:\Files\sfml\include" -DSFML_STATIC
link:
	g++ main.o grid.o shape.o line.o -o main -L"D:\Files\sfml\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
clean:
	del -f main *.o