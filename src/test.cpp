#include "Dom.hpp"

int main() {

	ReactViews::View mainView = ReactViews::View();
	ReactViews::View v1 = ReactViews::View();
	ReactViews::View v2 = ReactViews::View();
	ReactViews::View v3 = ReactViews::View();
	ReactViews::View v4 = ReactViews::View();
	ReactViews::View v5 = ReactViews::View();

	mainView.addChild(v1);
	v1.addChild(v4);
	v1.addChild(v5);
	mainView.addChild(v2);
	mainView.addChild(v3);

	mainView.setFlex(0.2);
	v2.setFlex(0.3);
	v3.setFlex(0.3);

	DOM.setMainView(&mainView);

	std::cout << mainView << std::endl;

	return 0;
}