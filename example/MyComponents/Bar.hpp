#pragma once

#include "Dom.hpp"

class Bar : public ReactViews::View {
	public:
		Bar() = default;
		~Bar() = default;

		//needed
		static Bar *newInstance() { return (new Bar()); };

		//lifecycle
		void constructor(ReactViews::Props props) override;
		void componentDidMount() override;
		ReactViews::View *componentRender() override;
		void updateRender() override;
		void componentDidUpdate() override;
};