#pragma once

#include "Dom.hpp"

class Carret : public ReactViews::View {
	public:
		Carret() = default;
		~Carret() = default;

		//needed
		static Carret *newInstance() { return (new Carret()); };

		//lifecycle
		void constructor(ReactViews::Props props) override;
		void componentDidMount();
		ReactViews::View *componentRender();
};