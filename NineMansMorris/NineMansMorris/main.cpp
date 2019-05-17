#include "Window.h"

int main(int argc, char **argv)
{
	Window window("SDL Tutorilo", 800, 600);
	while (!window.isClosed())
	{
		window.pollEvents();
		window.clear();
	}
	
	return 0;
}