 
#pragma once

#include "../xmlLib/pugixml.hpp"
#include "../View/View.hpp"
#include "../ImageView/ImageView.hpp"

namespace ReactViews {

	class Dom {
	public:
		static Dom &getInstance() {
			static Dom instance;

			return instance;
		}

		void enableAutoSet() { _autoSet = true; };
		void disableAutoSet() { _autoSet = false; };

		void setMainView(View &view);
		void unsetMainView();

		void setWindow(sf::RenderWindow &window);

		bool isInit() const { return _view != nullptr; };
		bool hasAutoSet() const { return _autoSet; };

		bool hasWindow() const { return _window != nullptr; };
		sf::RenderWindow *getWindow() const { return _window; };

		View &findViewById(const std::string &id);

		sf::RectangleShape getLocalZone(const View &view);

		void checkEvents();

		void render();

		void parseFromFile(const std::string &path);
		void endParsingAndThrow(bool wasDisabled, std::exception except);
		void evaluateDocument(pugi::xml_node &node, unsigned int level = 0, View *currentView = nullptr);
		View *createView(View *v, pugi::xml_node_iterator &it, View *currentView);
		View *createImageView(pugi::xml_node_iterator &it, View *currentView);

	private:
		Dom() { _view = nullptr; _keeper = nullptr; _autoSet = true; _window = nullptr; };
		Dom(Dom const&);
		~Dom();
		void operator=(Dom const&);

		void applyToViewTree(View &view, std::function<void(View &)>);

		unsigned int getXmlChildNumber(pugi::xml_node &node);

		View *_view;
		View *_keeper;
		sf::RenderWindow *_window;
		bool _autoSet;
	};

	#define DOM (ReactViews::Dom::getInstance())
}