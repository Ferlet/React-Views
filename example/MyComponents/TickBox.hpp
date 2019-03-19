
#pragma once

#include "Dom.hpp"

class TickBox : public ReactViews::View {
	public:
		TickBox() = default;
		~TickBox() = default;

		//needed
		static TickBox *newInstance() { return (new TickBox()); };


		//lifecycle
		void constructor(ReactViews::Props props) override;
		void componentDidMount();
		ReactViews::View *componentRender();
};