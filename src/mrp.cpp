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

int main() {

	bool turn = false;

	//---------------Dom creation---------------
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	DOM.setWindow(window);
	//------------------------------------------
	
	//--------------Views creation--------------
	ReactViews::View mainView;
	ReactViews::View game;
	ReactViews::View separator;
	ReactViews::View clearGame;
	ReactViews::View column1;
	ReactViews::View column2;
	ReactViews::View column3;
	ReactViews::View column4;
	ReactViews::View column5;
	ReactViews::View square1_1;
	ReactViews::View square1_2;
	ReactViews::View square1_3;
	ReactViews::View square2_1;
	ReactViews::View square2_2;
	ReactViews::View square2_3;
	ReactViews::View square3_1;
	ReactViews::View square3_2;
	ReactViews::View square3_3;
	ReactViews::View sep1_1;
	ReactViews::View sep1_2;
	ReactViews::View sep2_1;
	ReactViews::View sep2_2;
	ReactViews::View sep3_1;
	ReactViews::View sep3_2;
	ReactViews::View sepClearGame;
	ReactViews::View clearButton;

	//------------------------------------------

	//-------------Tree building----------------
	mainView.addChild(game);
	{
		game.addChild(column1);
		{
			column1.addChild(square1_1);
			column1.addChild(sep1_1);
			column1.addChild(square1_2);
			column1.addChild(sep1_2);
			column1.addChild(square1_3);
		}
		game.addChild(column2);
		game.addChild(column3);
		{
			column3.addChild(square2_1);
			column3.addChild(sep2_1);
			column3.addChild(square2_2);
			column3.addChild(sep2_2);
			column3.addChild(square2_3);
		}
		game.addChild(column4);
		game.addChild(column5);
		{
			column5.addChild(square3_1);
			column5.addChild(sep3_1);
			column5.addChild(square3_2);
			column5.addChild(sep3_2);
			column5.addChild(square3_3);
		}
	}
	mainView.addChild(separator);
	mainView.addChild(clearGame);
	{
		clearGame.addChild(sepClearGame);
		clearGame.addChild(clearButton);
	}
	//-----------------------------------------

	//-----------Setting some IDs--------------
	square1_1.setId("case 1-1");
	square1_2.setId("case 1-2");
	square1_3.setId("case 1-3");
	square2_1.setId("case 2-1");
	square2_2.setId("case 2-2");
	square2_3.setId("case 2-3");
	square3_1.setId("case 3-1");
	square3_2.setId("case 3-2");
	square3_3.setId("case 3-3");
	//-----------------------------------------

	//------------Flexbox definitions----------
	mainView.setFlexDirection(ReactViews::COLUMN);
	column1.setFlexDirection(ReactViews::COLUMN);
	column3.setFlexDirection(ReactViews::COLUMN);
	column5.setFlexDirection(ReactViews::COLUMN);
	game.setFlex(0.85);
	column2.setFlex(0.05);
	column4.setFlex(0.05);
	sep1_1.setFlex(0.05);
	sep1_2.setFlex(0.05);
	sep2_1.setFlex(0.05);
	sep2_2.setFlex(0.05);
	sep3_1.setFlex(0.05);
	sep3_2.setFlex(0.05);
	sepClearGame.setFlex(0.05);
	clearButton.setFlex(0.25);
	//-----------------------------------------

	//----------Defining some style------------
	column2.setBackgroundColor(sf::Color(150, 150, 150));
	column4.setBackgroundColor(sf::Color(150, 150, 150));
	sep1_1.setBackgroundColor(sf::Color(150, 150, 150));
	sep1_2.setBackgroundColor(sf::Color(150, 150, 150));
	sep2_1.setBackgroundColor(sf::Color(150, 150, 150));
	sep2_2.setBackgroundColor(sf::Color(150, 150, 150));
	sep3_1.setBackgroundColor(sf::Color(150, 150, 150));
	sep3_2.setBackgroundColor(sf::Color(150, 150, 150));
	clearButton.setBackgroundColor(sf::Color::Red);
	//-----------------------------------------

	//---------------Defining Renders----------
	sf::Font font;
	if (!font.loadFromFile("./ressources/arial.ttf"))
		throw std::exception();
	sf::Text text("  Clear game", font, 30);


	clearButton.setRenderFunction([&text](ReactViews::View &v){
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

	square1_1.setEvent("onLeftClick", squareFunc);
	square1_2.setEvent("onLeftClick", squareFunc);
	square1_3.setEvent("onLeftClick", squareFunc);
	square2_1.setEvent("onLeftClick", squareFunc);
	square2_2.setEvent("onLeftClick", squareFunc);
	square2_3.setEvent("onLeftClick", squareFunc);
	square3_1.setEvent("onLeftClick", squareFunc);
	square3_2.setEvent("onLeftClick", squareFunc);
	square3_3.setEvent("onLeftClick", squareFunc);

	clearButton.setEvent("onLeftClick", [](ReactViews::View &view){
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