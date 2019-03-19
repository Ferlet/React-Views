
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

	void Dom::setWindow(sf::RenderWindow &window) {
		_window = std::addressof(window);
		if (isInit())
			_view->reevaluateChildFlex(1, 1, 0, 0);
	}

	View &Dom::findViewById(const std::string &id) {
		if (!_view)
			throw std::domain_error("No view is linked to the Dom yet");
		return _view->findViewById(id);
	}

	sf::RectangleShape Dom::getLocalZone(const View &view) {
		sf::Vector2u v = _window->getSize();

		sf::RectangleShape rect(sf::Vector2f(v.x * view.getGlobalRowFlex(), v.y * view.getGlobalColumnFlex()));
 
		rect.setPosition(v.x * view.getGlobalLeftRatio(), v.y * view.getGlobalTopRatio());

		return rect;
	}

	void Dom::checkEvents() {
		if (!_view || !_window)
			throw std::domain_error("Both main View and a window must be set before using events");

		sf::Event event;

		_window->pollEvent(event);

		applyToViewTree(*_view, [&event](View &v){ v.checkEvents(event); });
	}

	void Dom::render() {
		if (_view && _window)
			_view->render();
	}

	void Dom::parseFromFile(const std::string &path) {
		bool wasDisabled = !_autoSet;

		if (_view) {
			_keeper = _view;
			unsetMainView();
		}
		enableAutoSet();

		try {
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(path.c_str());
			if (!result) {
				endParsingAndThrow(wasDisabled, std::domain_error("XML syntax error"));
			}
			evaluateDocument(doc);
		} catch (std::exception &except) {
			endParsingAndThrow(wasDisabled, except);
		}
	}

	void Dom::endParsingAndThrow(bool wasDisabled, std::exception except) {
		if (wasDisabled) {
			disableAutoSet();
		}
		if (_view) {
			_view->treeDelete();
		}
		if (_keeper) {
			_view = _keeper;
			_keeper = nullptr;
		}
		throw except;
	}

	void Dom::evaluateDocument(pugi::xml_node &node, unsigned int level, View *currentView) {
		
		if (level == 0 && getXmlChildNumber(node) > 1)
			throw std::domain_error("XML elements must be enclosed in an enclosing tag");
		for (pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it) {

			View *v = nullptr;

			Props props = parseProps(it);
			if (_factory.count(it->name())) {
				v = _factory[it->name()]();
				v->constructor(props);
			}
			else
				throw std::domain_error("Wrong tag name");
			v->mustBeCleaned();
			if (currentView == nullptr)
				_view = v;
			else {
				currentView->addChild(*v);
			}

		    evaluateDocument(*it, level + 1, v);
		}
	}

	Props Dom::parseProps(pugi::xml_node_iterator &it) {
		Props props;

		pugi::xml_attribute first = it->first_attribute();
		if (first != pugi::xml_attribute()) {
			props[first.name()] = first.value();
			pugi::xml_attribute next = first.next_attribute();
			while (next != pugi::xml_attribute()) {
				props[next.name()] = next.value();
				next = next.next_attribute();
			}
		}

		return props;
	}


	Dom::~Dom() {
		if (_view)
			_view->treeDelete();
		if (_keeper)
			_keeper->treeDelete();
	}

	void Dom::applyToViewTree(View &view, std::function<void(View &)> func) {
		func(view);
		for (View &v : view.getChilds()) {
			applyToViewTree(v, func);
		}
	}

	unsigned int Dom::getXmlChildNumber(pugi::xml_node &node) {	
		unsigned int i = 0;

		for (pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it)
			i++;
		return i;
	}
}