
#include "Panel.hpp"

void Panel::constructor(ReactViews::Props props) {
	ReactViews::View::constructor(props);

	setEvent("onLeftClick", [this](ReactViews::View &view){

		ReactViews::View &shadow1 = view.findViewBySelector("shadow1");
		ReactViews::View &shadow2 = view.findViewBySelector("shadow2");

		shadow1.setVisible(false);
		shadow2.setVisible(false);

		setState(json::makeObject({{"change", state["changed"].to<bool>()}}));

	});

	state = json::makeObject({{"changed", false}});
}

void Panel::componentDidMount() {
	if (this->props.count("src")) {

		ReactViews::View &image = findViewBySelector("image");

		image.setState(json::makeObject({
			{"image", this->props["src"]}
		}));
	}
}

ReactViews::View *Panel::componentRender() {
	return DOM.parseFromString(
		"<View flex='1'>"
			"<View flex='0.98' flexDirection='column'>"
				"<View flex='0.95' backgroundColor='ffffffff'>"
					"<View flex='0.3'/>"
					"<ImageView select='image'/>"
					"<View flex='0.3'/>"
				"</View>"
				"<View flex='0.05'>"
					"<View flex='0.05'/>"
					"<View flex='0.95' backgroundColor='666666ff' select='shadow1'/>"
				"</View>"
			"</View>"
			"<View flexDirection='column'>"
				"<View flex='0.05'/>"
				"<View flex='0.95' backgroundColor='666666ff' select='shadow2'/>"
			"</View>"
		"</View>"
	);
}
