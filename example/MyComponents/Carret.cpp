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
}

ReactViews::View *Carret::componentRender() {
	return DOM.parseFromString(
		"<View flex='1' backgroundColor='ffffffff'>"

		"</View>"
	);
}