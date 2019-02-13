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

int main() {

	//Dom creation
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	DOM.setWindow(window);
	
	//Views creation
	ReactViews::View mainView;
	ReactViews::View v1;
	ReactViews::View v2;
	ReactViews::View v3;
	ReactViews::View v4;
	ReactViews::View v5;
	ReactViews::View v6;
	ReactViews::View v7;

	mainView.setId("main");

	//Tree building
	mainView.addChild(v1);
	{
		v1.addChild(v4);
		v1.addChild(v5);
		{
			v5.addChild(v6);
			v5.addChild(v7);	
		}
	}
	mainView.addChild(v2);
	mainView.addChild(v3);

	//Flexbox definitions
	v1.setFlexDirection(ReactViews::COLUMN);
	v2.setFlex(0.2);
	v3.setFlex(0.1);

	//Defining some style
	v4.setBackgroundColor(sf::Color::Green);
	v6.setBackgroundColor(sf::Color::Red);
	v7.setBackgroundColor(sf::Color::Yellow);
	v2.setBackgroundColor(sf::Color::White);
	v3.setBackgroundColor(sf::Color::Magenta);

	//Defining events
	v4.setOnPress([](ReactViews::View &view){
		if (view.getBackgroundColor() != sf::Color::Transparent)
			view.setBackgroundColor(sf::Color::Transparent);
		else
			view.setBackgroundColor(sf::Color::Green);
	});

	//Display
	while (window.isOpen() && !closing(window)) {
		window.clear();
		DOM.render();
		window.display();
		DOM.checkEvents();
	}

	return 0;
}