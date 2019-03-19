
#include "TickBox.hpp"

void TickBox::constructor(ReactViews::Props props) {
	ReactViews::View::constructor(props);

	setEvent("onLeftClick", [this](ReactViews::View &view){
		(void)view;
		if (this->state["displayed"].to<bool>()) {clearRenderFunction();}
		else {setRenderFunction([this](View &view){(void)view;
		 		if (this->state["hasImage"] == true) draw(_sprite);
		 	});
		}

		this->setState(json::makeObject{
		 	{"displayed", !this->state["displayed"].to<bool>()}
		});
	});
}

void TickBox::newProps(ReactViews::Props props) {
	View::newProps(props);

	if (props.count("src")) loadFromFile(props["src"]);
}

void TickBox::loadFromFile(const std::string path) {
	_texture.loadFromFile(path);
	_sprite.setTexture(_texture);
	
	this->setState(json::makeObject{
			{"hasImage", true},
			{"displayed", false}
		});
}