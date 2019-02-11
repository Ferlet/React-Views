 
#pragma once

#include "View.hpp"

namespace ReactViews {

	class Dom {
	public:
		static Dom &getInstance() {
			static Dom instance;

			return instance;
		}

		void setMainView(View *view);
		void unsetMainView();

		View &findViewById(const std::string &id);

	private:
		Dom() { _view = nullptr; };	
		Dom(Dom const&);
		void operator=(Dom const&);

		View *_view;
		//window here
	};

	#define DOM (ReactViews::Dom::getInstance())
}