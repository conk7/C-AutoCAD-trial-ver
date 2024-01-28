all: compile link

compile:
	g++ -c main.cpp -I"D:\Files\sfml\include" -DSFML_STATIC
link:
	g++ main.o -o main -L"D:\Files\sfml\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
# clean:
# 	rm -f main *.o