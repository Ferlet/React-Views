
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
		if (path == std::string("") || path == "null")
			return;
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

	void ImageView::componentDidUpdate() {
		if (this->state["image"].to<std::string>() != "") {
			loadFromFile(this->state["image"].to<std::string>());
		}
	}
}