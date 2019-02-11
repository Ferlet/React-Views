
#include "Dom.hpp"
#include "View.hpp"

namespace ReactViews {

	View::View() {
		_flex = 1;
		_literalFlex = 1;
		_isDefault = true;
		_direction = ROW;

		_parent = nullptr;

		_id = std::string("");

		if (!DOM.isInit() && DOM.hasAutoSet())
			DOM.setMainView(this);
	}

	View::View(const double &flex) {
		_flex = flex;
		_literalFlex = flex;
		_isDefault = false;
		_direction = ROW;

		_parent = nullptr;

		_id = std::string("");

		if (!DOM.isInit() && DOM.hasAutoSet())
			DOM.setMainView(this);
	}

	void View::setId(const std::string &id) {
		if (id == "")
			throw std::invalid_argument("Empty strings aren't valid");
		if (!isLinkedToDom())
			throw std::domain_error("Views must be linked to the Dom to be assigned an Id");
		if (isAvailableId(id)) {
			_id = id;
			return ;
		}
		throw std::domain_error("Id must be unique");
	}

	View &View::findViewById(const std::string &id) {
		if (id == "")
			throw std::invalid_argument("Empty strings aren't valid");

		if (id == getId())
			return *this;
		for (View &v : getChilds()) {
			try {
				return v.findViewById(id);
			} catch (...) {};
		}

		throw std::invalid_argument("Id not found");
	}

	bool View::isAvailableId(const std::string &id) {
		if (id == "")
			throw std::invalid_argument("Empty strings aren't valid");

		if (id == getId())
			return false;
		for (View &v : getChilds()) {
			if (v.isAvailableId(id) == false)
				return false;
		}

		return true;
	}

	void View::setFlex(const double &flex) {
		_flex = flex;
		_literalFlex = flex;
		_isDefault = false;

		if (flex < 0)
			return ;
		if (_parent != nullptr) {
			std::cout << "reevaluating" << std::endl;
			_parent->reevaluateChildFlex();
		}
		else if (_isMaster)
			_flex = 1;
	}

	void View::setFlexAsParent(const double &flex) {
		_flex = flex;
	}

	void View::setFlexDirection(const FlexDirection &dir) {
		_direction = dir;
		reevaluateChildPos();
	}

	void View::setMaster() {
		_isMaster = true;
	}

	void View::unsetMaster() {
		_isMaster = false;
	}

	void View::addChild(View &view) {
		view.setParent(this);
		_childs.push_back(view);
		reevaluateChildFlex();
	}

	void View::addChild(View &view, const unsigned int &idx) {
		view.setParent(this);
		_childs.insert(_childs.begin() + idx, view);
		reevaluateChildFlex();
	}

	void View::reevaluateChildFlex() {
		double totalFlex = 0;
		double roundedFlex = 0;
		double remainingFlex = 0;
		double intPart;
		double fractPart;
		double nbOfDefault = 0;

		if (_isMaster)
			setFlex(1);

		for (View &v : _childs) {
			if (v.isDefault())
				nbOfDefault += 1;
			else
				totalFlex += v.getLiteralFlex();
		}
		
		fractPart = modf(totalFlex, &intPart);
		roundedFlex = intPart;
		if (fractPart > 0 || intPart == 0)
			roundedFlex += 1;
		remainingFlex = roundedFlex - totalFlex;
		if (roundedFlex > 0)
			remainingFlex /= roundedFlex;

		for (View &v : _childs) {
			double ratio;
			if (v.isDefault()) {
				ratio = remainingFlex / nbOfDefault;
			}
			else {
				ratio = v.getLiteralFlex() / roundedFlex;
			}
			v.setFlexAsParent(ratio);
		}
		reevaluateChildPos();
	}

	void View::reevaluateChildPos() {

	}


	void View::setParent(View *view) {
		_parent = view;
	}

}

std::ostream& operator<< (std::ostream &stream, const ReactViews::View &view) {
	printView(stream, view, 0);

	return stream;
}

void printView(std::ostream &stream, const ReactViews::View &view, const unsigned int &floor) {

	for (unsigned int i = 0; i < floor; i++) {
		stream << "\t";
	}
	stream << view.getFlex();
	for (ReactViews::View &v : view.getChilds()) {
		stream << "\n";
		printView(stream, v, floor + 1);
	}
}