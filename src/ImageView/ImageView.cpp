
#include "ImageView.hpp"

namespace ReactViews {

	void ImageView::constructor(Props props) {
		View::constructor(props);

		setRenderFunction([this](View &view){
			(void)view;
			if (_hasImage) draw(_sprite);
		});
		_hasImage = false;
		
	}

	void ImageView::loadFromFile(const std::string path) {
		_texture.loadFromFile(path);
		_sprite.setTexture(_texture);
		_hasImage = true;
	}

	void ImageView::newProps(Props props) {
		View::newProps(props);

		if (props.count("image")) loadFromFile(props["image"]);
	}
}