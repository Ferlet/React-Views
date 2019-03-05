
#pragma once

#include "../View/View.hpp"

namespace ReactViews {

	class ImageView : public View {
	public:
		ImageView() {ImageView(std::map<std::string, std::string>());};
		ImageView(Props props);
		~ImageView() = default;

		static ImageView *newInstance(Props props) { return (new ImageView(props)); };

		void loadFromFile(const std::string path);
	protected:
		sf::Texture _texture;
		sf::Sprite _sprite;

		bool _hasImage;
	};
}