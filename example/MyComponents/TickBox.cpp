
#include "TickBox.hpp"

TickBox::TickBox(ReactViews::Props props) : ReactViews::View(props) {

	if (props.count("src")) loadFromFile(props["src"]);

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

void TickBox::loadFromFile(const std::string path) {
	_texture.loadFromFile(path);
	_sprite.setTexture(_texture);
	
	this->setState(json::makeObject{
			{"hasImage", true},
			{"displayed", false}
		});
}