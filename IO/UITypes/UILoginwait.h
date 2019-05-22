//////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015-2016 Daniel Allendorf                                   //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../UIElement.h"

namespace jrc
{
	class UILoginwait : public UIElement
	{
	public:
		static constexpr Type TYPE = LOGINWAIT;
		static constexpr bool FOCUSED = true;
		static constexpr bool TOGGLED = false;

		UILoginwait();
		UILoginwait(std::function<void()> okhandler);

		void draw(float alpha) const override;
		void update() override;

		void close();
		std::function<void()> get_handler();

	protected:
		Button::State button_pressed(uint16_t id) override;

	private:
		enum Buttons : uint16_t
		{
			CANCEL
		};

		std::function<void()> okhandler;
	};
}