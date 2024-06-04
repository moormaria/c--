#include "SFML\Graphics.hpp"
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<locale>
#include<sstream>
#include<iterator>
using namespace std;
using namespace sf;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGTH 480
void main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Draw");
    while (window.isOpen()) {

        Event event;
        window.pollEvent(event);
        if (event.type == Event::Closed) window.close();



        window.display();
    }
}