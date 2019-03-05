
#include "TickBox.hpp"

TickBox::TickBox(ReactViews::Props props) : ReactViews::View() {

	_hasImage = false;
	if (props.count("src")) loadFromFile(props["src"]);

	setEvent("onLeftClick", [this](ReactViews::View &view){
		(void)view;
		if (hasRenderFunction()) {
			setRenderFunction([this](View &view){
	 			(void)view;
		 		if (_hasImage) draw(_sprite);
		 	});
		} else {
			clearRenderFunction();
		}
	});
}

void TickBox::loadFromFile(const std::string path) {
	_texture.loadFromFile(path);
	_sprite.setTexture(_texture);
	_hasImage = true;
}