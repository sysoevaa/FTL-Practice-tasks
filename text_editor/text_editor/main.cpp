#include <SFML/Graphics.hpp>
#include <vector>
#include "Front.h"
#include "Back.h";
using namespace sf;

int main() {
    RenderWindow window(VideoMode(1400, 900), "Text Edit");
    BackEnd(window);
    return 0;
}
