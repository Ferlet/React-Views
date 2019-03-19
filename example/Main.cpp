
#include "Dom.hpp"
#include "TickBox.hpp"

bool closing(sf::RenderWindow &window) {

	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return true;
	return false;
}

int main() {

	DOM.registerComponent("TickBox", TickBox::newInstance);

	//---------------Dom creation---------------
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	DOM.setWindow(window);
	//------------------------------------------

	//---------------XML parsing----------------
	DOM.parseFromFile("./ressources/mrc.xml");
	//------------------------------------------

	DOM.start();

	//------------------Display---------------
	while (window.isOpen() && !closing(window)) {
		window.clear();
		DOM.render();
		window.display();
		DOM.checkEvents();
	}
	//----------------------------------------

	return 0;
}