#include <string.h>
#include <sstream>
#include "Dom.hpp"

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

void eventFunction(bool &turn, ReactViews::View &view) {
	if (view.getBackgroundColor() == sf::Color::Transparent) {
		view.setBackgroundColor(turn == true ? sf::Color::Red : sf::Color::Green);
		turn = !turn;
	}
}

void displayTree(pugi::xml_node &node, int tabs = 0) {
	for (pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it) {
		for (int i = 0; i < tabs; i++)
			std::cout << "\t";
		std::cout << it->name() << ": ";
		for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {
        	std::cout << " " << ait->name() << " = " << ait->value();
    	}
	    std::cout << std::endl;
	    displayTree(*it, tabs + 1);
	}
}

int main() {

	DOM.parseFromFile("ressources/mrc.xml");

	DOM.findViewById("column3");

	//return 0;

	bool turn = false;

	//---------------Dom creation---------------
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	DOM.setWindow(window);
	//------------------------------------------
	

	//----------Defining some style------------
	DOM.findViewById("column2").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("column4").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("sep 1-1").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("sep 1-2").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("sep 2-1").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("sep 2-2").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("sep 3-1").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("sep 3-2").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("clearButton").setBackgroundColor(sf::Color::Red);
	//-----------------------------------------

	//---------------Defining Renders----------
	sf::Font font;
	if (!font.loadFromFile("./ressources/arial.ttf"))
		throw std::exception();
	sf::Text text("  Clear game", font, 30);


	DOM.findViewById("clearButton").setRenderFunction([&text](ReactViews::View &v){
	 	v.draw(text);
	});
	//-----------------------------------------

	//---------------Defining events-----------
	std::function<void(ReactViews::View &)> squareFunc = [&turn](ReactViews::View &view){
		if (view.getBackgroundColor() == sf::Color::Transparent) {
			view.setBackgroundColor(turn == true ? sf::Color::Red : sf::Color::Green);
			turn = !turn;
		}
	};

	DOM.findViewById("square 1-1").setEvent("onLeftClick", squareFunc);
	DOM.findViewById("square 1-2").setEvent("onLeftClick", squareFunc);
	DOM.findViewById("square 1-3").setEvent("onLeftClick", squareFunc);
	DOM.findViewById("square 2-1").setEvent("onLeftClick", squareFunc);
	DOM.findViewById("square 2-2").setEvent("onLeftClick", squareFunc);
	DOM.findViewById("square 2-3").setEvent("onLeftClick", squareFunc);
	DOM.findViewById("square 3-1").setEvent("onLeftClick", squareFunc);
	DOM.findViewById("square 3-2").setEvent("onLeftClick", squareFunc);
	DOM.findViewById("square 3-3").setEvent("onLeftClick", squareFunc);

	DOM.findViewById("clearButton").setEvent("onLeftClick", [](ReactViews::View &view){
		(void)view;
		for (int i = 1; i < 4; i++) {
			for (int j = 1; j < 4; j++) {
				std::stringstream s;
				s << "case " << i << "-" << j;
				DOM.findViewById(s.str()).setBackgroundColor(sf::Color::Transparent);
			}
		}
	});
	//----------------------------------------

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