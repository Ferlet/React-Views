
#include "ImageView.hpp"

namespace ReactViews {

	ImageView::ImageView() : View() {
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
}