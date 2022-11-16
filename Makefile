all: compile link

compile:
	g++ -c snek.cpp -I"C:\Users\arsen\Documents\LIBS\SFML-2.5.1\include" -DSFML_STATIC
link:
	g++ snek.o -o main -L"C:\Users\arsen\Documents\LIBS\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows
clean:
	del *.o main.exe