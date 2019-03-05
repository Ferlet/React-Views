
#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <functional>
#include <stdexcept>
#include <math.h>

#include <SFML/Graphics.hpp>

namespace ReactViews {

	typedef enum {
		ROW,
		COLUMN
	} FlexDirection;

	class View {
	public:
		View();
		~View() = default;
		bool treeDelete();

		//used by the Dom class
		void mustBeCleaned() { _mustBeCleaned = true; };

		//ID management (can't be used without main View)
		void setId(const std::string &id);
		View &findViewById(const std::string &id);
		bool isAvailableId(const std::string &id);

		//Pure flexbox
		void setFlex(const double &flex);
		void setFlexAsParent(const double &flex);
		void setFlexDirection(const FlexDirection &dir);

		//Global Size and Position
		void setStartFlexAsParent(const double &startFlex);
		void setGlobalRowFlexAsParent(const double &globalRowFlex);
		void setGlobalColumnFlexAsParent(const double &globalColumFlex);
		void setGlobalTopRatioAsParent(const double &globalTopRatio);
		void setGlobalLeftRatioAsParent(const double &globalLeftRatio);

		//Master and Childs (DOM Tree)
		void setMaster();
		void unsetMaster();
		void addChild(View &view);
		void addChild(View &view, const unsigned int &idx);

		//Flex algorithm
		void reevaluateChildFlex(double globalRowFlex, double globalColumFlex, double globalTopRatio, double globalLeftRatio);
		void reevaluateZone();

		//Style
		void setBackgroundColor(sf::Color color);
		void setVisible(bool visible);

		//Events
		void setEvent(std::string key, std::function<void(View &)> func);
		void setOnLeftClick(std::function<void(View &)> func);
		void setOnRightClick(std::function<void(View &)> func);
		void checkEvents(sf::Event &event);

		//Render
		void draw(sf::Drawable &drawable);
		void setRenderFunction(std::function<void(View &)> func);
		void clearRenderFunction();
		void render();

		//Getters
		std::string getId() const { return _id; };
		double getFlex() const { return _flex; };
		double getLiteralFlex() const { return _literalFlex; };
		double getStartFlex() const { return _startFlex; };
		double getGlobalRowFlex() const { return _globalRowFlex; };
		double getGlobalColumnFlex() const { return _globalColumnFlex; };
		double getGlobalTopRatio() const { return _globalTopRatio; };
		double getGlobalLeftRatio() const { return _globalLeftRatio; };
		std::vector<std::reference_wrapper<View>> getChilds() const { return _childs; };
		sf::RectangleShape getZone() const { return _background; };
		sf::Color getBackgroundColor() const { return _background.getFillColor(); };
		bool isVisible() const { return _visible; };
		bool hasParent() const { return _parent != nullptr; };
		bool isDefault() const { return _isDefault; };
		bool hasRenderFunction() const { return _hasRenderFunction; };
		bool isLinkedToDom() const {
			if (_parent == nullptr && _isMaster == false)
				return false;
			return (_isMaster || _parent->isLinkedToDom());
		}

	protected:

		void setParent(View &view);

		bool _mustBeCleaned;

		std::string _id;

		double _flex;
		double _literalFlex;
		FlexDirection _direction;
		bool _isDefault;

		double _startFlex;
		double _globalRowFlex;
		double _globalColumnFlex;
		double _globalTopRatio;
		double _globalLeftRatio;

		View *_parent;
		std::vector<std::reference_wrapper<View>> _childs;

		bool _isMaster;

		sf::RectangleShape _background;
		bool _visible;

		std::map<std::string, std::function<void(View &)>> _eventMap;
		std::function<void(View &)> _renderFunction;
		bool _hasRenderFunction;
	};

}

std::ostream& operator<< (std::ostream &stream, const ReactViews::View &view);
void printView(std::ostream &stream, const ReactViews::View &view, const unsigned int &floor);