#include <string.h>
#include <sstream>
#include <array>
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

void loadFirstScene(bool &turn, bool &mode, sf::Sprite &thinkingSprite, sf::Sprite &okSprite, std::array<std::array<int, 3>, 3> &tab) {

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
	DOM.findViewById("checkBox").setBackgroundColor(sf::Color(150, 150, 150));
	DOM.findViewById("crossBox").setBackgroundColor(sf::Color::Black);
	//-----------------------------------------

	//---------------Defining events-----------
	std::function<void(ReactViews::View &)> squareFunc = [&turn, &thinkingSprite, &okSprite](ReactViews::View &view){
		if (view.hasRenderFunction())
			return ;
		if (turn) view.setRenderFunction([&thinkingSprite](ReactViews::View &v){v.draw(thinkingSprite);});
		else view.setRenderFunction([&okSprite](ReactViews::View &v){v.draw(okSprite);});

		turn = !turn;
	};

	DOM.findViewById("square 1-1").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[0][0] = turn;});
	DOM.findViewById("square 1-2").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[0][1] = turn;});
	DOM.findViewById("square 1-3").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[0][2] = turn;});
	DOM.findViewById("square 2-1").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[1][0] = turn;});
	DOM.findViewById("square 2-2").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[1][1] = turn;});
	DOM.findViewById("square 2-3").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[1][2] = turn;});
	DOM.findViewById("square 3-1").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[2][0] = turn;});
	DOM.findViewById("square 3-2").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[2][1] = turn;});
	DOM.findViewById("square 3-3").setEvent("onLeftClick", [squareFunc, &tab, turn](ReactViews::View &view){squareFunc(view); tab[2][2] = turn;});

	DOM.findViewById("crossBox").setEvent("onLeftClick", [&mode](ReactViews::View &view){
		ReactViews::View &v = view.findViewById("crossImage");
		v.setVisible(!v.isVisible());
	});

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

	//---------------Some Variables-------------
	bool turn = false;
	bool mode = false;
	std::array<std::array<int, 3>, 3> tab = {
		std::array<int, 3>({-1, -1, -1}),
		std::array<int, 3>({-1, -1, -1}),
		std::array<int, 3>({-1, -1, -1})
	};
	//------------------------------------------

	//---------------Dom creation---------------
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	DOM.setWindow(window);
	//------------------------------------------

	loadFirstScene(turn, mode, thinkingSprite, okSprite, tab);

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