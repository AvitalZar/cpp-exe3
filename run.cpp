#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 800), "MY Window");
	window.setPosition(Vector2i(1000,100));

	CircleShape circe(100);
	circe.setFillColor(Color(200,0,200));
	circe.setPosition(300,200);
	bool s = false;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
			
			if (event.type == Event::KeyPressed){
				if (event.key.code == Keyboard::Space){
					s = !s;
				}
			}
        }

        window.clear(sf::Color::Blue);

		if(s)
			window.draw(circe);
        window.display();
    }

    return 0;
}
