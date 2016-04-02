/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 Daniel Allendorf                                        //
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
#include "PetLook.h"
#include "Constants.h"

#include "nlnx\nx.hpp"
#include "nlnx\node.hpp"

namespace Character
{
	PetLook::PetLook(int32_t iid, string nm, int32_t uqid,
		Point<int16_t> pos, uint8_t st, int32_t) {

		itemid = iid;
		name = nm;
		uniqueid = uqid;
		setposition(pos.x(), pos.y());
		setstance(st);

		namelabel = Text(Text::A13M, Text::CENTER, Text::WHITE);
		namelabel.settext(name);
		namelabel.setback(Text::NAMETAG);

		string strid = std::to_string(iid);

		node src = nl::nx::item["Pet"][strid + ".img"];

		animations[MOVE] = src["move"];
		animations[STAND] = src["stand0"];
		animations[JUMP] = src["jump"];
		animations[ALERT] = src["alert"];
		animations[PRONE] = src["prone"];
		animations[FLY] = src["fly"];
		animations[HANG] = src["hang"];

		node effsrc = nl::nx::effect["PetEff.img"][strid];

		animations[WARP] = effsrc["warp"];
	}

	PetLook::PetLook()
	{
		itemid = 0;
		name = "";
		uniqueid = 0;
		stance = Stance::STAND;
	}

	void PetLook::draw(Point<int16_t> viewpos, float inter) const
	{
		using Graphics::DrawArgument;
		Point<int16_t> absp = phobj.getposition(inter) + viewpos;

		animations[stance].draw(DrawArgument(absp, flip), inter);
		namelabel.draw(absp);
	}

	void PetLook::update(const Physics& physics, Point<int16_t> charpos)
	{
		static const double PETWALKFORCE = 0.35;
		static const double PETFLYFORCE = 0.2;

		Point<int16_t> curpos = phobj.getposition(1.0f);
		switch (stance)
		{
		case STAND:
		case MOVE:
			if (curpos.distance(charpos) > 150)
			{
				setposition(charpos.x(), charpos.y());
			}
			else
			{
				if (charpos.x() - curpos.x() > 50)
				{
					phobj.hforce = PETWALKFORCE;
					flip = true;
					setstance(MOVE);
				}
				else if (charpos.x() - curpos.x() < -50)
				{
					phobj.hforce = -PETWALKFORCE;
					flip = false;
					setstance(MOVE);
				}
				else
				{
					phobj.hforce = 0.0;
					setstance(STAND);
				}
			}
			phobj.type = PhysicsObject::NORMAL;
			phobj.clearflag(PhysicsObject::NOGRAVITY);
			break;
		case HANG:
			setposition(charpos.x(), charpos.y());
			phobj.setflag(PhysicsObject::NOGRAVITY);
			break;
		case FLY:
			if ((charpos - curpos).length() > 250)
			{
				setposition(charpos.x(), charpos.y());
			}
			else
			{
				if (charpos.x() - curpos.x() > 50)
				{
					phobj.hforce = PETFLYFORCE;
					flip = true;
				}
				else if (charpos.x() - curpos.x() < -50)
				{
					phobj.hforce = -PETFLYFORCE;
					flip = false;
				}
				else
				{
					phobj.hforce = 0.0f;
				}

				if (charpos.y() - curpos.y() > 50.0f)
					phobj.vforce = PETFLYFORCE;
				else if (charpos.y() - curpos.y() < -50.0f)
					phobj.vforce = -PETFLYFORCE;
				else
					phobj.vforce = 0.0f;
			}
			phobj.type = PhysicsObject::FLYING;
			phobj.clearflag(PhysicsObject::NOGRAVITY);
			break;
		}

		physics.moveobject(phobj);

		animations[stance].update();
	}

	void PetLook::setposition(int16_t x, int16_t y)
	{
		phobj.setx(x);
		phobj.sety(y);
	}

	void PetLook::setstance(Stance st)
	{
		if (stance != st)
		{
			stance = st;
			animations[stance].reset();
		}
	}

	void PetLook::setstance(uint8_t stancebyte)
	{
		flip = stancebyte % 2 == 1;
		stance = stancebyvalue(stancebyte);
	}

	int32_t PetLook::getiid() const
	{
		return itemid;
	}

	PetLook::Stance PetLook::getstance() const
	{
		return stance;
	}
}