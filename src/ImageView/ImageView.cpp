
#include "ImageView.hpp"

namespace ReactViews {

	void ImageView::constructor(Props props) {
		View::constructor(props);

		setRenderFunction([this](View &view){
			(void)view;

			if (_hasImage && _visible) {
				draw(_sprite);
			}
		});

	}

	void ImageView::loadFromFile(const std::string path) {
		_texture.loadFromFile(path);
		_sprite.setTexture(_texture);
		_hasImage = true;
	}

	void ImageView::newProps(Props props) {
		View::newProps(props);

		_hasImage = false;
		if (props.count("image")) {
			loadFromFile(props["image"]);
		};
	}

	View *ImageView::componentRender() {

		return nullptr;
	}
}