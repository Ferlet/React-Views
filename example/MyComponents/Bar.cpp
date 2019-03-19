
#include "Bar.hpp"

void Bar::constructor(ReactViews::Props props) {
	ReactViews::View::constructor(props);

	this->state = json::makeObject({
		{"remain", 10}
	});
}

void Bar::componentDidMount() {

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
	});
}

void Bar::updateRender() {
	if (this->state["remain"].to<int>() > 10)
		this->state["remain"] = 10;
	if (this->state["remain"].to<int>() < 0)
		this->state["remain"] = 0;
}

void Bar::componentDidUpdate() {
	ReactViews::View &bars = getChilds()[0].get()
				.getChilds()[1].get()
				.getChilds()[1];

	for (int i = this->state["remain"].to<int>() - 1; i >= 0; i--) {
		ReactViews::View &bar = bars.getChilds()[i];

		bar.setVisible(true);
	}

	for (int i = this->state["remain"].to<int>(); i < 10; i++) {
		ReactViews::View &bar = bars.getChilds()[i];

		bar.setVisible(false);
	}
}

ReactViews::View *Bar::componentRender() {
	return DOM.parseFromString(
		"<View flex='1'>"
			"<View flex='0.01' backgroundColor='ffffffff'/>"
			"<View flex='0.98' flexDirection='column'>"
				"<View flex='0.1' backgroundColor='ffffffff'/>"
				"<View flex='0.8'>"
					"<View id='0' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='1' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='2' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='3' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='4' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='5' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='6' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='7' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='8' flex='0.1' backgroundColor='ff0000ff'/>"
					"<View id='9' flex='0.1' backgroundColor='ff0000ff'/>"
				"</View>"
				"<View flex='0.1' backgroundColor='ffffffff'/>"
			"</View>"
			"<View flex='0.01' backgroundColor='ffffffff'/>"
		"</View>"
	);
}