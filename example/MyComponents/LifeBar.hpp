#pragma once

#include "Dom.hpp"

class LifeBar : public ReactViews::View {
	public:
		LifeBar() = default;
		~LifeBar() = default;

		//needed
		static LifeBar *newInstance() { return (new LifeBar()); };

		//lifecycle
		void constructor(ReactViews::Props props) override;
		void componentDidMount() override;
		ReactViews::View *componentRender() override;
		void updateRender() override;
		void didUpdate() override;
};