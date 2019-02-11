
#include "Dom.hpp"

namespace ReactViews {

	void Dom::setMainView(View *view) {
		if (_view)
			unsetMainView();
		_view = view;
		_view->setMaster();
		_view->reevaluateChildFlex();
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
}