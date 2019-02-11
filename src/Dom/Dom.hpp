 
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

		View &findViewById(const std::string &id);

	private:
		Dom() { _view = nullptr; _autoSet = true; };	
		Dom(Dom const&);
		void operator=(Dom const&);

		View *_view;
		//window here
		bool _autoSet;
	};

	#define DOM (ReactViews::Dom::getInstance())
}