
#pragma once

#include "Dom.hpp"

class TickBox : public ReactViews::View {
	public:
		TickBox() = default;
		~TickBox() = default;

		void constructor(ReactViews::Props props) override;

		//needed
		static TickBox *newInstance() { return (new TickBox()); };

	protected:
		void loadFromFile(const std::string path);

		sf::Texture _texture;
		sf::Sprite _sprite;
};