
#pragma once

#include "../View/View.hpp"

namespace ReactViews {

	class ImageView : public View {
	public:
		ImageView();
		~ImageView() = default;

		void loadFromFile(const std::string path);
	private:
		sf::Texture _texture;
		sf::Sprite _sprite;

		bool _hasImage;
	};
}