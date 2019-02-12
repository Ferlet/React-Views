
#include "Dom.hpp"
#include "View.hpp"

namespace ReactViews {

	View::View() {
		_flex = 1;
		_literalFlex = 1;
		_isDefault = true;
		_direction = ROW;

		_startFlex = 0;
		_globalRowFlex = 1;
		_globalColumnFlex = 1;
		_globalTopRatio = 0;
		_globalLeftRatio = 0;

		_parent = nullptr;

		_id = std::string("");

		_isMaster = false;

		setBackgroundColor(sf::Color::Transparent);

		if (!DOM.isInit() && DOM.hasAutoSet())
			DOM.setMainView(*this);
	}

	View::View(const double &flex) {
		_flex = flex;
		_literalFlex = flex;
		_isDefault = false;
		_direction = ROW;

		_startFlex = 0;
		_globalRowFlex = 1;
		_globalColumnFlex = 1;
		_globalTopRatio = 0;
		_globalLeftRatio = 0;

		_parent = nullptr;

		_id = std::string("");

		_isMaster = false;

		setBackgroundColor(sf::Color::Transparent);

		if (!DOM.isInit() && DOM.hasAutoSet())
			DOM.setMainView(*this);
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
			_parent->reevaluateChildFlex(_parent->getGlobalRowFlex(), _parent->getGlobalColumnFlex(), _parent->getGlobalTopRatio(), _parent->getGlobalLeftRatio());
		}
		else if (_isMaster)
			_flex = 1;
	}

	void View::setFlexAsParent(const double &flex) {
		_flex = flex;
	}

	void View::setFlexDirection(const FlexDirection &dir) {
		_direction = dir;
		reevaluateChildFlex(_globalRowFlex, _globalColumnFlex, _globalTopRatio, _globalLeftRatio);
	}

	void View::setStartFlexAsParent(const double &startFlex) {
		_startFlex = startFlex;
	}

	void View::setGlobalRowFlexAsParent(const double &globalRowFlex) {
		_globalRowFlex = globalRowFlex;
	}

	void View::setGlobalColumnFlexAsParent(const double &globalColumnFlex) {
		_globalColumnFlex = globalColumnFlex;
	}

	void View::setGlobalTopRatioAsParent(const double &globalTopRatio) {
		_globalTopRatio = globalTopRatio;
	}

	void View::setGlobalLeftRatioAsParent(const double &globalLeftRatio) {
		_globalLeftRatio = globalLeftRatio;
	}

	void View::setMaster() {
		_isMaster = true;
	}

	void View::unsetMaster() {
		_isMaster = false;
	}

	void View::addChild(View &view) {
		view.setParent(*this);
		_childs.push_back(view);
		reevaluateChildFlex(_globalRowFlex, _globalColumnFlex, _globalTopRatio, _globalLeftRatio);
	}

	void View::addChild(View &view, const unsigned int &idx) {
		view.setParent(*this);
		_childs.insert(_childs.begin() + idx, view);
		reevaluateChildFlex(_globalRowFlex, _globalColumnFlex, _globalTopRatio, _globalLeftRatio);
	}

	void View::reevaluateChildFlex(double globalRowFlex, double globalColumnFlex, double globalTopRatio, double globalLeftRatio) {
		double totalFlex = 0;
		double roundedFlex = 0;
		double remainingFlex = 0;
		double intPart;
		double fractPart;
		double nbOfDefault = 0;

		double currentStartFlex = 0;

		if (_isMaster) {
			setFlex(1);
			_globalColumnFlex = 1;
			_globalRowFlex = 1;
		}

		reevaluateZone();

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
			v.setGlobalTopRatioAsParent(globalTopRatio);
			v.setGlobalLeftRatioAsParent(globalLeftRatio);
			v.setFlexAsParent(ratio);
			v.setStartFlexAsParent(currentStartFlex);
			currentStartFlex += ratio;
			globalTopRatio += ratio * (_direction == COLUMN) * globalColumnFlex;
			globalLeftRatio += ratio * (_direction == ROW) * globalRowFlex;
			
			v.setGlobalRowFlexAsParent((_direction == ROW ? ratio * globalRowFlex : globalRowFlex));
			v.setGlobalColumnFlexAsParent((_direction == COLUMN ? ratio * globalColumnFlex : globalColumnFlex));
			v.reevaluateChildFlex(v.getGlobalRowFlex(), v.getGlobalColumnFlex(), v.getGlobalTopRatio(), v.getGlobalLeftRatio());
		}
	}

	void View::reevaluateZone() {
		if (isLinkedToDom() && DOM.hasWindow()) {
			sf::Color color = _background.getFillColor();

			_background = DOM.getLocalZone(*this);
			_background.setFillColor(color);
		}
	}

	void View::setBackgroundColor(sf::Color color) {
		_background.setFillColor(color);
	}

	void View::render() {
		if (DOM.hasWindow() && DOM.isInit()) {
			DOM.getWindow()->draw(_background);
			for (View &v : _childs)
				v.render();
		}
	}

	void View::setParent(View &view) {
		_parent = std::addressof(view);
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
	stream << "global: {top: " << view.getGlobalTopRatio() << ", left: " << view.getGlobalLeftRatio() << "} | ";
	stream << "size: {vertical: " << view.getGlobalColumnFlex() << ", horizontal: " << view.getGlobalRowFlex() << "}";
	if (view.isLinkedToDom() && DOM.hasWindow()) {
		stream << "\t-> Rect(pos = {" << view.getZone().getPosition().x << ", " << view.getZone().getPosition().y << "}, size = {" << view.getZone().getSize().x << ", " << view.getZone().getSize().y << "}";
		stream << ", color: " << (int)view.getZone().getFillColor().r << ", " << (int)view.getZone().getFillColor().g << ", " << (int)view.getZone().getFillColor().b << ")";
	}

	for (ReactViews::View &v : view.getChilds()) {
		stream << "\n";
		printView(stream, v, floor + 1);
	}
}