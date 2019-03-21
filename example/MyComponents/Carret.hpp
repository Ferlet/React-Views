#pragma once

#include "Dom.hpp"

class Carret : public ReactViews::View {
	public:

		//needed
		static Carret *newInstance() { return (new Carret()); };

		//lifecycle
		void constructor(ReactViews::Props props) override;
		void componentDidMount();
		ReactViews::View *componentRender();
};