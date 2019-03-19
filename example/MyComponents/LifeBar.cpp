
#include "LifeBar.hpp"

void LifeBar::constructor(ReactViews::Props props) {
	ReactViews::View::constructor(props);

	this->state = json::makeObject({
		{"remain", 10}
	});
}

void LifeBar::componentDidMount() {

	setEvent("onLeftClick", [](ReactViews::View &view){
		if (view.state["remain"].to<int>() > 0) {
			view.setState(json::makeObject({
			 	{"remain", view.state["remain"].to<int>() - 1}
			}));

			View &bar = view.getChilds()[0].get()
				.getChilds()[1].get()
				.getChilds()[1].get()
				.getChilds()[view.state["remain"].to<int>()];

			bar.setVisible(false);
		}
		int nb = view.state["remain"].to<int>();

		std::cout << nb << std::endl;
	});
}

ReactViews::View *LifeBar::componentRender() {
	return DOM.parseFromString(
		"<View flex='1'>"
			"<View flex='0.01' backgroundColor='ffffffff'/>"
			"<View flex='0.98' flexDirection='column'>"
				"<View flex='0.1' backgroundColor='ffffffff'/>"
				"<View flex='0.8'>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
					"<View flex='0.1' backgroundColor='ff0000ff'/>"
				"</View>"
				"<View flex='0.1' backgroundColor='ffffffff'/>"
			"</View>"
			"<View flex='0.01' backgroundColor='ffffffff'/>"
		"</View>"
	);
}