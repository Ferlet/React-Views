
#pragma once

#include "Dom.hpp"

class TickBox : public ReactViews::View {
	public:
		TickBox(ReactViews::Props props);
		~TickBox() = default;

		//needed
		static TickBox *newInstance(ReactViews::Props props) { return (new TickBox(props)); };

	protected:
		void loadFromFile(const std::string path);

		sf::Texture _texture;
		sf::Sprite _sprite;
};