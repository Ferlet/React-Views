
#pragma once

#include <string>
#include <vector>
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
		View(const double &flex);
		~View() = default;

		void setId(const std::string &id);
		View &findViewById(const std::string &id);
		bool isAvailableId(const std::string &id);

		void setFlex(const double &flex);
		void setFlexAsParent(const double &flex);
		void setFlexDirection(const FlexDirection &dir);

		void setStartFlexAsParent(const double &startFlex);
		void setGlobalRowFlexAsParent(const double &globalRowFlex);
		void setGlobalColumnFlexAsParent(const double &globalColumFlex);
		void setGlobalTopRatioAsParent(const double &globalTopRatio);
		void setGlobalLeftRatioAsParent(const double &globalLeftRatio);

		void setMaster();
		void unsetMaster();

		void addChild(View &view);
		void addChild(View &view, const unsigned int &idx);

		void reevaluateChildFlex(double globalRowFlex, double globalColumFlex, double globalTopRatio, double globalLeftRatio);

		void reevaluateZone();
		void setBackgroundColor(sf::Color color);

		void render();

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

		bool hasParent() const { return _parent != nullptr; };
		bool isDefault() const { return _isDefault; };

		bool isLinkedToDom() const {
			if (_parent == nullptr && _isMaster == false)
				return false;
			return (_isMaster || _parent->isLinkedToDom());
		}

	private:

		void setParent(View &view);

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
	};

}

std::ostream& operator<< (std::ostream &stream, const ReactViews::View &view);
void printView(std::ostream &stream, const ReactViews::View &view, const unsigned int &floor);