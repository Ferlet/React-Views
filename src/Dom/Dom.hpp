 
#pragma once

#include "View.hpp"

namespace ReactViews {

	class Dom {
	public:
		static Dom &getInstance() {
			static Dom instance;

			return instance;
		}

		void enableAutoSet() { _autoSet = true; };
		void disableAutoSet() { _autoSet = false; };

		void setMainView(View *view);
		void unsetMainView();

		bool isInit() const { return _view != nullptr; };
		bool hasAutoSet() const { return _autoSet; };

		bool hasWindow() const { return _window != nullptr; };
		sf::RenderWindow *getWindow() const { return _window; };

		View &findViewById(const std::string &id);

		sf::RectangleShape getLocalZone(const View *view);

		void render();

	private:
		Dom() { _view = nullptr; _autoSet = true; _window = nullptr; };
		Dom(Dom const&);
		void operator=(Dom const&);

		View *_view;
		sf::RenderWindow *_window;
		bool _autoSet;
	};

	#define DOM (ReactViews::Dom::getInstance())
}