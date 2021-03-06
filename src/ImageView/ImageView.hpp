
#pragma once

#include "../View/View.hpp"

namespace ReactViews {

	class ImageView : public View {
	public:
		ImageView() = default;
		~ImageView() = default;

		void constructor(Props props) override;

		static ImageView *newInstance() { return (new ImageView()); };

		void loadFromFile(const std::string path);

		void newProps(Props props);

		View *componentRender() override;
		void componentDidUpdate() override;

	protected:
		sf::Texture _texture;
		sf::Sprite _sprite;

		bool _hasImage;
	};
}