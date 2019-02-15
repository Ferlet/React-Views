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

int main() {

	//--------------SFML stuff------------------
	sf::Texture thinkingTexture;
	sf::Texture okTexture;
	thinkingTexture.loadFromFile("./ressources/thinking.png");
	okTexture.loadFromFile("./ressources/ok_hand.png");

	sf::Sprite thinkingSprite;
	sf::Sprite okSprite;
	thinkingSprite.setTexture(thinkingTexture);
	okSprite.setTexture(okTexture);

	sf::Font font;
	if (!font.loadFromFile("./ressources/arial.ttf"))
		throw std::exception();
	sf::Text text("  Clear game", font, 30);
	//------------------------------------------

	bool turn = false;

	//---------------Dom creation---------------
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	DOM.setWindow(window);
	//------------------------------------------

	//---------------XML parsing----------------
	DOM.parseFromFile("./ressources/mrc.xml");
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
	DOM.findViewById("clearButton").setRenderFunction([&text](ReactViews::View &v){
	 	v.draw(text);
	});
	//-----------------------------------------

	//---------------Defining events-----------
	std::function<void(ReactViews::View &)> squareFunc = [&turn, &thinkingSprite, &okSprite](ReactViews::View &view){
		if (view.hasRenderFunction())
			return ;
		if (turn) view.setRenderFunction([&thinkingSprite](ReactViews::View &v){v.draw(thinkingSprite);});
		else view.setRenderFunction([&okSprite](ReactViews::View &v){v.draw(okSprite);});

		turn = !turn;
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
				s << "square " << i << "-" << j;
				DOM.findViewById(s.str()).clearRenderFunction();
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