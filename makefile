all: compile link clean

#REMEMBER TO CHANGE PATHS
compile:
	g++ -c src/main.cpp src/grid.cpp -I"C:\Users\Pavel\Documents\libraries_for_cpp\SFML-2.6.1\include" -DSFML_STATIC
link:
	g++ main.o grid.o -o main -L"C:\Users\Pavel\Documents\libraries_for_cpp\SFML-2.6.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
clean:
	del -f main *.o