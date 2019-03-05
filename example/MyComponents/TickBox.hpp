
#pragma once

#include "Dom.hpp"

class TickBox : public ReactViews::View {
	public:
		TickBox(ReactViews::Props props);
		~TickBox() = default;

		static TickBox *newInstance(ReactViews::Props props) { return (new TickBox(props)); };

		void loadFromFile(const std::string path);
	protected:
		sf::Texture _texture;
		sf::Sprite _sprite;
		bool _hasImage;
};