
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

		void setMaster();
		void unsetMaster();

		void addChild(View &view);
		void addChild(View &view, const unsigned int &idx);

		void reevaluateChildFlex();
		void reevaluateChildPos();

		void render();

		std::string getId() const { return _id; };
		double getFlex() const { return _flex; };
		double getLiteralFlex() const { return _literalFlex; };
		double getStartFlex() const { return _startFlex; };
		double getTopFlex() const { return _topFlex; };
		double getLeftFlex() const { return _leftFlex; };
		std::vector<std::reference_wrapper<View>> getChilds() const { return _childs; };

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
		double _topFlex;
		double _leftFlex;

		View *_parent;
		std::vector<std::reference_wrapper<View>> _childs;

		bool _isMaster;
	};

}

std::ostream& operator<< (std::ostream &stream, const ReactViews::View &view);
void printView(std::ostream &stream, const ReactViews::View &view, const unsigned int &floor);