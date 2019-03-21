#pragma once

#include "Dom.hpp"

class Panel : public ReactViews::View {
	public:

		//needed
		static Panel *newInstance() { return (new Panel()); };

		//lifecycle
		void constructor(ReactViews::Props props);

		void componentDidMount();
		ReactViews::View *componentRender();

};