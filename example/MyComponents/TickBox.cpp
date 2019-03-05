
#include "TickBox.hpp"

TickBox::TickBox(ReactViews::Props props) : ReactViews::View(props) {

	_hasImage = false;
	if (props.count("src")) loadFromFile(props["src"]);

	setEvent("onLeftClick", [this](ReactViews::View &view){
		(void)view;
		if (hasRenderFunction()) {
			clearRenderFunction();
		} else {
			setRenderFunction([this](View &view){
	 			(void)view;
		 		if (_hasImage) draw(_sprite);
		 	});
		}
	});
}

void TickBox::loadFromFile(const std::string path) {
	_texture.loadFromFile(path);
	_sprite.setTexture(_texture);
	_hasImage = true;
}