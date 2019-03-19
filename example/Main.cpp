
#include "Dom.hpp"
#include "TickBox.hpp"
#include "LifeBar.hpp"
#include "Carret.hpp"

int main() {

	DOM.registerComponent("TickBox", TickBox::newInstance);
	DOM.registerComponent("LifeBar", LifeBar::newInstance);
	DOM.registerComponent("Carret", Carret::newInstance);

	//---------------Dom creation---------------
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	DOM.setWindow(window);
	//------------------------------------------

	//---------------XML parsing----------------
	DOM.parseFromFile("./ressources/mrc.xml");
	//------------------------------------------

	DOM.start();

	return 0;
}