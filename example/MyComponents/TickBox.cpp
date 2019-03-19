
#include "TickBox.hpp"

void TickBox::constructor(ReactViews::Props props) {
	ReactViews::View::constructor(props);
}

void TickBox::componentDidMount() {

	setEvent("onLeftClick", [](ReactViews::View &view){

		View &v = view.getChilds()[0].get()
		.getChilds()[1].get()
		.getChilds()[1].get()
		.getChilds()[1];
		v.setVisible(!v.isVisible());
	});
}

ReactViews::View *TickBox::componentRender() {
	return DOM.parseFromString(
		"<View flex='1'>\n"
			"<View flex='0.2'/>\n"
			"<View flex='0.6' flexDirection='column'>\n"
				"<View flex='0.2'/>\n"
				"<View flex='0.6'>\n"
					"<View flex='0.2'/>"
					"<ImageView flex='0.6' image='./ressources/RedCross.png'></ImageView>"
					"<View flex='0.2'></View>"
				"</View>\n"
				"<View flex='0.2'/>\n"
			"</View>\n"
			"<View flex='0.2'/>\n"
		"</View>\n"
	);
}