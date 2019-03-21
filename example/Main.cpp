
#include "Dom.hpp"
#include "TickBox.hpp"
#include "Bar.hpp"
#include "Carret.hpp"
#include "Panel.hpp"

int main() {

	DOM.registerComponent("TickBox", TickBox::newInstance);
	DOM.registerComponent("Bar", Bar::newInstance);
	DOM.registerComponent("Carret", Carret::newInstance);
	DOM.registerComponent("Panel", Panel::newInstance);

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