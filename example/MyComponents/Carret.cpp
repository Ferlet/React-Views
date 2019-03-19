#include "Carret.hpp"

void Carret::constructor(ReactViews::Props props) {
	ReactViews::View::constructor(props);
}

void Carret::componentDidMount() {

	setEvent("onLeftClick", [](ReactViews::View &view){

		View &bar = DOM.findViewById("bar");
		int inc = view.props["dir"] == "left" ? -1 : 1;
		
		bar.setState(json::makeObject({
			{"remain", bar.state["remain"].to<int>() + inc}
		}));
	});

	ReactViews::View image = _childs[0];

	if (this->props["dir"] == "left") {
		image.setState(json::makeObject({
			{"image", "./ressources/caret-left.png"}
		}));
	} else {
		image.setState(json::makeObject({
			{"image", "./ressources/caret-right.png"}
		}));
	}
}

ReactViews::View *Carret::componentRender() {
	return DOM.parseFromString(
		"<ImageView flex='1'>"

		"</ImageView>"
	);
}