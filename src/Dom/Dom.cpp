
#include "Dom.hpp"

namespace ReactViews {

	void Dom::setMainView(View &view) {
		if (view.hasParent())
			throw std::domain_error("Main View must be the first node of its tree");

		if (_view)
			unsetMainView();
		_view = std::addressof(view);
		_view->setMaster();
		_view->reevaluateChildFlex(1, 1, 0, 0);
	}

	void Dom::unsetMainView() {
		if (_view)
			_view->unsetMaster();

		_view = nullptr;
	}

	View &Dom::findViewById(const std::string &id) {
		if (_view)
			_view->findViewById(id);
		throw std::domain_error("No view is linked to the Dom yet");
	}

	/*sf::RectangleShape Dom::getLocalZone(const View &view) {
		sf::Vector2u v = _window->getSize();
		sf::RectangleShape rect()
	}*/
}