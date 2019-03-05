
#include "ImageView.hpp"

namespace ReactViews {

	ImageView::ImageView(Props props) : View(props) {
		setRenderFunction([this](View &view){
			(void)view;
			if (_hasImage) draw(_sprite);
		});
		_hasImage = false;

		if (props.count("image")) loadFromFile(props["image"]);
	}

	void ImageView::loadFromFile(const std::string path) {
		_texture.loadFromFile(path);
		_sprite.setTexture(_texture);
		_hasImage = true;
	}
}